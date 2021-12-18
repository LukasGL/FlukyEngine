#pragma once
#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

#include <memory>
#include <iostream>
#include <stdio.h>
#include "../World/TransformComponent.hpp"

namespace Fluky {

	class CameraComponent {

	public:

		void SetAt(float x, float y, float z){
			at.x = x;
			at.y = y;
			at.z = z;
		}

		void SetEye(float x, float y, float z) {
			eye.x = x;
			eye.y = y;
			eye.z = z;
		}

		void SetSpeed(float s) { cameraSpeed = s; }

		float GetAtX() { return at.x; }
		float GetAtY() { return at.y; }
		float GetAtZ() { return at.z; }

		float GetEyeX() { return eye.x; }
		float GetEyeY() { return eye.y; }
		float GetEyeZ() { return eye.z; }

		float GetMtxX() { return transf->GetLocation(0); }
		float GetMtxY() { return transf->GetLocation(1);}
		float GetMtxZ() { return transf->GetLocation(2); }

		float GetSpeed() { return cameraSpeed; }

		float* GetMatrix() {
			return transf->GetMatrix();
		}

		void Translate(float x, float y, float z) {
			transf->Translate(x, y, z);
		}

		void SetTranslation(float x, float y, float z) {
			transf->SetTranslation(x, y, z);
		}

		void RotateX(float angle) {
			transf->RotateX(angle);
		}
		void RotateY(float angle) {
			transf->RotateY(angle);
		}
		void RotateZ(float angle) {
			transf->RotateZ(angle);
		}
		void RotateXY(float angleX, float angleY) {
			transf->RotateXY(angleX, angleY);
		}
		void RotateXYZ(float angleX, float angleY, float angleZ) {
			transf->RotateXYZ(angleX, angleY, angleZ);
		}

	private:
		//float view[16];
		//float proj[16];

		float cameraSpeed = 1.f;

		TransformComponent* transf = new TransformComponent;

		Fluky::Vec3 at = { 0.0f, 0.0f,   0.0f };
		Fluky::Vec3 eye = { 0.0f, 0.0f, -5.0f };

	};

}

#endif