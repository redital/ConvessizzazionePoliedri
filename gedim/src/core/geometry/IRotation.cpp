#include "IRotation.hpp"
#include "Output.hpp"
#include "DefineNumbers.hpp"
namespace GeDiM
{
	// ***************************************************************************
	// IGenericDomainRotation Implementation
	// ***************************************************************************
	IRotation::IRotation()
	{
		rotation = NULL;
		originTranslation = NULL;
	}

	IRotation::IRotation(const IRotation& irotation)
	{
		if(irotation.rotation != NULL)
			rotation = new Matrix3d(*irotation.rotation);
		else
			rotation = NULL;
		if(irotation.originTranslation != NULL)
			originTranslation = new Vector3d(*irotation.originTranslation);
		else
			originTranslation = NULL;
	}
	IRotation::~IRotation()
	{
		rotation = NULL;
		originTranslation = NULL;
	}
	// ***************************************************************************
	Output::ExitCodes IRotation::RotateVertices(const vector<Vector3d>& verticesToRotate, vector<Vector3d>& rotatedVertices) const
	{
		const unsigned int& numVertices = verticesToRotate.size();

		rotatedVertices.clear();
		rotatedVertices.reserve(numVertices);

		for(unsigned int i = 0; i < numVertices; i++)
			rotatedVertices.push_back(RotatePoint(verticesToRotate[i]));

		return Output::Success;
	}
	// ***************************************************************************
	Vector3d IRotation::RotatePoint(const Vector3d& point, const bool& translation, const bool& inverse) const
	{
		if (originTranslation == NULL && rotation == NULL)
			return point;

		if (rotation == NULL)
		{
			if (inverse)
				return point + Translation();
			else
				return point - Translation();
		}

		if (originTranslation == NULL || translation == false)
		{
			if (inverse)
				return RotationMatrix() * point;
			else
				return RotationMatrix().transpose() * point;
		}

		if (inverse)
			return RotationMatrix() * point + Translation();
		else
			return RotationMatrix().transpose() * (point - Translation());
	}
	// ***************************************************************************
	Vector3d IRotation::RotatePointWithInput(const Vector3d& point, const Matrix3d& rotationMatrix, const Vector3d& translationVector, const bool& inverse) const
	{
		if (inverse)
			return rotationMatrix * point + translationVector;
		else
			return rotationMatrix.transpose() * (point - translationVector);
	}
  // ***************************************************************************
}
