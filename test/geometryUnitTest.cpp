#include "geometryUnitTest.hpp"
#include "Eigen"
#include "Output.hpp"

#include "Polygon.hpp"
#include "Polyhedron.hpp"
#include "ConcaveToConvex.hpp"
#include "Intersector2D1D.hpp"
#include "Intersector1D1D.hpp"
#include "Intersector2D2D.hpp"


using namespace std;
using namespace MainApplication;

namespace GeDiM
{
  namespace UnitTest
  {
    namespace Geometry
    {
      // ***************************************************************************
      void UnitTest::RunAllTests(const double& tolerance)
      {
        RunPolygonTests(tolerance);
        RunPolyhedronTests(tolerance);
      }
      // ***************************************************************************
      void UnitTest::RunPolygonTests(const double& tolerance)
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polygon tests", true);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestOne(tolerance);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestTwo(tolerance);
        Output::PrintLine('-');
        ConcavePolygonUnitTest::TestThree(tolerance);
      }
      // ***************************************************************************
      void UnitTest::RunPolyhedronTests(const double& tolerance)
      {
        Output::PrintLine('-');
        Output::PrintGenericMessage("Polyhedron tests", true);
        Output::PrintLine('-');
        cout<<endl;
        ConcavePolyhedronUnitTest::TestZero(tolerance);
        cout<<endl;
        Output::PrintLine('-');
        cout<<endl;
        ConcavePolyhedronUnitTest::TestOne(tolerance);
        cout<<endl;
        Output::PrintLine('-');
        cout<<endl;
        ConcavePolyhedronUnitTest::TestTwo(tolerance);
        cout<<endl;
        Output::PrintLine('-');
        cout<<endl;
        ConcavePolyhedronUnitTest::TestThree(tolerance);
        cout<<endl;
        Output::PrintLine('-');
        cout<<endl;
        ConcavePolyhedronUnitTest::TestFour(tolerance);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestOne(vector<Vertex>& vertices,  vector<ISegment*>& segments, IPolygon& concavePolygon)
      {
        unsigned int numVertices = 9, numSegments = 9;

        concavePolygon.Initialize(numVertices, numSegments);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.9239e+00, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 1.9239e+00));
        vertices.push_back(Vertex(6.1732e-01, 1.9239e+00));
        vertices.push_back(Vertex(7.6120e-02, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 6.1732e-01));
        vertices.push_back(Vertex(7.6120e-02, 6.1732e-01));
        vertices.push_back(Vertex(6.1732e-01, 7.6120e-02));
        vertices.push_back(Vertex(1.3827e+00, 7.6120e-02));
        vertices.push_back(Vertex(1.9239e+00, 6.1732e-01));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(new Segment(v + 1));

          ISegment& segment = *segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(*segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestTwo(vector<Vertex>& vertices,  vector<ISegment*>& segments, IPolygon& concavePolygon)
      {
        unsigned int numVertices = 10, numSegments = 10;

        concavePolygon.Initialize(numVertices, numSegments);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.0000e+00, 2.0000e+00));
        vertices.push_back(Vertex(7.6489e-01, 1.3236e+00));
        vertices.push_back(Vertex(4.8943e-02, 1.3090e+00));
        vertices.push_back(Vertex(6.1958e-01, 8.7639e-01));
        vertices.push_back(Vertex(4.1221e-01, 1.9098e-01));
        vertices.push_back(Vertex(1.0000e+00, 6.0000e-01));
        vertices.push_back(Vertex(1.5878e+00, 1.9098e-01));
        vertices.push_back(Vertex(1.3804e+00, 8.7639e-01));
        vertices.push_back(Vertex(1.9511e+00, 1.3090e+00));
        vertices.push_back(Vertex(1.2351e+00, 1.3236e+00));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(new Segment(v + 1));

          ISegment& segment = *segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(*segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::CreatePolygonTestThree(vector<Vertex>& vertices,  vector<ISegment*>& segments, IPolygon& concavePolygon)
      {
        unsigned int numVertices = 8, numSegments = 8;

        concavePolygon.Initialize(numVertices, numSegments);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.9239e+00, 1.3827e+00));
        vertices.push_back(Vertex(1.3827e+00, 1.9239e+00));
        vertices.push_back(Vertex(6.1732e-01, 1.9239e+00));
        vertices.push_back(Vertex(7.6120e-02, 1.3827e+00));
        vertices.push_back(Vertex(7.6120e-02, 6.1732e-01));
        vertices.push_back(Vertex(6.1732e-01, 7.6120e-02));
        vertices.push_back(Vertex(1.3827e+00, 7.6120e-02));
        vertices.push_back(Vertex(1.9239e+00, 6.1732e-01));

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolygon.AddVertex(vertices[s]);

