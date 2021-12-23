#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Eigen"

using namespace  Eigen;

namespace GeDiM
{
	class Vertex;

	class Vertex : public Vector3d
	{
		protected:
			unsigned int id;
			unsigned int globalId;


		public:
			Vertex(): Vector3d() { id = 0;}
			Vertex(const double& x): Vector3d(x, 0.0, 0.0) { id = 0; }
			Vertex(const double& x, const double& y) : Vector3d(x, y, 0.0) { id = 0; }
			Vertex(const double& x, const double& y, const double& z): Vector3d(x, y, z) { id = 0; }

			virtual ~Vertex() {};
			// This constructor allows you to construct MyVectorType from Eigen expressions
			template<typename OtherDerived>
			Vertex(const MatrixBase<OtherDerived>& other)
				: Vector3d(other)
			{ }
			// This method allows you to assign Eigen expressions to MyVectorType
			template<typename OtherDerived>
			Vertex& operator=(const MatrixBase <OtherDerived>& other)
			{
				this->Vector3d::operator=(other);
				return *this;
			}

			void SetGlobalId(const unsigned int& _globalId) { globalId = _globalId; }
			void SetId(const unsigned int& _id) { id = _id; }

            bool IsEqual(Vertex vertice) const
			{
                double tolerance = 1e-14;
                if( (this->x() - vertice.x())*(this->x() - vertice.x()) +
                    (this->y() - vertice.y())*(this->y() - vertice.y()) +
                    (this->z() - vertice.z())*(this->z() - vertice.z()) <= tolerance*tolerance){
                    return true;
                    }
                else{
                    return false;
                }
			}
	};

}


#endif //VERTEX_HPP
