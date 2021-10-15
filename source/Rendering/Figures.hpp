#pragma once
#ifndef FIGURES_HPP
#define FIGURES_HPP


namespace Fluky {
 /**
  * Class that has to render the figures the user wants
  */
	class Figures {

	public:
		friend class World;
  /**
   * Figures initializer
	 * 
   * @return {int}  : 
   */
		int Init();

		~Figures();
  /**
   * Funciton called in every iteration of the main loop
   */
		void Update(float sizeX, float sizeY) noexcept;

		unsigned int counter;

		/*void StartUp() noexcept;
		void ShutDown() noexcept;
		void Update() noexcept;*/

	};

}
#endif