        segments.reserve(numSegments);

        for (unsigned int v = 0; v < numVertices; v++)
        {
          segments.push_back(new Segment(v + 1));

          ISegment& segment = *segments[v];
          const Vertex& origin = vertices[v];
          const Vertex& end = vertices[(v + 1) % numVertices];
          segment.Initialize(origin, end);
        }

        for (unsigned int s = 0; s < numSegments; s++)
          concavePolygon.AddSegment(*segments[s]);
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestPolygon(const IPolygon& concavePolygon, const double& tolerance, const string& fatherFunctionName)
      {
        list<IPolygon*> convexPolygons;

        Output::Assert(ConcaveToConvex::ConcaveToConvexPolygon(concavePolygon, convexPolygons, tolerance), "%s: ConcaveToConvexPolygon", fatherFunctionName.c_str());

        unsigned int counter = 1;
        for (list<IPolygon*>::iterator it = convexPolygons.begin(); it != convexPolygons.end(); it++)
        {
          if (*it == NULL)
          {
            Output::PrintErrorMessage("Polygon %d is NULL", true, counter);
            continue;
          }

          const IPolygon& convexPolygon = **it;
          Output::Assert(ConcaveToConvex::IsPolygonConvex(convexPolygon, tolerance), "%s: IsPolygonConvex %d", fatherFunctionName.c_str(), counter);

          counter++;
        }

        for (list<IPolygon*>::iterator it = convexPolygons.begin(); it != convexPolygons.end(); it++)
          delete *it;
        convexPolygons.clear();
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestOne(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestOne(vertices, segments, concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestTwo(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestTwo(vertices, segments, concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];
      }
      // ***************************************************************************
      void ConcavePolygonUnitTest::TestThree(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        Polygon concavePolygon;

        ConcavePolygonUnitTest::CreatePolygonTestThree(vertices, segments, concavePolygon);
        ConcavePolygonUnitTest::TestPolygon(concavePolygon, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];
      }


      void ConcavePolyhedronUnitTest::CreatePolyhedronTestZero(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 8, numSegments = 12, numFaces = 6;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(0, 0, 0)); // 0
        vertices.push_back(Vertex(1, 0, 0)); // 1
        vertices.push_back(Vertex(0, 1, 0)); // 2
        vertices.push_back(Vertex(0, 0, 1)); // 3
        vertices.push_back(Vertex(1, 1, 1)); // 4
        vertices.push_back(Vertex(1, 0, 1)); // 5
        vertices.push_back(Vertex(0, 1, 1)); // 6
        vertices.push_back(Vertex(1, 1, 0)); // 7

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        segments.reserve(numSegments);
        for (unsigned int v = 0; v < numSegments; v++)
          segments.push_back(new Segment(v+1));

        segments[0]->Initialize(vertices[0], vertices[1]);
        segments[1]->Initialize(vertices[0], vertices[2]);
        segments[2]->Initialize(vertices[0], vertices[3]);
        segments[3]->Initialize(vertices[1], vertices[7]);
        segments[4]->Initialize(vertices[1], vertices[5]);
        segments[5]->Initialize(vertices[7], vertices[2]);
        segments[6]->Initialize(vertices[7], vertices[4]);
        segments[7]->Initialize(vertices[4], vertices[6]);
        segments[8]->Initialize(vertices[6], vertices[3]);
        segments[9]->Initialize(vertices[3], vertices[5]);
        segments[10]->Initialize(vertices[2], vertices[6]);
        segments[11]->Initialize(vertices[5], vertices[4]);

        for (unsigned int s = 0; s < numSegments; s++){
          segments[s]->ComputeTangent();
          concavePolyhedron.AddSegment(*segments[s]);
        }

        faces.reserve(numFaces);
        for (unsigned int f = 0; f < numFaces; f++)
        {
          faces.push_back(new Polygon(f + 1));
          IPolygon& face = *faces[f];

          //face.Initialize(3, 3);
        }

        faces[0]->AddVertex(vertices[0]);
        faces[0]->AddVertex(vertices[1]);
        faces[0]->AddVertex(vertices[2]);
        faces[0]->AddVertex(vertices[7]);
        faces[0]->AddSegment(*segments[0]);
        faces[0]->AddSegment(*segments[1]);
        faces[0]->AddSegment(*segments[3]);
        faces[0]->AddSegment(*segments[5]);
        faces[1]->AddVertex(vertices[3]);
        faces[1]->AddVertex(vertices[5]);
        faces[1]->AddVertex(vertices[4]);
        faces[1]->AddVertex(vertices[6]);
        faces[1]->AddSegment(*segments[9]);
        faces[1]->AddSegment(*segments[11]);
        faces[1]->AddSegment(*segments[7]);
        faces[1]->AddSegment(*segments[8]);
        faces[2]->AddVertex(vertices[0]);
        faces[2]->AddVertex(vertices[1]);
        faces[2]->AddVertex(vertices[5]);
        faces[2]->AddVertex(vertices[3]);
        faces[2]->AddSegment(*segments[0]);
        faces[2]->AddSegment(*segments[4]);
        faces[2]->AddSegment(*segments[9]);
        faces[2]->AddSegment(*segments[2]);
        faces[3]->AddVertex(vertices[1]);
        faces[3]->AddVertex(vertices[7]);
        faces[3]->AddVertex(vertices[4]);
        faces[3]->AddVertex(vertices[5]);
        faces[3]->AddSegment(*segments[6]);
        faces[3]->AddSegment(*segments[3]);
        faces[3]->AddSegment(*segments[11]);
        faces[3]->AddSegment(*segments[4]);
        faces[4]->AddVertex(vertices[7]);
        faces[4]->AddVertex(vertices[2]);
        faces[4]->AddVertex(vertices[6]);
        faces[4]->AddVertex(vertices[4]);
        faces[4]->AddSegment(*segments[5]);
        faces[4]->AddSegment(*segments[10]);
        faces[4]->AddSegment(*segments[7]);
        faces[4]->AddSegment(*segments[6]);
        faces[5]->AddVertex(vertices[2]);
        faces[5]->AddVertex(vertices[0]);
        faces[5]->AddVertex(vertices[3]);
        faces[5]->AddVertex(vertices[6]);
        faces[5]->AddSegment(*segments[1]);
        faces[5]->AddSegment(*segments[2]);
        faces[5]->AddSegment(*segments[8]);
        faces[5]->AddSegment(*segments[10]);

        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(*faces[f]);

        for (unsigned int f = 0; f < numFaces; f++){
            Polygon& poly = static_cast<Polygon&>(*faces[f]);

            poly.ComputePlane();
            poly.ComputeCentroid();
            poly.ComputeRotatedVertices();
        }
    }

      // ***************************************************************************
      void ConcavePolyhedronUnitTest::CreatePolyhedronTestOne(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 5, numSegments = 9, numFaces = 6;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1.6462e+00, 2.0335e+00, 2.0229e+00)); // 0
        vertices.push_back(Vertex(1.1764e+00, 6.6632e-01, 1.7380e+00)); // 1
        vertices.push_back(Vertex(4.2294e-01, 3.1275e+00, 2.4979e-01)); // 2
        vertices.push_back(Vertex(2.5080e+00, 2.3502e+00, 1.7143e+00)); // 3
        vertices.push_back(Vertex(2.2820e+00, 1.7009e+00, 1.1686e+00)); // 4

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        segments.reserve(numSegments);
        for (unsigned int v = 0; v < numSegments; v++)
          segments.push_back(new Segment(v+1));

        segments[0]->Initialize(vertices[1], vertices[4]);
        segments[1]->Initialize(vertices[4], vertices[3]);
        segments[2]->Initialize(vertices[3], vertices[0]);
        segments[3]->Initialize(vertices[0], vertices[1]);
        segments[4]->Initialize(vertices[0], vertices[4]);
        segments[5]->Initialize(vertices[0], vertices[2]);
        segments[6]->Initialize(vertices[1], vertices[2]);
        segments[7]->Initialize(vertices[3], vertices[2]);
        segments[8]->Initialize(vertices[4], vertices[2]);

        for (unsigned int s = 0; s < numSegments; s++){
          segments[s]->ComputeTangent();
          concavePolyhedron.AddSegment(*segments[s]);
        }

        faces.reserve(numFaces);
        for (unsigned int f = 0; f < numFaces; f++)
        {
          faces.push_back(new Polygon(f + 1));
          IPolygon& face = *faces[f];

          face.Initialize(3, 3);
        }

        faces[0]->AddVertex(vertices[1]);
        faces[0]->AddVertex(vertices[2]);
        faces[0]->AddVertex(vertices[4]);
        faces[0]->AddSegment(*segments[6]);
        faces[0]->AddSegment(*segments[8]);
        faces[0]->AddSegment(*segments[0]);
        faces[1]->AddVertex(vertices[4]);
        faces[1]->AddVertex(vertices[2]);
        faces[1]->AddVertex(vertices[3]);
        faces[1]->AddSegment(*segments[8]);
        faces[1]->AddSegment(*segments[7]);
        faces[1]->AddSegment(*segments[1]);
        faces[2]->AddVertex(vertices[1]);
        faces[2]->AddVertex(vertices[2]);
        faces[2]->AddVertex(vertices[0]);
        faces[2]->AddSegment(*segments[6]);
        faces[2]->AddSegment(*segments[5]);
        faces[2]->AddSegment(*segments[3]);
        faces[3]->AddVertex(vertices[0]);
        faces[3]->AddVertex(vertices[2]);
        faces[3]->AddVertex(vertices[3]);
        faces[3]->AddSegment(*segments[5]);
        faces[3]->AddSegment(*segments[7]);
        faces[3]->AddSegment(*segments[2]);
        faces[4]->AddVertex(vertices[1]);
        faces[4]->AddVertex(vertices[4]);
        faces[4]->AddVertex(vertices[0]);
        faces[4]->AddSegment(*segments[0]);
        faces[4]->AddSegment(*segments[4]);
        faces[4]->AddSegment(*segments[3]);
        faces[5]->AddVertex(vertices[4]);
        faces[5]->AddVertex(vertices[3]);
        faces[5]->AddVertex(vertices[0]);
        faces[5]->AddSegment(*segments[1]);
        faces[5]->AddSegment(*segments[2]);
        faces[5]->AddSegment(*segments[4]);


        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(*faces[f]);


        /// **************************************************************************
        /// **************************************************************************
        /// Aggiunto perchè mancavano le info per le facce superiori alla seconda
        for (unsigned int f = 0; f < numFaces; f++){
            Polygon& poly = static_cast<Polygon&>(*faces[f]);

            poly.ComputePlane();
            poly.ComputeCentroid();
            poly.ComputeRotatedVertices();
        }
        /// **************************************************************************
        /// **************************************************************************


        Polygon& poly = static_cast<Polygon&>(*faces[0]);
        Polygon& poly2 = static_cast<Polygon&>(*faces[1]);

        poly.ComputePlane();
        poly.ComputeCentroid();
        poly.ComputeRotatedVertices();

        poly2.ComputePlane();
        poly2.ComputeCentroid();
        poly2.ComputeRotatedVertices();

        Intersector1D1D intersector;
        Vector3d puntoZero(0.5, 0.0, 0.0);
        Vector3d puntoUno(1.0, 2.0, 0.0);
        Vector3d vettoreTangente = puntoUno - puntoZero;

        const Vertex& firstVertex = poly.RotatedVertex(0);
        const Vertex& secondVertex = poly.RotatedVertex(1);
        Vector3d tangentVector = secondVertex - firstVertex;

        intersector.SetFirstTangentVector(tangentVector);
        intersector.SetSecondTangentVector(vettoreTangente);

        Vector3d tangentStartPoints = puntoZero - firstVertex;
        intersector.ComputeIntersectionEdges(tangentVector, vettoreTangente, tangentStartPoints);

        Vector3d intersectionPoint = intersector.IntersectionStartPointFirstVector(firstVertex, tangentVector);
        Vector3d intersectionPoint2 = intersector.IntersectionStartPointSecondVector(puntoZero, vettoreTangente);

        double difference = (intersectionPoint- intersectionPoint2).norm();
        Intersector1D1D::Type tipoIntersezione = intersector.TypeIntersection();
/*
        if(tipoIntersezione == Intersector1D1D::IntersectionOnLine )
            //cout << "Intersezione sulla retta" << endl;
        else if (tipoIntersezione == Intersector1D1D::IntersectionOnSegment)
            //cout << "Intersezione nel segmento" << endl;
*/
        Intersector2D2D intersectorPlanes;

        intersectorPlanes.SetFirstPlane(poly.Normal(), poly.PlaneTranslation());
        intersectorPlanes.SetSecondPlane(poly2.Normal(), poly2.PlaneTranslation());

        intersectorPlanes.ComputeIntersection();
        Vector3d LineIntersection = intersectorPlanes.TangentLine();
        Vector3d StartPoint = intersectorPlanes.PointLine();

        Intersector2D1D intersectorPlaneLine;
        intersectorPlaneLine.SetLine(StartPoint, LineIntersection);
        intersectorPlaneLine.SetPlane(poly.Normal(), poly.PlaneTranslation());
        intersectorPlaneLine.ComputeIntersection();

        /*if(intersectorPlaneLine.IntersectionType() == Intersector2D1D::Coplanar)
            cout << "Retta appartiene al piano" << endl;
    */
    }
      // ***************************************************************************








