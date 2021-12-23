#ifndef IGEOMETRICOBJECT_HPP
#define IGEOMETRICOBJECT_HPP

#include <vector>

#include "Output.hpp"
#include "Vertex.hpp"

using namespace std;
using namespace MainApplication;

namespace GeDiM
{
  class IGeometricObject
  {
    public:
      virtual ~IGeometricObject() { }

      /// Set the global Id of the geometric object
      virtual void SetGlobalId(const unsigned int& _globalId) = 0;
      /// Set the Id of the geometric object
      virtual void SetId(const unsigned int& _id) = 0;

      /// @return The global Id of the geometric object
      virtual const unsigned int& GlobalId() = 0;
      /// @return The Id of the geometric object
      virtual const unsigned int& Id() = 0;

      /// @return The measure of the geometric object
      virtual const double& Measure() const = 0;
      /// @return The centroid of the geometric object
      virtual const Vertex& Centroid() const = 0;
      /// @return The radius of the geometric object
      virtual const double& Radius() const = 0;
      /// @return The squared radius of the geometric object
      virtual const double& SquaredRadius() const = 0;
      /// @return The total number of vertices of the geometric object
      virtual unsigned int NumberOfVertices() const = 0;
      /// @return The vertex at position p of the geometric object
      virtual const Vertex& GetVertex(const unsigned int& position) const = 0;
      /// @return The list of vertices of the geometric object
      virtual const vector<const Vertex*>& Vertices() const = 0;
      /// @return The barycenter of the geometric object
      virtual const Vertex& Barycenter() const = 0;
      /// @return The dimension of the geometric object
      virtual unsigned int Dimension() const = 0;

      /// Computes the barycenter and stores it in the geometric object
      virtual Output::ExitCodes ComputeBarycenter() = 0;
      /// Computes the barycenter of the geometric object
      /// @param[out] _barycenter : the computed barycenter
      virtual Output::ExitCodes ComputeBarycenter(Vertex& _barycenter) const = 0;

      /// Computes the centroid and stores it in the geometric object
      virtual Output::ExitCodes ComputeCentroid() = 0;
      /// Computes the centroid of the geometric object
      /// @param[out] _centroid : the centroid barycenter
      virtual Output::ExitCodes ComputeCentroid(Vertex& _centroid) const = 0;

      /// Computes the measure and stores it in the geometric object
      virtual Output::ExitCodes ComputeMeasure() = 0;
      /// Computes the measure of the geometric object
      /// @param[out] _measure : the measure barycenter
      virtual Output::ExitCodes ComputeMeasure(double& measure) const = 0;

      /// Computes the radius and stores it in the geometric object
      virtual Output::ExitCodes ComputeRadius() = 0;
      /// Computes the radius of the geometric object
      /// @param[out] _radius : the radius barycente
      virtual Output::ExitCodes ComputeRadius(double& _radius) const = 0;

      /// Computes the squared radius and stores it in the geometric object
      virtual Output::ExitCodes ComputeSquaredRadius() = 0;
      /// Computes the squared radius of the geometric object
      /// @param[out] _radiusSquared : the squared radius barycente
      virtual Output::ExitCodes ComputeSquaredRadius(double& _radiusSquared) const = 0;
  };
}

#endif // IGEOMETRICOBJECT_HPP
