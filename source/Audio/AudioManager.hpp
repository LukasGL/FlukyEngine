#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP


#include <AL/al.h>
#include <AL/alc.h>
#include <cstdint>
#include <vector>

namespace Fluky {

	/**
	 * This class gives to the user the methods that will allow the management of the game audio
	   *
	 */
	class AudioManager {
	public:
		/**
		 * initialize all the important values
		   *
		 */
		int StartUp() noexcept;


		/**
		 * Sets free all the resources
		   *
		 */
		int ShutDown() noexcept;



		/**
		   * what to do when the game updates
		 *
		 */
		void Update();

		/**
		   * Plays a .wav file
		 *
		 * @param  {char*} file :
		 * @return {int}        :
		 */
		int Play(const char* file, ALuint& source, ALuint& buffer);
	private:

		std::vector<float> Position = { 0.f, 0.f, 0.f };

	};
}
#endif