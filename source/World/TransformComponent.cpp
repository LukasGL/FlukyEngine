#include "TransformComponent.hpp"


#include <bx/bx.h>
#include <bx/math.h>

namespace Fluky {

	void TransformComponent::Translate(float x, float y, float z) {
		mtx[12] += x;
		mtx[13] += y;
		mtx[14] += z;
	}

	void TransformComponent::SetTranslation(float x, float y, float z) {
		mtx[12] = x;
		mtx[13] = y;
		mtx[14] = z;
	}

	void TransformComponent::RotateX(float angle) {
		bx::mtxRotateX(mtx, angle);
	}
	void TransformComponent::RotateY(float angle) {
		bx::mtxRotateY(mtx, angle);
	}
	void TransformComponent::RotateZ(float angle) {
		bx::mtxRotateZ(mtx, angle);
	}
	void TransformComponent::RotateXY(float angleX, float angleY) {
		bx::mtxRotateXY(mtx, angleX, angleY);
	}
	void TransformComponent::RotateXYZ(float angleX, float angleY, float angleZ) {
		bx::mtxRotateXYZ(mtx, angleX, angleY, angleZ);
	}

	void TransformComponent::AddRotationXYZ(float angleX, float angleY, float angleZ)
	{
	}

}