            // ***************************************************************************
      void ConcavePolyhedronUnitTest::CreatePolyhedronTestTwo(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 5, numSegments = 9, numFaces = 6;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex(1, 2, 1)); // 0
        vertices.push_back(Vertex(1, 0, 0)); // 1
        vertices.push_back(Vertex(0, 1, 0)); // 2
        vertices.push_back(Vertex(0, 0, 1)); // 3
        vertices.push_back(Vertex(1, 1, 0)); // 4

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        segments.reserve(numSegments);
        for (unsigned int v = 0; v < numSegments; v++)
          segments.push_back(new Segment(v+1));

        segments[0]->Initialize(vertices[1], vertices[4]);
        segments[1]->Initialize(vertices[1], vertices[2]);
        segments[2]->Initialize(vertices[2], vertices[3]);
        segments[3]->Initialize(vertices[0], vertices[3]);
        segments[4]->Initialize(vertices[0], vertices[4]);
        segments[5]->Initialize(vertices[1], vertices[3]);
        segments[6]->Initialize(vertices[2], vertices[4]);
        segments[7]->Initialize(vertices[2], vertices[0]);
        segments[8]->Initialize(vertices[3], vertices[4]);

        for (unsigned int s = 0; s < numSegments; s++){
          segments[s]->ComputeTangent();
          concavePolyhedron.AddSegment(*segments[s]);
        }

