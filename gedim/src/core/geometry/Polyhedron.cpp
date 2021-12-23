#include "Polyhedron.hpp"
#include "DefineNumbers.hpp"

namespace GeDiM
{

	Polyhedron::Polyhedron()
	{
		barycenter = NULL;
		centroid = NULL;
		measure = 0.0;
		squaredRadius = 0.0;
		radius = 0.0;
		aspectRatio = 0.0;
	}

	Polyhedron::~Polyhedron()
	{
		if(centroid != NULL)
			delete centroid;

		if(barycenter != NULL)
			delete barycenter;

		vertices.clear();
		segments.clear();
		faces.clear();
	}


}
