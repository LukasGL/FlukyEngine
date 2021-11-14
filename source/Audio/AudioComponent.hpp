#pragma once
#include <cstdint>
#ifndef AUDIO_HPP
#define AUDIO_HPP

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
		void Update() noexcept;


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


	};
}
#endif