        faces.reserve(numFaces);
        for (unsigned int f = 0; f < numFaces; f++)
        {
          faces.push_back(new Polygon(f + 1));
          IPolygon& face = *faces[f];

          //face.Initialize(3, 3);
        }

        faces[0]->AddVertex(vertices[0]);
        faces[0]->AddVertex(vertices[3]);
        faces[0]->AddVertex(vertices[4]);
        faces[0]->AddSegment(*segments[3]);
        faces[0]->AddSegment(*segments[4]);
        faces[0]->AddSegment(*segments[8]);
        faces[1]->AddVertex(vertices[1]);
        faces[1]->AddVertex(vertices[2]);
        faces[1]->AddVertex(vertices[3]);
        faces[1]->AddSegment(*segments[1]);
        faces[1]->AddSegment(*segments[2]);
        faces[1]->AddSegment(*segments[5]);
        faces[2]->AddVertex(vertices[0]);
        faces[2]->AddVertex(vertices[2]);
        faces[2]->AddVertex(vertices[3]);
        faces[2]->AddSegment(*segments[2]);
        faces[2]->AddSegment(*segments[7]);
        faces[2]->AddSegment(*segments[3]);
        faces[3]->AddVertex(vertices[0]);
        faces[3]->AddVertex(vertices[2]);
        faces[3]->AddVertex(vertices[4]);
        faces[3]->AddSegment(*segments[6]);
        faces[3]->AddSegment(*segments[7]);
        faces[3]->AddSegment(*segments[4]);
        faces[4]->AddVertex(vertices[1]);
        faces[4]->AddVertex(vertices[4]);
        faces[4]->AddVertex(vertices[2]);
        faces[4]->AddSegment(*segments[0]);
        faces[4]->AddSegment(*segments[6]);
        faces[4]->AddSegment(*segments[1]);
        faces[5]->AddVertex(vertices[1]);
        faces[5]->AddVertex(vertices[3]);
        faces[5]->AddVertex(vertices[4]);
        faces[5]->AddSegment(*segments[5]);
        faces[5]->AddSegment(*segments[0]);
        faces[5]->AddSegment(*segments[8]);

        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(*faces[f]);

