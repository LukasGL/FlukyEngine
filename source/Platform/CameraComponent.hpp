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

		float GetAt() {
			return at.x, at.y, at.z;
		}

		float GetEye() {
			return eye.x, eye.y, eye.z;
		}

	private:
		//float view[16];
		//float proj[16];

		Fluky::Vec3 at = { 0.0f, 0.0f,   0.0f };
		Fluky::Vec3 eye = { 0.0f, 0.0f, -5.0f };

	};

}

#endif