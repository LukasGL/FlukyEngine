#pragma once
#ifndef AUDIOCOMPONENT_HPP
#define AUDIOCOMPONENT_HPP


#include <AL/al.h>
#include <AL/alc.h>
#include <cstdint>
#include <vector>
#include "../World/Scene.hpp"
#include "AudioManager.hpp"

namespace Fluky {

	/**
	 * This class gives to the user the methods that will allow the management of the game audio
	   *
	 */
	class AudioComponent {
	public:
		/**
		 * initialize all the important values
		   *
		 */
		int StartUp(Scene& sc);

		int StartUpSource(ALuint source) noexcept;

		int StartUpBuffer(Scene& sc) noexcept;


		/**
		 * Sets free all the resources
		   *
		 */
		int ShutDown() noexcept;


		void SetPosition(float x, float y, float z);


		/**
		   * what to do when the game updates
		 *
		 */
		void Update();


		/**
		 * Returns the master volume
		   *
		 */
		float GetMasterVolume() const noexcept;


		/**
		 * Sets the master volume
		   *
		 */
		void SetMasterVolume(float volume) noexcept;


		/**
		 * Removes OpenAL source and it's called when the audio system is destroyed
		   *
		 */
		void RemoveOpenALSource(uint32_t index) noexcept;


		/**
		   * Clear all the sources of the audio system
		 *
		 */
		void ClearSources() noexcept;
		/**
		   * Plays a .wav file
		 *
		 * @param  {char*} file :
		 * @return {int}        :
		 */
		int Play(const char* file);
	private:

		std::vector<float> Position = {0.f, 0.f, 0.f};

		ALuint source;
		ALuint buffer = (ALuint)1;

		Scene* p_sc;

	};
}
#endif