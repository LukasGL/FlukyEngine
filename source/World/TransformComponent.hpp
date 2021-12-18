#pragma once
#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP



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
  /**
	 * Returns the transform values matrix
   * 
   * @return {float*}  : 
   */
		float* GetMatrix() {
			return mtx;
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


		std::vector<float> Location = { 0.f, 0.f, 0.f };

	private:

		float mtx[16];


	};



}
#endif