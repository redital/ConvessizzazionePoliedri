#ifndef INTERSECTORPOLYGONLINE_HPP
#define INTERSECTORPOLYGONLINE_HPP

#include "Output.hpp"
#include "Eigen"
#include "list"
#include "IPolygon.hpp"

using namespace std;
using namespace MainApplication;
using namespace Eigen;

namespace GeDiM
{
	class IntersectorPolygonLine;

	class IntersectorPolygonLine
	{
		public:

			enum TypeIntersection
			{
				NoIntersection = 0,
				Tangent = 1,
				Inside = 2,
				Boundary = 3,
			};

			enum IntersectionPosition
			{
				NoPosition = 0,
				EdgeVertex = 1,
				EdgeEdge = 2,
				VertexVertex = 3,
				EdgeVertices = 4,
				Vertex = 5,
			};

		private:

			const IPolygon* polygonPointer;

			const Vector3d* startPointPointer;
			const Vector3d* tangentPointer;
			int positionBoundaryEdge;
			TypeIntersection intersectionType;
			IntersectionPosition positionIntersection;
			double toleranceParallelism;
			double toleranceIntersection;

			vector<unsigned int> indexEdges;
			vector<unsigned int> indexVertices;
			vector<double> parametricCoordinates;

			const Output::ExitCodes Reset();
			const Output::ExitCodes ComputeIntersectionGenericCell();
			const Output::ExitCodes ComputeIntersectionGenericDomain();

		public:
			IntersectorPolygonLine();
			~IntersectorPolygonLine();

			void SetTolleranceIntersection(const double& _tolerance) { toleranceIntersection = _tolerance; }
			void SetTolleranceParallelism(const double& _tolerance) { toleranceParallelism = _tolerance; }
			const Output::ExitCodes ComputeIntersection();

			void SetPolygon(const IPolygon& _polygon) {polygonPointer = &_polygon;}
			const Output::ExitCodes SetLine(const Vector3d& startPoint, const Vector3d& tangent);

			const bool CheckIntersection() { return (intersectionType != NoIntersection && intersectionType != Tangent); }
			vector<double>& ParametricCoordinates() {return parametricCoordinates;}
			const TypeIntersection& IntersectionType() const { return intersectionType; }
			const IntersectionPosition& IntersectionPosition() const { return positionIntersection; }
			const int& PositionBoundaryEdge() const {return positionBoundaryEdge;}
			const vector<unsigned int>& IndexEdges() const { return indexEdges;}

			Vector3d IntersectionPoint(const unsigned int& position) {return *startPointPointer + parametricCoordinates[position] * *tangentPointer;}
	};
}

#endif // INTERSECTORPOLYGONLINE_HPPs