        for (unsigned int f = 0; f < numFaces; f++){
            Polygon& poly = static_cast<Polygon&>(*faces[f]);

            poly.ComputePlane();
            poly.ComputeCentroid();
            poly.ComputeRotatedVertices();
        }
    }
      // ***************************************************************************



      void ConcavePolyhedronUnitTest::CreatePolyhedronTestThree(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 7, numSegments = 12, numFaces = 7;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex( 0, 0, 0)); // 0
        vertices.push_back(Vertex( 0, 0, 4)); // 1
        vertices.push_back(Vertex(-2, 0, 3)); // 2
        vertices.push_back(Vertex( 2, 0, 3)); // 3
        vertices.push_back(Vertex(-1, 0, 2)); // 4
        vertices.push_back(Vertex( 1, 0, 2)); // 5
        vertices.push_back(Vertex( 0, 1, 3)); // 6

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        segments.reserve(numSegments);
        for (unsigned int v = 0; v < numSegments; v++)
          segments.push_back(new Segment(v+1));

        segments[0] ->Initialize(vertices[0], vertices[6]);
        segments[1] ->Initialize(vertices[0], vertices[2]);
        segments[2] ->Initialize(vertices[0], vertices[3]);
        segments[3] ->Initialize(vertices[2], vertices[6]);
        segments[4] ->Initialize(vertices[6], vertices[3]);
        segments[5] ->Initialize(vertices[2], vertices[4]);
        segments[6] ->Initialize(vertices[5], vertices[3]);
        segments[7] ->Initialize(vertices[4], vertices[6]);
        segments[8] ->Initialize(vertices[5], vertices[6]);
        segments[9] ->Initialize(vertices[1], vertices[6]);
        segments[10]->Initialize(vertices[4], vertices[1]);
        segments[11]->Initialize(vertices[5], vertices[1]);

