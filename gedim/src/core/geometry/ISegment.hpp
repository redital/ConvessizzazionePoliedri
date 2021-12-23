#ifndef ISEGMENT_HPP
#define ISEGMENT_HPP

#include "IGeometricObject.hpp"

namespace GeDiM
{
  class ISegment : virtual public IGeometricObject
  {
    public:
      virtual ~ISegment() { }

      enum Position
      {
        AtTheLeft = 0,
        AtTheRight = 1,
        Beyond = 2,
        Behind = 3,
        Between = 4,
        AtTheOrigin = 5,
        AtTheEnd = 6
      };

      /// Initialize the segment with the vertices
      virtual void Initialize(const Vertex& origin, const Vertex& end) = 0;

      /// Initialize the vertices of the geometric object
      virtual void InitializeVertices(const unsigned int& numberOfVertices) = 0;
      /// Add a single vertex to the geometric object
      virtual void AddVertex(const Vertex& vertex) = 0;
      /// Add a list of vertices to the geometric object
      virtual void AddVertices(const vector<const Vertex*>& _vertices) = 0;

      /// @return The origin of the segment
      virtual const Vertex& Origin() const = 0;
      /// @return The end of the segment
      virtual const Vertex& End() const = 0;
      /// @return The tangent of the segment
      virtual const Vector3d& Tangent() const = 0;

      /// Invert the direction of the segment
      virtual void Flip() = 0;
      /// Computes the normalized tangent and stores it in the segment
      virtual void ComputeTangent() = 0;
      /// Computes the normalized tangent
      /// @param[out] _tangent : the computed tangent
      virtual Output::ExitCodes ComputeTangent(Vector3d& _tangent) const = 0;

      /// Transforms a coordinate curvilinear in a point on the segment line
      /// @param[in] curvilinearCoordinate : coordinate curvilinear
      /// @param[out] point : the point computed
      virtual void ComputePointOnLine(const double curvilinearCoordinate, Vertex& point) const = 0;

      /// Computes the position of a point respect to the segment
      /// @param[in] Vertex
      /// @param[in] toll
      /// @param[out] coordinateCurvilinear : the curvilinear coordinate of the point in the segment
      /// @warning Works only with 2D segment
      virtual ISegment::Position PointPosition(const Vertex& point, const double& tollerance) const = 0;
  };
}

#endif // ISEGMENT_HPP
