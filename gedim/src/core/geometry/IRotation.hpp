#ifndef IROTATION_H
#define IROTATION_H

#include <vector>
#include <string>

#include "Eigen"
#include "Output.hpp"

using namespace std;
using namespace Eigen;
using namespace MainApplication;

namespace GeDiM
{
	class IRotation;

	class IRotation
	{
		protected:
			Matrix3d* rotation; ///< rotation matrix
			Vector3d* originTranslation; ///< origin point of the translation

		public:
			IRotation();
			IRotation(const IRotation& irotation);
			virtual ~IRotation();

			const Matrix3d& RotationMatrix() const { return *rotation; }
			const Vector3d& Translation() const { return *originTranslation; }
			Matrix3d& RotationMatrix() { return *rotation; }
			Vector3d& Translation() { return *originTranslation; }

			void SetRotationMatrix(const Matrix3d& _rotationMatrix) { rotation = new Matrix3d(_rotationMatrix); }
			void SetOriginTranslation(const Vector3d& _originTranslation) { originTranslation = new Vector3d(_originTranslation); }

			Output::ExitCodes RotateVertices(const vector<Vector3d>& verticesToRotate, vector<Vector3d>& rotatedVertices) const;
			Vector3d RotatePoint(const Vector3d& point, const bool& translation = true, const bool& inverse = false) const;
			Vector3d RotatePointWithInput(const Vector3d& point, const Matrix3d& rotationMatrix, const Vector3d& translationVector, const bool& inverse = false) const;
	};
}

#endif // GENERICDOMAIN_H
