#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "GeometricObject.hpp"
#include "Segment.hpp"
#include "DefineNumbers.hpp"
#include "IPolygon.hpp"

using namespace std;
using namespace Eigen;
using namespace MainApplication;

namespace GeDiM
{
  class Polygon : public GeometricObject, public IPolygon
  {
    protected:
      vector<const Vertex*> vertices; ///< Array of domain vertices
      vector< const ISegment* > segments; ///< list of the segments in the polygon

      Vector3d* planeNormal; ///< Normal of plane containing the polygon in the space: comes from the equation ax+by+cz = d
      double planeTranslation; ///< plane translation in the space: comes from the equation ax+by+cz = d

      Vertex* rotatedCentroid;
      vector< const Vertex* > rotatedVertices;

    public:
      Polygon();
      Polygon(const unsigned int& _id) : Polygon() { globalId = _id; id = _id;}
      virtual ~Polygon();

      inline void Initialize(const unsigned int& numberOfVertices,
                             const unsigned int& numberOfSegments)
      {
        InitializeVertices(numberOfVertices);
        InitializeSegments(numberOfSegments);
      }

      inline const Vector3d* GetPlaneNormal () const { return planeNormal;}
      inline const double GetPlaneTranslation () const {return planeTranslation;}

      inline IPolygon* Clone() const { return new Polygon(); }

      inline void InitializeVertices(const unsigned int& numberOfVertices) { vertices.reserve(numberOfVertices); }
      inline void AddVertex(const Vertex& vertex) { vertices.push_back(&vertex); }
      inline void AddVertices(const vector<const Vertex*>& _vertices) { vertices = _vertices; }
      inline void DeleteVertices() { vertices.clear(); }
      inline unsigned int NumberOfVertices() const { return vertices.size(); }
      inline const Vertex& GetVertex(const unsigned int& position) const { return *vertices[position]; }
      inline const vector<const Vertex*>& Vertices() const { return vertices; }

      inline void InitializeSegments(const unsigned int& numberOfSegments) { segments.reserve(numberOfSegments);}
      inline void AddSegment(const ISegment& segment) { segments.push_back(&segment); }
      inline void AddSegments(const vector<const ISegment*>& _segments) {segments = _segments; }
      inline void DeleteSegments() { segments.clear(); }
      inline unsigned int NumberOfSegments() const { return segments.size(); }
      inline const ISegment& GetSegment(const unsigned int& position) const { return *segments[position]; }
      inline const vector<const ISegment*>& Segments() const { return segments; }

      inline unsigned int Dimension() const { return 2; }
      inline const Vertex& RotatedVertex(const unsigned int& position) const {return *rotatedVertices[position];}
      inline const vector< const Vertex* >& RotatedVertices() const { return rotatedVertices; }
      inline unsigned int NumberOfRotatedVertices() const { return rotatedVertices.size(); }
      inline const Vertex& RotatedCentroid() const { return *rotatedCentroid; }

      inline Output::ExitCodes ComputeBarycenter() { if(barycenter == NULL) barycenter = new Vertex(); return ComputeBarycenter(*barycenter); }
      Output::ExitCodes ComputeBarycenter(Vertex& _barycenter) const;

      ///Compute Centroid
      /// \brief Compute the centroid of the polygon and save inside the object
      inline Output::ExitCodes ComputeCentroid() { if(centroid == NULL) centroid = new Vertex(); return ComputeCentroid(*centroid); }
      Output::ExitCodes ComputeCentroid(Vertex& _centroid) const;

      ///Compute Measure
      /// \brief Compute the length of the edge and save inside the object
      inline Output::ExitCodes ComputeMeasure() { return ComputeMeasure(measure); }
      Output::ExitCodes ComputeMeasure(double& _measure) const;

      ///Compute radius
      /// \brief Compute the radius of the edge and save inside the object
      inline Output::ExitCodes ComputeRadius() { return ComputeRadius(radius); }
      Output::ExitCodes ComputeRadius(double& _radius) const;

      ///Compute squared radius
      /// \brief Compute the squared radius of the edge and save inside the object
      inline Output::ExitCodes ComputeSquaredRadius() { return ComputeSquaredRadius(squaredRadius); }
      Output::ExitCodes ComputeSquaredRadius(double& _radiusSquared) const;

      inline Output::ExitCodes ComputeAspectRatio() { return ComputeAspectRatio(aspectRatio); }
      Output::ExitCodes ComputeAspectRatio(double& _aspectRatio) const;

      const Vector3d& Normal() const { return *planeNormal; }
      const double& PlaneTranslation() const { return planeTranslation; }

      void ComputePlane();
      void ComputeRotatedVertices();
      void ComputeRotationMatrix(const double& rotationTolerance = 1.0E-12);
      void ComputeRotatedVertices(const Matrix3d& rotationMatrix, const Vector3d& translationVector);
      bool PointInside(const Vertex& point, const bool& rotatedPolygon = true, const double& tolerance = 1.0e-7) const;
  };
}
#endif //POLYGON_HPP
