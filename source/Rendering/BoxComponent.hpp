#pragma once
#ifndef BOXCOMPONENT_HPP
#define BOXCOMPONENT_HPP

#include "../World/Component.hpp"

namespace Fluky {
	/**
	 * Class that has to render the figures the user wants
	 */
	class BoxComponent : Component {

	public:
		friend class World;
		/**
		 * BoxComponent initializer
		   *
		 * @return {int}  :
		 */
		int Init();

  /**
   * BoxComponent destructor
   * 
   */
		~BoxComponent();
		/**
		 * Funciton called in every iteration of the main loop
		 */
		void Update(class TransformComponent& transform) noexcept;

		unsigned int counter;

		bool initialized = false;

	};

}
#endif