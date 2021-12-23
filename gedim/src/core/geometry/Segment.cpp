#include "Segment.hpp"

namespace GeDiM
{

	// ***************************************************************************
	Segment::Segment()
	{
		tangent = NULL;

		centroid = NULL;
		barycenter = NULL;
		measure = 0.0;
		squaredRadius = 0.0;
		radius = 0.0;
		vertices.reserve(2);
	}

	Segment::~Segment()
	{
		if(tangent != NULL)
			delete tangent;

		if(centroid != NULL)
			delete centroid;

		if(barycenter != NULL)
			delete barycenter;

		vertices.clear();
	}

	// ***************************************************************************
	Output::ExitCodes Segment::ComputeBarycenter(Vertex& _centroid) const
	{
		_centroid = (*vertices[0] + *vertices[1]) * 0.5;
		return Output::Success;
	}

	// ***************************************************************************
	Output::ExitCodes Segment::ComputeMeasure(double& _measure) const
	{
		_measure = (*vertices[1] - *vertices[0]).norm();
		return Output::Success;
	}

	// ***************************************************************************
	Output::ExitCodes Segment::ComputeTangent(Vector3d& _tangent) const
	{
		_tangent = *vertices[1] - *vertices[0];
    _tangent.normalize();
		return Output::Success;
	}

	// ***************************************************************************
	Output::ExitCodes Segment::ComputeRadius(double& _radius) const
	{
		_radius = (*vertices[1] - *vertices[0]).norm() * 0.5;
		return Output::Success;
	}

	// ***************************************************************************
	Output::ExitCodes Segment::ComputeSquaredRadius(double& _radiusSquared) const
	{
		_radiusSquared = (*vertices[1] - *vertices[0]).squaredNorm() * 0.25;
		return Output::Success;
	}

	// ***************************************************************************
	ISegment::Position Segment::PointPosition(const Vertex& point, const double& tollerance) const
	{
		Vector3d tangentVectorEdge;
		if(tangent == NULL)
			tangentVectorEdge = End() - Origin();
		else
			tangentVectorEdge = *tangent * measure;

		Vector3d tangentVectorDiff = point - Origin();
		double crossProd = tangentVectorEdge.x() * tangentVectorDiff.y() - tangentVectorDiff.x() * tangentVectorEdge.y();

		double coordinateCurvilinear = (tangentVectorEdge.dot(tangentVectorDiff)) / tangentVectorEdge.squaredNorm();

		if(crossProd > tollerance)
			return Position::AtTheLeft;
		if(crossProd < -tollerance)
			return Position::AtTheRight;
		if(coordinateCurvilinear < -tollerance)
			return Position::Behind;
		if(coordinateCurvilinear > 1.0 + tollerance)
			return Position::Beyond;
		if(abs(coordinateCurvilinear) < tollerance)
			return Position::AtTheOrigin;
		if(abs(coordinateCurvilinear) > 1.0 - tollerance)
			return Position::AtTheEnd;
		return Position::Between;
	}
}
