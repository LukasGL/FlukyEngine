#pragma once
#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <bx/math.h>

namespace Fluky {

	class TransformComponent {

	public:
		const bx::Vec3& GetLocalScale() const {
			return localScale;
		}
		float* GetMatrix() {
			return mtx;
		}
		void Translate(bx::Vec3 translation) {
			mtx[12] += translation.x;
			mtx[13] += translation.y;
			mtx[14] += translation.z;
		}

		void SetTranslation(const bx::Vec3 translation) {
			mtx[12] = translation.x;
			mtx[13] = translation.y;
			mtx[14] = translation.z;
		}

		//void Scale(bx::Vec3 scale) {
		//	localScale = localScale * scale;
		//}

		void SetScale(const bx::Vec3& scale) {
			localScale = scale;
		}
		void RotateX(float angle) {
			bx::mtxRotateX(mtx, angle);
		}
		void RotateY(float angle) {
			bx::mtxRotateY(mtx, angle);
		}
		void RotateZ(float angle) {
			bx::mtxRotateZ(mtx, angle);
		}
		void RotateXY(float angleX, float angleY) {
			bx::mtxRotateXY(mtx, angleX, angleY);
		}
		void RotateXYZ(float angleX, float angleY, float angleZ) {
			bx::mtxRotateXYZ(mtx, angleX, angleY, angleZ);
		}

	private:
		float mtx[16];
		bx::Vec3 localScale;

	};



}
#endif