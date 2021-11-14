#include "TransformComponent.hpp"


#include <bx/bx.h>
#include <bx/math.h>
#include <iostream>

namespace Fluky {

	void TransformComponent::Translate(float x, float y, float z) {
		mtx[12] = x;
		mtx[13] = y;
		mtx[14] = z;
		Location = {x, y, z};
	}

	void TransformComponent::SetTranslation(float x, float y, float z) {
		mtx[12] = x;
		mtx[13] = y;
		mtx[14] = z;
		Location = {x, y, z};
	}

	void TransformComponent::RotateX(float angle) {
		bx::mtxRotateX(mtx, angle);
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}
	void TransformComponent::RotateY(float angle) {
		bx::mtxRotateY(mtx, angle);
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}
	void TransformComponent::RotateZ(float angle) {
		bx::mtxRotateZ(mtx, angle);
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}
	void TransformComponent::RotateXY(float angleX, float angleY) {
		bx::mtxRotateXY(mtx, angleX, angleY);
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}
	void TransformComponent::RotateXYZ(float angleX, float angleY, float angleZ) {
		bx::mtxRotateXYZ(mtx, angleX, angleY, angleZ);
		std::cout << Location[0] << " caca" << std::endl;
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}

}