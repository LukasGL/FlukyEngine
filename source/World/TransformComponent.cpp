#include "TransformComponent.hpp"


#include <bx/bx.h>
#include <bx/math.h>
#include <iostream>


Fluky::TransformComponent PhysMtxtoTransfMtx(btTransform mtx_in) {
	Fluky::TransformComponent mtx_out;
	btMatrix3x3 m = mtx_in.getBasis();
	float m_out[16] = { 0.f };
	int counter = 0;
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m_out[counter] = m[i][j];
			counter++;
		}
	}*/
	m_out[0] = m[0][0]; //
	m_out[1] = m[0][1];
	m_out[2] = m[0][2];
	m_out[4] = m[1][0];
	m_out[5] = m[1][1]; //
	m_out[6] = m[1][2];
	m_out[8] = m[2][0];
	m_out[9] = m[2][1];
	m_out[10] = m[2][2]; //

	m_out[12] = mtx_in.getOrigin().getX();
	m_out[13] = mtx_in.getOrigin().getY();
	m_out[14] = mtx_in.getOrigin().getZ();

	m_out[15] = 1.f;

	mtx_out.SetMatrix(m_out);

	mtx_out.SetTranslation(m_out[12], m_out[13], m_out[14]);
	return mtx_out;
}

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
		mtx[12] = Location[0];
		mtx[13] = Location[1];
		mtx[14] = Location[2];
	}

}