        for (unsigned int s = 0; s < numSegments; s++){
          segments[s]->ComputeTangent();
          concavePolyhedron.AddSegment(*segments[s]);
        }

        faces.reserve(numFaces);
        for (unsigned int f = 0; f < numFaces; f++)
        {
          faces.push_back(new Polygon(f + 1));
          IPolygon& face = *faces[f];

          //face.Initialize(3, 3);
        }

        faces[0]->AddVertex(vertices[0]);
        faces[0]->AddVertex(vertices[2]);
        faces[0]->AddVertex(vertices[6]);
        faces[0]->AddSegment(*segments[0]);
        faces[0]->AddSegment(*segments[1]);
        faces[0]->AddSegment(*segments[3]);
        faces[1]->AddVertex(vertices[0]);
        faces[1]->AddVertex(vertices[6]);
        faces[1]->AddVertex(vertices[3]);
        faces[1]->AddSegment(*segments[0]);
        faces[1]->AddSegment(*segments[2]);
        faces[1]->AddSegment(*segments[4]);
        faces[2]->AddVertex(vertices[5]);
        faces[2]->AddVertex(vertices[6]);
        faces[2]->AddVertex(vertices[3]);
        faces[2]->AddSegment(*segments[4]);
        faces[2]->AddSegment(*segments[6]);
        faces[2]->AddSegment(*segments[8]);
        faces[3]->AddVertex(vertices[6]);
        faces[3]->AddVertex(vertices[2]);
        faces[3]->AddVertex(vertices[4]);
        faces[3]->AddSegment(*segments[3]);
        faces[3]->AddSegment(*segments[5]);
        faces[3]->AddSegment(*segments[7]);
        faces[4]->AddVertex(vertices[5]);
        faces[4]->AddVertex(vertices[1]);
        faces[4]->AddVertex(vertices[6]);
        faces[4]->AddSegment(*segments[8]);
        faces[4]->AddSegment(*segments[9]);
        faces[4]->AddSegment(*segments[11]);
        faces[5]->AddVertex(vertices[1]);
        faces[5]->AddVertex(vertices[6]);
        faces[5]->AddVertex(vertices[4]);
        faces[5]->AddSegment(*segments[7]);
        faces[5]->AddSegment(*segments[10]);
        faces[5]->AddSegment(*segments[9]);
        faces[6]->AddVertex(vertices[0]);
        faces[6]->AddVertex(vertices[2]);
        faces[6]->AddVertex(vertices[4]);
        faces[6]->AddVertex(vertices[1]);
        faces[6]->AddVertex(vertices[5]);
        faces[6]->AddVertex(vertices[3]);
        faces[6]->AddSegment(*segments[5]);
        faces[6]->AddSegment(*segments[10]);
        faces[6]->AddSegment(*segments[1]);
        faces[6]->AddSegment(*segments[11]);
        faces[6]->AddSegment(*segments[6]);
        faces[6]->AddSegment(*segments[2]);


        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(*faces[f]);

        for (unsigned int f = 0; f < numFaces; f++){
            Polygon& poly = static_cast<Polygon&>(*faces[f]);

            poly.ComputePlane();
            poly.ComputeCentroid();
            poly.ComputeRotatedVertices();
        }
    }
 // ***************************************************************************

