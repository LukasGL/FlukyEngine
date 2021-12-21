#pragma once
#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP



#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Fluky {
	struct Vec3 {
		float x;
		float y;
		float z;
	};
}



namespace Fluky {

	

	/**
	 * Class in charge of define the transform component
	 */ 
	class TransformComponent {

	public:

		friend class BoxComponent;

		TransformComponent operator + (TransformComponent tr2) {
			TransformComponent tr3;
			for (int i = 0; i < 15; i++) {
				tr3.mtx[i] = this->mtx[i] + tr2.mtx[i];
			}

			tr3.Location[0] = tr3.mtx[12];
			tr3.Location[1] = tr3.mtx[13];
			tr3.Location[2] = tr3.mtx[14];

			return tr3;
		}

  /**
	 * Returns the transform values matrix
   * 
   * @return {float*}  : 
   */
		float* GetMatrix() {
			return mtx;
		}

		void SetMatrix(float mtx_in[16]) {
			for (int i = 0; i < 16; i++) {
				mtx[i] = mtx_in[i];
			}
		}
  /**
	 * Returns the location of the component
   * 
   * @param  {int} i  : 
   * @return {float}  : 
   */
		float GetLocation(int i) {
			return Location[i];
		}
  /**
	 * Translates the component
   * 
   * @param  {float} x : 
   * @param  {float} y : 
   * @param  {float} z : 
   */
		void Translate(float x, float y, float z);
  /**
	 * Sets the position of the component
   * 
   * @param  {float} x : 
   * @param  {float} y : 
   * @param  {float} z : 
   */
		void SetTranslation(float x, float y, float z);
  /**
   * Rotates the component in X axis
   * @param  {float} angle : 
   */
		void RotateX(float angle);
  /**
   * Rotates the component in Y axis
   * @param  {float} angle : 
   */
		void RotateY(float angle);
		/**
   * Rotates the component in Z axis
   * @param  {float} angle : 
   */
		void RotateZ(float angle);
	
  /**
   * Rotates the component in X axis and Y axis
   * @param  {float} angleX : 
   * @param  {float} angleY : 
   */
		void RotateXY(float angleX, float angleY);
	
  /**
   * Rotates the component in X axis, Y axis and Z axis
   * @param  {float} angleX : 
   * @param  {float} angleY : 
   * @param  {float} angleZ : 
   */
		void RotateXYZ(float angleX, float angleY, float angleZ);
  /**
   * Adds a certain quantity of Rotation to the component
   * @param  {float} angleX : 
   * @param  {float} angleY : 
   * @param  {float} angleZ : 
   */
		void AddRotationXYZ(float angleX, float angleY, float angleZ);

		void ScaleMtx(Fluky::Vec3 scale);


		std::vector<float> Location = { 0.f, 0.f, 0.f };

	private:

		float mtx[16];


	};



}

Fluky::TransformComponent PhysMtxtoTransfMtx(btTransform mtx_in);
#endif