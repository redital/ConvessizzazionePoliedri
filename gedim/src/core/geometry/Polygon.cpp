#include "Polygon.hpp"
#include "DefineNumbers.hpp"
#include "Measurer.hpp"


namespace GeDiM
{

    // ***************************************************************************
    Polygon::Polygon()
    {
        planeNormal = NULL;
        planeTranslation = 0.0;
        rotatedCentroid = NULL;

        barycenter = NULL;
        centroid = NULL;
        measure = 0.0;
        squaredRadius = 0.0;
        radius = 0.0;
        aspectRatio = 0.0;
    }

    Polygon::~Polygon()
    {
        if(planeNormal != NULL)
            delete planeNormal;

        if(rotatedCentroid != NULL)
            delete rotatedCentroid;

        if(centroid != NULL)
            delete centroid;

        if(barycenter != NULL)
            delete barycenter;

        vertices.clear();
        rotatedVertices.clear();
        segments.clear();
    }

  Output::ExitCodes Polygon::ComputeBarycenter(Vertex& _barycenter) const
    {
        _barycenter.setZero();
        double inverseNumberPoints = 1.0/NumberOfVertices();
        for (unsigned int i = 0; i < NumberOfVertices(); i++)
            _barycenter += GetVertex(i) * inverseNumberPoints;

        return Output::Success;
    }
    // ***************************************************************************
  Output::ExitCodes Polygon::ComputeCentroid(Vertex& _centroid) const
    {
        _centroid.setZero();
        unsigned int numberPoints = NumberOfVertices();

        vector<double> valuePositive;
        vector<double> valueNegative;
        double valueP = 0.0;
        double valueN = 0.0;
        vector<double> valuePositive2;
        vector<double> valueNegative2;
        double value2P = 0.0;
        double value2N = 0.0;

        vector<double> measurePositive;
        vector<double> measureNegative;
        double measureP = 0.0;
        double measureN = 0.0;

        valuePositive.reserve(numberPoints);
        valueNegative.reserve(numberPoints);
        valuePositive2.reserve(numberPoints);
        valueNegative2.reserve(numberPoints);
        measurePositive.reserve(numberPoints);
        measureNegative.reserve(numberPoints);
        double resultTemp = 0.0;

        const vector< const Vertex* >& VerticesTemp = (NumberOfRotatedVertices() > 0)? RotatedVertices() : Vertices();
        for (unsigned int i = 0; i < numberPoints; i++)
        {
            const Vector3d& vertex = *VerticesTemp[i];
            const Vector3d& nextVertex = *VerticesTemp[(i+1)%numberPoints];
            Vector3d sumPoint = (vertex + nextVertex);
            Vector3d normal(0.5*(nextVertex[1] - vertex[1]), 0.5*(vertex[0] - nextVertex[0]), 0.0);

            resultTemp = sumPoint(0) * normal(0);
            if(resultTemp > 1.0E-16)
                measurePositive.push_back(resultTemp);
            else
                measureNegative.push_back(resultTemp);

            resultTemp = (vertex(0)*vertex(0) +
                                        sumPoint(0)*sumPoint(0)	+
                                        nextVertex(0)*nextVertex(0)) * normal(0);

            if(resultTemp > 1.0E-16)
                valuePositive.push_back(resultTemp);
            else
                valueNegative.push_back(resultTemp);

            resultTemp = (vertex(1)*vertex(1) +
                                        sumPoint(1)*sumPoint(1)	+
                                        nextVertex(1)*nextVertex(1)) * normal(1);

            if(resultTemp > 1.0E-16)
                valuePositive2.push_back(resultTemp);
            else
                valueNegative2.push_back(resultTemp);
        }
        sort(valuePositive.begin(), valuePositive.end());
        sort(valueNegative.begin(), valueNegative.end());
        sort(valuePositive2.begin(), valuePositive2.end());
        sort(valueNegative2.begin(), valueNegative2.end());
        sort(measurePositive.begin(), measurePositive.end());
        sort(measureNegative.begin(), measureNegative.end());

        for_each(valuePositive.begin(), valuePositive.end(), [&] (double n) {valueP += n;});
        for_each(valueNegative.begin(), valueNegative.end(), [&] (double n) {valueN += n;});
        for_each(valuePositive2.begin(), valuePositive2.end(), [&] (double n) {value2P += n;});
        for_each(valueNegative2.begin(), valueNegative2.end(), [&] (double n) {value2N += n;});
        for_each(measurePositive.begin(), measurePositive.end(), [&] (double n) {measureP += n;});
        for_each(measureNegative.begin(), measureNegative.end(), [&] (double n) {measureN += n;});

        _centroid[0] = valueP + valueN ;
        _centroid[1] = value2P + value2N;

        double invertMeasure = 1.0/(measureP + measureN);
        _centroid[0] = _centroid[0] * invertMeasure * RAT1_6;
        _centroid[1] = _centroid[1] * invertMeasure * RAT1_6;
        _centroid = RotatePoint(_centroid, true , true);
        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Polygon::ComputeMeasure(double& _measure) const
    {
        if(rotatedVertices.size() == 0)
        {
            Output::PrintErrorMessage("Compute rotated vertices to compute polygon area", true);
            return Output::GenericError;
        }
        unsigned int numberPoints = NumberOfVertices();
        vector<double> measurePositive;
        vector<double> measureNegative;
        double measureP = 0.0;
        double measureN = 0.0;

        measurePositive.reserve(numberPoints);
        measureNegative.reserve(numberPoints);
        double resultTemp = 0.0;

        for (unsigned int i = 0; i < numberPoints; i++)
        {
            const Vertex& vertex = RotatedVertex(i);
            const Vertex& nextVertex = RotatedVertex((i + 1)%numberPoints);
            Vector3d sumPoint = (vertex + nextVertex);
            Vector3d normal(0.5*(nextVertex[1] - vertex[1]), 0.5*(vertex[0] - nextVertex[0]), 0.0);

            resultTemp = sumPoint(0) * normal(0);
            if(resultTemp > 1.0E-16)
                measurePositive.push_back(resultTemp);
            else
                measureNegative.push_back(resultTemp);
        }
        sort(measurePositive.begin(), measurePositive.end());
        sort(measureNegative.begin(), measureNegative.end());

        for_each(measurePositive.begin(), measurePositive.end(), [&] (double n) {measureP += n;});
        for_each(measureNegative.begin(), measureNegative.end(), [&] (double n) {measureN += n;});

        _measure = measureP + measureN;
        return Output::Success;
    }

    // ***************************************************************************
    Output::ExitCodes Polygon::ComputeRadius(double& _radius) const
    {
        double squaredRadius = 0.0;
        _radius = 0.0;
        const unsigned int numberVertices = this->NumberOfVertices();
        Vertex* centroidTemp = NULL;
        if(this->centroid != NULL)
            centroidTemp = centroid;
        else
            ComputeCentroid(*centroidTemp);

        double squaredDistance = 0.0;
        for (unsigned int v = 0; v < numberVertices; v++)
        {
            squaredDistance = (*centroidTemp - GetVertex(v)).squaredNorm();
            if (squaredRadius < squaredDistance)
                squaredRadius = squaredDistance;
        }

        _radius = sqrt(squaredRadius);
        return Output::Success;
    }

    // ***************************************************************************
    Output::ExitCodes Polygon::ComputeSquaredRadius(double& _squaredRadius) const
    {
        _squaredRadius = 0.0;
        const unsigned int numberVertices = NumberOfVertices();
        Vertex* centroidTemp = NULL;

        if(centroid != NULL)
            centroidTemp = centroid;
        else
            ComputeCentroid(*centroidTemp);

        double squaredDistance = 0.0;
        for (unsigned int v = 0; v < numberVertices; v++)
        {
            squaredDistance = (*centroidTemp - GetVertex(v)).squaredNorm();
            if (_squaredRadius < squaredDistance)
                _squaredRadius = squaredDistance;
        }

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Polygon::ComputeAspectRatio(double& _aspectRatio) const
    {
        if(rotatedVertices.size() == 0)
        {
            Output::PrintErrorMessage("Compute rotated vertices to compute the aspect ratio of the polygon", true);
            return Output::GenericError;
        }
        Vertex centroid;
        ComputeCentroid(centroid);
        Vertex rotatedCentroid = RotatePoint(centroid);
        Measurer measurerEdge(Measurer::PointToLine);
        Measurer measurerPoint(Measurer::PointToPoint);

        double outRadius = 0.0;
        double inRadius = numeric_limits<double>::max();
        unsigned int numVertices = NumberOfVertices();
        for(unsigned int numPnt = 0; numPnt < numVertices; numPnt++)
        {
            Vector3d tangentVectorEdge = RotatedVertex((numPnt+1)%numVertices) - RotatedVertex(numPnt);
            Vector3d normalVectorEdge(tangentVectorEdge[1], -tangentVectorEdge[0], 0.0);
            normalVectorEdge *= 1.0/normalVectorEdge.norm();
            measurerEdge.ComputeDistancePointLineAndProj(rotatedCentroid, GetVertex(numPnt), tangentVectorEdge, normalVectorEdge);
            measurerPoint.ComputeSquaredDistancePoints(rotatedCentroid, GetVertex(numPnt));
            if(measurerEdge.DistanceSquared() < inRadius)
                inRadius = measurerEdge.DistanceSquared();
            if(measurerPoint.DistanceSquared() > outRadius)
                outRadius = measurerPoint.DistanceSquared();
        }
        _aspectRatio = sqrt(outRadius / inRadius);
        return Output::Success;
    }

    // ***************************************************************************
    void Polygon::ComputePlane()
    {
        planeNormal = new Vector3d();
        Vector3d& planeNormalTemp = *planeNormal;
        /// <li> Compute normal vector N
        planeNormalTemp.setZero();

        Vector3d edge = GetVertex(1) - GetVertex(0);

        Vector3d edgePrevious = GetVertex(NumberOfSegments() -1) -  GetVertex(0);

        planeNormalTemp.noalias() += edge.cross(edgePrevious);
        for(unsigned int i = 1; i < NumberOfSegments(); i++)
        {
            Vector3d edge = GetVertex((i+1)%NumberOfSegments()) - GetVertex(i);
            Vector3d edgePrevious = GetVertex(i - 1) - GetVertex(i);
            planeNormalTemp.noalias() += edge.cross(edgePrevious);
        }
        planeNormalTemp.normalize();

        /// <li> Compute d
        planeTranslation = planeNormalTemp.dot(*vertices[0]);

        return;
        /// </ul>
    }

    // ***************************************************************************
    void Polygon::ComputeRotationMatrix(const double& rotationTolerance)
    {
        if(planeNormal == NULL)
        {
            Output::PrintErrorMessage("Compute polygon plane to compute rotation matrix", true);
            exit(-1);
        }

        if(rotation != NULL)
        {
            Output::PrintWarningMessage("Rotation Matrix already computed", true);
            return;
        }

        unsigned int numVertices = NumberOfVertices();
        MatrixXd Z(3, numVertices);
        MatrixXd W(3, numVertices);
        Matrix3d H;
        Vector3d V1mV0 = *vertices[1] - *vertices[0];
        double normVectorOne = V1mV0.norm();
        Z.col(0) = V1mV0;
        W.col(0) << normVectorOne * cos(0.0), normVectorOne * sin(0.0), 0;
        for (unsigned int i = 2; i < numVertices; i++)
        {
            Vector3d VimV0 = *vertices[i] - *vertices[0];
            Z.col(i - 1) = VimV0;

            double normVectorI = VimV0.norm();
            double cosTheta = VimV0.dot(V1mV0) / (normVectorOne * normVectorI);


            if(cosTheta > 1.0 - rotationTolerance)
                W.col(i - 1) << normVectorI, 0.0, 0.0;
            else if(cosTheta < -1.0 + rotationTolerance)
                W.col(i - 1) << -normVectorI, 0.0, 0.0;
            else if((cosTheta > -rotationTolerance) && (cosTheta < rotationTolerance))
                W.col(i - 1) << 0.0, normVectorI, 0.0;
            else
            {
                double angleBetweenVectors = acos(cosTheta);
                W.col(i - 1) << normVectorI * cosTheta, normVectorI * sin(angleBetweenVectors), 0;
            }
        }
        Z.col(numVertices - 1) = *planeNormal;
        W.col(numVertices - 1)<< 0, 0, 1;
        H = W * Z.transpose();
        JacobiSVD<MatrixXd> svd(H, ComputeThinU | ComputeThinV);
        rotation = new Matrix3d();
        *rotation = svd.matrixV() * (svd.matrixU()).transpose();
        originTranslation = new Vector3d(*vertices[0]);
    }

    // ***************************************************************************
    void Polygon::ComputeRotatedVertices()
    {
        if(rotation == NULL)
        {
            //Output::PrintWarningMessage("Rotation matrix is not computed. I am computing it", true);
            ComputeRotationMatrix();
        }

        rotatedVertices.resize(NumberOfVertices());

        for(unsigned int v = 0; v < NumberOfVertices(); v++)
            rotatedVertices[v] = new Vertex(RotatePoint(*vertices[v]));

        if(centroid == NULL)
            ComputeCentroid();

        rotatedCentroid = new Vertex(RotatePoint(*centroid));
    }

    // ***************************************************************************
    void Polygon::ComputeRotatedVertices(const Matrix3d& rotationMatrix, const Vector3d& translationVector)
    {
        rotatedVertices.resize(NumberOfVertices());

        for(unsigned int v = 0; v < NumberOfVertices(); v++)
            rotatedVertices[v] = new Vertex(RotatePointWithInput(*vertices[v], rotationMatrix, translationVector));

        rotatedCentroid = new Vertex(RotatePointWithInput(*centroid, rotationMatrix, translationVector));
    }

    // ***************************************************************************
  bool Polygon::PointInside(const Vertex& point, const bool& rotatedPolygon, const double& tolerance) const
    {
        if(rotatedPolygon & (rotation == NULL || originTranslation == NULL))
        {
            Output::PrintGenericMessage("Rotation matrix and origin translation not computed ", true);
        }
        const vector< const Vertex* >& vertices = (rotatedPolygon)? RotatedVertices() : Vertices();

        Vector3d coordinatesPoint = (rotatedPolygon)? (*rotation).transpose() * (point - *originTranslation) : point;

        for(unsigned int pntVert = 0; pntVert < NumberOfVertices() ; pntVert++)
        {
            Vector3d tangentVectorEdge = *vertices[(pntVert+1)%NumberOfVertices()] - *vertices[pntVert];
            Vector3d tangentVectorDifference = coordinatesPoint -  *vertices[pntVert];

            double crossProd = tangentVectorEdge.x() * tangentVectorDifference.y() - tangentVectorDifference.x() * tangentVectorEdge.y();

            if(crossProd < -tolerance)
                return false;
        }
        return true;
    }
  // ***************************************************************************
}
