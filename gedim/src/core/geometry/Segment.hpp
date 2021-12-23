#ifndef SEGMENT_HPP
#define SEGMENT_HPP
/**
 * @file
 * @brief Qui scrivere una descrizione del file
 * @brief
 * @author Alessandro D'Auria
 * @version 1.0
 */

#include "ISegment.hpp"
#include "GeometricObject.hpp"

using namespace std;
using namespace Eigen;
using namespace MainApplication;

namespace GeDiM
{
  class Segment;

  class Segment : public GeometricObject, public ISegment
  {
    protected:
      vector<const Vertex*> vertices; ///< Array of domain vertices
      Vector3d* tangent; ///< Pointer to the normalized vector tangent

    public:
      Segment();
      Segment(const unsigned int& _id) : Segment() { id = _id; globalId = id; }
      virtual ~Segment();

      inline void Initialize(const Vertex& origin, const Vertex& end) { vertices.push_back(&origin); vertices.push_back(&end); }
      inline void Flip() { const Vertex* tempPoint = vertices[0]; vertices[0] = vertices[1]; vertices[1] = tempPoint; }

      inline void InitializeVertices(const unsigned int& numberOfVertices) { vertices.reserve(numberOfVertices); }
      inline void AddVertex(const Vertex& vertex) { vertices.push_back(&vertex); }
      inline void AddVertices(const vector<const Vertex*>& _vertices) { vertices = _vertices; }

      inline unsigned int NumberOfVertices() const { return vertices.size(); }
      inline const Vertex& GetVertex(const unsigned int& position) const { return *vertices[position]; }
      inline const vector<const Vertex*>& Vertices() const { return vertices; }

      ///GETTER
      inline unsigned int Dimension() const { return 1; }
      inline const Vertex& Origin() const { return *vertices[0]; }
      inline const Vertex& End() const { return *vertices[1]; }
      inline const Vector3d& Tangent() const { return *tangent; }

      ///Compute Tangent
      /// \brief Compute the normalized tangent of the segment and save inside the object
      inline void ComputeTangent() { if (tangent == NULL) tangent = new Vector3d (3.0,1.0,5.0); ComputeTangent(*tangent); }
      ///Compute Tangent
      /// \brief Compute the normalized tangent of the segment and save the result in the output
      /// \param[out] _tangent is a Vector3d where it will be saved the tangent of the segment
      Output::ExitCodes ComputeTangent(Vector3d& _tangent) const;

      ///Compute Point On line
      /// \brief Transform in a Point on line given a coordinate curvilinear
      /// @param[in] coordinate curvilinear
      /// @param[out] point on the line at the parametric coordinate given in input
      void ComputePointOnLine(const double curvilinearCoordinate, Vertex& point) const { point = *tangent * curvilinearCoordinate * measure; point.noalias() += *vertices[0]; }

      ///Compute Centroid
      /// \brief Compute the centroid of the edge and save inside the object
      Output::ExitCodes ComputeBarycenter() { return ComputeBarycenter(*barycenter); }
      Output::ExitCodes ComputeBarycenter(Vertex& _barycenter) const;

      ///Compute Centroid
      /// \brief Compute the centroid of the edge and save inside the object
      Output::ExitCodes ComputeCentroid() { return ComputeBarycenter(*centroid); }
      Output::ExitCodes ComputeCentroid(Vertex& _centroid) const {return ComputeBarycenter(_centroid); }

      ///Compute Measure
      /// \brief Compute the length of the edge and save inside the object
      Output::ExitCodes ComputeMeasure() { return ComputeMeasure(measure); }
      Output::ExitCodes ComputeMeasure(double& _measure) const;

      ///Compute radius
      /// \brief Compute the radius of the edge and save inside the object
      Output::ExitCodes ComputeRadius() { return ComputeRadius(radius); }
      Output::ExitCodes ComputeRadius(double& _radius) const;

      ///Compute squared radius
      /// \brief Compute the squared radius of the edge and save inside the object
      Output::ExitCodes ComputeSquaredRadius() { return ComputeSquaredRadius(squaredRadius); }
      Output::ExitCodes ComputeSquaredRadius(double& _radiusSquared) const;

      ///\brief Compute the position of a point given in input respect to the segment
      /// \param[in] Vertex
      /// \param[in] toll set to a default value = 1.0E-7
      /// \warning It works only with 2D Segment
      ISegment::Position PointPosition(const Vertex& point, const double& tollerance = 1e-7) const;
  };
}
#endif //SEGMENT_HPP
