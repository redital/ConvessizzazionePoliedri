#include "IntersectorPolygonLine.hpp"
#include "Intersector1D1D.hpp"
#include "Polygon.hpp"

namespace GeDiM
{

	// ***************************************************************************
	IntersectorPolygonLine::IntersectorPolygonLine()
	{
		polygonPointer = NULL;
		startPointPointer = NULL;
		tangentPointer = NULL;
		toleranceParallelism = 1.0e-07;
		toleranceIntersection = 1.0e-07;
		indexEdges.reserve(2);
		indexVertices.reserve(2);
		parametricCoordinates.resize(2, 0.0);
		positionBoundaryEdge = -1;
	}

	IntersectorPolygonLine::~IntersectorPolygonLine()
	{

	}

	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::ComputeIntersection()
	{
		if(polygonPointer == NULL )
		{
			Output::PrintErrorMessage("Set a polygon in Intersector ", false);
			return Output::GenericError;
		}
		return ComputeIntersectionGenericDomain();
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::ComputeIntersectionGenericDomain()
	{
		if(polygonPointer->NumberOfRotatedVertices() == 0)
		{
			Output::PrintErrorMessage("Compute rotated vertices", true);
			return Output::GenericError;
		}

		Vector3d tangentVectorEdge, tangentVectorDifference;
		Intersector1D1D intersect;
		unsigned int counterIntersection = 0;
		bool continueIter = true;
		double toll = toleranceIntersection * toleranceIntersection;
		const Polygon& polygon = static_cast<const Polygon&>(*polygonPointer);
		const Vector3d& tangentVectorSegment = *tangentPointer;
		const Vector3d& startPoint = *startPointPointer;

		intersect.SetFirstTangentVector(tangentVectorSegment);
		vector<bool> checkEdges(polygon.NumberOfSegments(), false);
		for(unsigned int numPnt = 0; (numPnt < polygon.NumberOfRotatedVertices() && continueIter); numPnt++)
		{
			if(checkEdges[numPnt])
				continue;

			const unsigned int& indexFirstVert = numPnt;
			const unsigned int& indexSecondVert = (numPnt + 1)%(polygon.NumberOfRotatedVertices());
			const Vector3d& firstVert = polygon.RotatedVertex(indexFirstVert);
			const Vector3d& secondVert = polygon.RotatedVertex(indexSecondVert);

			tangentVectorEdge = secondVert - firstVert;
			tangentVectorDifference = firstVert - startPoint;
			intersect.SetSecondTangentVector(tangentVectorEdge);
			intersect.ComputeIntersectionEdges(tangentVectorSegment, tangentVectorEdge, tangentVectorDifference);

			double normVectorSegment = 1.0/tangentVectorSegment.norm();
			const unsigned int& type = intersect.TypeIntersection();
			checkEdges[numPnt] = true;
			switch(type)
			{
				case Intersector1D1D::IntersectionParallelOnLine:
				case Intersector1D1D::IntersectionParallelOnSegment:
					parametricCoordinates[0] = intersect.FirstParametricCoordinate();
					parametricCoordinates[1] = intersect.SecondParametricCoordinate();
					indexEdges.clear();
					indexVertices.clear();
					indexEdges.push_back(numPnt);
					indexVertices.push_back(indexFirstVert);
					indexVertices.push_back(indexSecondVert);
					intersectionType = TypeIntersection::Boundary;
					continueIter = false;
					counterIntersection = 2;
					break;

				case Intersector1D1D::IntersectionOnLine:
				case Intersector1D1D::IntersectionOnSegment:
					switch(intersect.PositionIntersectionInSecondEdge())
					{
						case Intersector1D1D::Inside:
							parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
							indexEdges.push_back(numPnt);
							intersectionType = TypeIntersection::Inside;
							break;
						case Intersector1D1D::Begin:
						{
							if(counterIntersection)
							{
								parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
								indexEdges.push_back(numPnt);
								indexVertices.push_back(indexFirstVert);
								continueIter = false;
							}
							else
							{
								unsigned int numEdgPrevious = (numPnt == 0)? polygon.NumberOfVertices() - 1 : numPnt -1;
								const unsigned int& indexFirstVertPrev = numEdgPrevious;
								const unsigned int& indexSecondVertPrev = numPnt;
								const Vector3d& firstVertPrev = polygon.RotatedVertex(indexFirstVertPrev);
								const Vector3d& secondVertPrev = polygon.RotatedVertex(indexSecondVertPrev);
								Vector3d tangentVectorEdgePrev = firstVertPrev - secondVertPrev;
								Vector3d tangentVectorSegment2(tangentVectorSegment);
								if(tangentVectorSegment2(1) < toll)
									tangentVectorSegment2 = -tangentVectorSegment2;

								double scalar1 = tangentVectorEdge.dot(tangentVectorEdgePrev / tangentVectorEdgePrev.norm());
								double scalar2 = tangentVectorEdge.dot(tangentVectorSegment2 * normVectorSegment);

								if( abs(scalar1 - scalar2) < toll || abs(scalar1 + scalar2) < toll)
								{
									double scalar3 = abs(tangentVectorEdgePrev.dot(tangentVectorSegment));
									indexVertices.push_back(indexFirstVert);
									if(scalar3 > toll)
									{
										parametricCoordinates[0] = 0.0;
										parametricCoordinates[1] = 1.0;
										indexVertices.push_back(indexFirstVertPrev);
									}
									else
									{
										parametricCoordinates[0] = 0.0;
										indexVertices.push_back(indexSecondVertPrev);
									}
									indexEdges.push_back(numEdgPrevious);
									positionIntersection = IntersectorPolygonLine::VertexVertex;
									intersectionType = TypeIntersection::Boundary;
									continueIter = false;
									counterIntersection = 2;
								}
								else if( scalar1 < scalar2)
								{
									parametricCoordinates[counterIntersection++] = intersect.FirstParametricCoordinate();
									indexEdges.push_back(numPnt);
									indexVertices.push_back(indexFirstVert);
									intersectionType = TypeIntersection::Inside;
								}
								checkEdges[numEdgPrevious] = true;
							}
						}
							break;
						default:
							break;
					}
			}

			if(intersectionType == TypeIntersection::Boundary && counterIntersection == 2)
			{
				positionBoundaryEdge = numPnt;
			}
		}

		if(counterIntersection == 2)
		{
			if(indexVertices.size() == 2)
			{
				if(indexVertices[0] == indexVertices[1])
				{
					intersectionType = TypeIntersection::Tangent;
					positionIntersection = IntersectorPolygonLine::Vertex;
				}
				else
					positionIntersection = IntersectorPolygonLine::VertexVertex;
			}
			else if(indexEdges.size() == 2)
			{
				if(indexVertices.size() == 1)
					positionIntersection = IntersectorPolygonLine::EdgeVertex;
				else
					positionIntersection = IntersectorPolygonLine::EdgeEdge;
			}

			if(parametricCoordinates[0] > parametricCoordinates[1])
			{
				double temp = parametricCoordinates[0];
				parametricCoordinates[0] = parametricCoordinates[1];
				parametricCoordinates[1] = temp;
			}
		}
		else
		{
			intersectionType = TypeIntersection::Tangent;
			positionIntersection = IntersectorPolygonLine::Vertex;
		}
		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::Reset()
	{
		parametricCoordinates[0] = 0.0;
		parametricCoordinates[1] = 0.0;
		indexEdges.clear();
		indexVertices.clear();
		intersectionType = NoIntersection;
		positionIntersection = NoPosition;
		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes IntersectorPolygonLine::SetLine(const Vector3d& startPoint, const Vector3d& tangent)
	{
		Reset();
		startPointPointer = &startPoint;
		tangentPointer = &tangent;
		return Output::Success;
	}

	// ***************************************************************************
}
