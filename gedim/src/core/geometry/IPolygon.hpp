#ifndef IPOLYGON_HPP
#define IPOLYGON_HPP

#include "IRotation.hpp"
#include "ISegment.hpp"

namespace GeDiM
{
  class IPolygon : public IRotation, virtual public IGeometricObject
  {
    public:
      virtual ~IPolygon() {}

      enum Type
      {
        Unknown = 0,
        Triangle = 3,
        Square = 4,
      };

        virtual const Vector3d* GetPlaneNormal () const =0;
      virtual const double GetPlaneTranslation () const =0;

      /// Initialize the polygon with number of vertices and segments
      virtual void Initialize(const unsigned int& numberOfVertices, const unsigned int& numberOfSegments) = 0;
      /// Initialize the number of segments in the polygon
      virtual void InitializeSegments(const unsigned int& numberOfSegments) = 0;

      /// Create a new instance of the polygon
      virtual IPolygon* Clone() const = 0;

      /// Initialize the vertices of the geometric object
      virtual void InitializeVertices(const unsigned int& numberOfVertices) = 0;
      /// Add a single vertex to the geometric object
      virtual void AddVertex(const Vertex& vertex) = 0;
      /// Add a list of vertices to the geometric object
      virtual void AddVertices(const vector<const Vertex*>& _vertices) = 0;
      /// Deletes all the vertices
      virtual void DeleteVertices() = 0;


      /// Add a new segment in the polygon
      virtual void AddSegment(const ISegment& segment) = 0;
      /// Add a list of segments in the polygon
      virtual void AddSegments(const vector<const ISegment*>& _segments) = 0;
      /// Deletes all the segments
      virtual void DeleteSegments() = 0;
      /// @return The number of segments of the polygon
      virtual unsigned int NumberOfSegments() const = 0;
      /// @return The segment at position p of the polygon
      virtual const ISegment& GetSegment(const unsigned int& position) const = 0;
      /// @return The list of segments of the polygon
      virtual const vector<const ISegment*>& Segments() const = 0;

      /// @return The vertex at position of the polygon
      virtual const Vertex& RotatedVertex(const unsigned int& position) const = 0;
      /// @return The list of rotated vertices of the polygon
      virtual const vector< const Vertex* >& RotatedVertices() const = 0;
      /// @return The number of rotated vertices of the polygon
      virtual unsigned int NumberOfRotatedVertices() const = 0;
      /// @return The rotated centroid of the polygon
      virtual const Vertex& RotatedCentroid() const = 0;

      /// Computes the aspect ration and stores it in the polygon
      virtual Output::ExitCodes ComputeAspectRatio() = 0;
      /// Computes the aspect ration of the polygon
      /// @param[out] _aspectRatio : the aspect ration
      virtual Output::ExitCodes ComputeAspectRatio(double& _aspectRatio) const = 0;

      /// Computes the plane on which the polygon lies
      virtual void ComputePlane() = 0;
      /// Computes the rotated vertices of the polygon
      virtual void ComputeRotatedVertices() = 0;
      /// Computes the rotation matrix of the polygon
      virtual void ComputeRotationMatrix(const double& rotationTolerance) = 0;
      /// Computes the rotated vertices given a rotation matrix and a translation vector
      virtual void ComputeRotatedVertices(const Matrix3d& rotationMatrix, const Vector3d& translationVector) = 0;

      /// Checks if an input point is inside the polygon
      virtual bool PointInside(const Vertex& point, const bool& rotatedPolygon, const double& tolerance) const = 0;
  };
}

#endif // IPOLYGON_HPP