void ConcavePolyhedronUnitTest::CreatePolyhedronTestFour(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron)
      {
        unsigned int numVertices = 10, numSegments = 15, numFaces = 7;

        concavePolyhedron.Initialize(numVertices, numSegments, numFaces);

        vertices.reserve(numVertices);
        vertices.push_back(Vertex( 0, 0, 0)); // 0
        vertices.push_back(Vertex( 1, 0, 0)); // 1
        vertices.push_back(Vertex( 1, 1, 0)); // 2
        vertices.push_back(Vertex( 0, 1, 0)); // 3
        vertices.push_back(Vertex( 0, 0, 1)); // 4
        vertices.push_back(Vertex( 1, 0, 1)); // 5
        vertices.push_back(Vertex( 1, 0.5, 0.67)); // 6
        vertices.push_back(Vertex( 1, 1, 1));//7
        vertices.push_back(Vertex( 0, 1, 1));//8
        vertices.push_back(Vertex( 0, 0.5, 0.67));//9

        for (unsigned int s = 0; s < numVertices; s++)
          concavePolyhedron.AddVertex(vertices[s]);

        segments.reserve(numSegments);
        for (unsigned int v = 0; v < numSegments; v++)
          segments.push_back(new Segment(v+1));

        segments[0] ->Initialize(vertices[0], vertices[1]);
        segments[1] ->Initialize(vertices[1], vertices[2]);
        segments[2] ->Initialize(vertices[2], vertices[3]);
        segments[3] ->Initialize(vertices[3], vertices[0]);
        segments[4] ->Initialize(vertices[0], vertices[4]);
        segments[5] ->Initialize(vertices[1], vertices[5]);
        segments[6] ->Initialize(vertices[2], vertices[7]);
        segments[7] ->Initialize(vertices[3], vertices[8]);
        segments[8] ->Initialize(vertices[4], vertices[5]);
        segments[9] ->Initialize(vertices[5], vertices[6]);
        segments[10]->Initialize(vertices[6], vertices[7]);
        segments[11]->Initialize(vertices[7], vertices[8]);
        segments[12]->Initialize(vertices[8], vertices[9]);
        segments[13]->Initialize(vertices[9], vertices[4]);
        segments[14]->Initialize(vertices[9], vertices[6]);

        for (unsigned int s = 0; s < numSegments; s++){
          segments[s]->ComputeTangent();
          concavePolyhedron.AddSegment(*segments[s]);
        }

        faces.reserve(numFaces);
        for (unsigned int f = 0; f < numFaces; f++)
        {
          faces.push_back(new Polygon(f + 1));
          IPolygon& face = *faces[f];

          //face.Initialize(3, 3);
        }

        faces[0]->AddVertex(vertices[0]);
        faces[0]->AddVertex(vertices[1]);
        faces[0]->AddVertex(vertices[2]);
        faces[0]->AddVertex(vertices[3]);
        faces[0]->AddSegment(*segments[0]);
        faces[0]->AddSegment(*segments[1]);
        faces[0]->AddSegment(*segments[2]);
        faces[0]->AddSegment(*segments[3]);
        faces[1]->AddVertex(vertices[0]);
        faces[1]->AddVertex(vertices[1]);
        faces[1]->AddVertex(vertices[5]);
        faces[1]->AddVertex(vertices[4]);
        faces[1]->AddSegment(*segments[0]);
        faces[1]->AddSegment(*segments[4]);
        faces[1]->AddSegment(*segments[5]);
        faces[1]->AddSegment(*segments[8]);
        faces[2]->AddVertex(vertices[1]);
        faces[2]->AddVertex(vertices[5]);
        faces[2]->AddVertex(vertices[6]);
        faces[2]->AddVertex(vertices[7]);
        faces[2]->AddVertex(vertices[2]);
        faces[2]->AddSegment(*segments[1]);
        faces[2]->AddSegment(*segments[6]);
        faces[2]->AddSegment(*segments[10]);
        faces[2]->AddSegment(*segments[9]);
        faces[2]->AddSegment(*segments[5]);
        faces[3]->AddVertex(vertices[2]);
        faces[3]->AddVertex(vertices[3]);
        faces[3]->AddVertex(vertices[8]);
        faces[3]->AddVertex(vertices[7]);
        faces[3]->AddSegment(*segments[2]);
        faces[3]->AddSegment(*segments[6]);
        faces[3]->AddSegment(*segments[11]);
        faces[3]->AddSegment(*segments[7]);
        faces[4]->AddVertex(vertices[0]);
        faces[4]->AddVertex(vertices[4]);
        faces[4]->AddVertex(vertices[9]);
        faces[4]->AddVertex(vertices[8]);
        faces[4]->AddVertex(vertices[3]);
        faces[4]->AddSegment(*segments[4]);
        faces[4]->AddSegment(*segments[3]);
        faces[4]->AddSegment(*segments[7]);
        faces[4]->AddSegment(*segments[12]);
        faces[4]->AddSegment(*segments[13]);
        faces[5]->AddVertex(vertices[4]);
        faces[5]->AddVertex(vertices[5]);
        faces[5]->AddVertex(vertices[6]);
        faces[5]->AddVertex(vertices[9]);
        faces[5]->AddSegment(*segments[9]);
        faces[5]->AddSegment(*segments[8]);
        faces[5]->AddSegment(*segments[14]);
        faces[5]->AddSegment(*segments[13]);
        faces[6]->AddVertex(vertices[6]);
        faces[6]->AddVertex(vertices[7]);
        faces[6]->AddVertex(vertices[8]);
        faces[6]->AddVertex(vertices[9]);
        faces[6]->AddSegment(*segments[14]);
        faces[6]->AddSegment(*segments[11]);
        faces[6]->AddSegment(*segments[10]);
        faces[6]->AddSegment(*segments[12]);


        for (unsigned int f = 0; f < numFaces; f++)
          concavePolyhedron.AddFace(*faces[f]);

        for (unsigned int f = 0; f < numFaces; f++){
            Polygon& poly = static_cast<Polygon&>(*faces[f]);

            poly.ComputePlane();
            poly.ComputeCentroid();
            poly.ComputeRotatedVertices();
        }
    }
 // ***************************************************************************







      void ConcavePolyhedronUnitTest::TestPolyhedron(const IPolyhedron& concavoPolyhedron, const double& tolerance, const string& fatherFunctionName)
      {
        list<IPolyhedron*> convexPolyhedra;
        vector <int*> problemi;
        bool resoult =0;


        IPolyhedron& concavePolyhedron=*concavoPolyhedron.Clone();
        for (unsigned int i=0; i<concavoPolyhedron.NumberOfVertices();i++){
            concavePolyhedron.AddVertex(concavoPolyhedron.GetVertex(i));
        }
        for (unsigned int i=0; i<concavoPolyhedron.NumberOfSegments();i++){
            concavePolyhedron.AddSegment(concavoPolyhedron.GetSegment(i));
        }
        for (unsigned int i=0; i<concavoPolyhedron.NumberOfFaces();i++){
            concavePolyhedron.AddFace(concavoPolyhedron.GetFace(i));
        }


        resoult = ConcaveToConvex::IsPolyhedronConvex(concavePolyhedron, tolerance, problemi);
        Output::Assert(resoult, "%s: IsPolyhedronConvex", fatherFunctionName.c_str());
        if(!resoult){
            //cout<<endl<<"***********************************************************************"<<endl;
            cout<<"       - Il poliedro è concavo, procedo con il taglio"<<endl;
            //cout<<endl<<"***********************************************************************"<<endl;
            Output::Assert(ConcaveToConvex::ConcaveToConvexPolyhedron(concavePolyhedron, convexPolyhedra, tolerance, problemi), "%s: ConcaveToConvexPolyhedron", fatherFunctionName.c_str());
        }
            if (!resoult){
                //cout<<endl<<"***********************************************************************"<<endl;
                cout<<"       - Controllo che tutti i poliedri ottenuti siano effettivamente convessi\n";
                //cout<<endl<<"***********************************************************************"<<endl;

                unsigned int counter = 1;
                for (list<IPolyhedron*>::iterator it = convexPolyhedra.begin(); it != convexPolyhedra.end(); it++)
                {
                if (*it == NULL)
                {
                    Output::PrintErrorMessage("Polyhedron %d is NULL", true, counter);
                    continue;
                }

                problemi.clear();
                const IPolyhedron& convexPolyhedron = **it;
                Output::Assert(ConcaveToConvex::IsPolyhedronConvex(convexPolyhedron, tolerance, problemi), "%s: IsPolyhedronConvex %d", fatherFunctionName.c_str(), counter);

                counter++;
                }
            }

            for (list<IPolyhedron*>::iterator it = convexPolyhedra.begin(); it != convexPolyhedra.end(); it++)
            delete *it;
            convexPolyhedra.clear();
      }
      // ***************************************************************************
      void ConcavePolyhedronUnitTest::TestZero(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        vector<IPolygon*> faces;
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestZero(vertices, segments, faces, concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];

        for (unsigned int s = 0; s < faces.size(); s++)
          delete faces[s];
        // ***************************************************************************
      }

      void ConcavePolyhedronUnitTest::TestOne(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        vector<IPolygon*> faces;
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestOne(vertices, segments, faces, concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];

        for (unsigned int s = 0; s < faces.size(); s++)
          delete faces[s];
        // ***************************************************************************
      }

       void ConcavePolyhedronUnitTest::TestTwo(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        vector<IPolygon*> faces;
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestTwo(vertices, segments, faces, concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];

        for (unsigned int s = 0; s < faces.size(); s++)
          delete faces[s];
        // ***************************************************************************
      }
       void ConcavePolyhedronUnitTest::TestThree(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        vector<IPolygon*> faces;
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestThree(vertices, segments, faces, concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];

        for (unsigned int s = 0; s < faces.size(); s++)
          delete faces[s];
        // ***************************************************************************
      }

      void ConcavePolyhedronUnitTest::TestFour(const double& tolerance)
      {
        vector<Vertex> vertices;
        vector<ISegment*> segments;
        vector<IPolygon*> faces;
        Polyhedron concavePolyhedron;

        ConcavePolyhedronUnitTest::CreatePolyhedronTestFour(vertices, segments, faces, concavePolyhedron);
        ConcavePolyhedronUnitTest::TestPolyhedron(concavePolyhedron, tolerance, __func__);

        for (unsigned int s = 0; s < segments.size(); s++)
          delete segments[s];

        for (unsigned int s = 0; s < faces.size(); s++)
          delete faces[s];
        // ***************************************************************************
      }
    }
  }
}
