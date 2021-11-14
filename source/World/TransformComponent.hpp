#pragma once
#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP



#include <iostream>
#include <string>
#include <vector>
#include <memory>


namespace Fluky {

	class TransformComponent {

	public:

		friend class BoxComponent;

		float* GetMatrix() {
			return mtx;
		}

		void Translate(float x, float y, float z);

		void SetTranslation(float x, float y, float z);

		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void RotateXY(float angleX, float angleY);
		void RotateXYZ(float angleX, float angleY, float angleZ);

		void AddRotationXYZ(float angleX, float angleY, float angleZ);


		std::vector<float> Location = { 0.f, 0.f, 0.f };

	private:
		float mtx[16];


	};



}
#endif