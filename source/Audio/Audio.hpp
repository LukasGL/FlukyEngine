#pragma once
#include <cstdint>
#ifndef AUDIO_HPP
#define AUDIO_HPP

namespace Fluky {
	

	class Audio {
	public:
		/*
		* Función llamada por el motor que inicializa el sistema de audio, el cual es capaz de reproducir channels audios simultaneamente.
		*/
		
		int StartUp() noexcept;

		/*
		* Libera todos los recuros mantenidos por el sistema de audio, esta función es llamada durante el proceso de cierre del motor.
		*/
		int ShutDown() noexcept;

		/*
		* Función llamada cada iteración del mainloop del motor
		*/
		void Update() noexcept;

		/*
		* Retorna el volumen global o maestro del sistema de audio
		*/
		float GetMasterVolume() const noexcept;

		/*
		* Ajusta el volumen global o maestro del sistema de audio al valor entregado. Internamente el rango del valor es restringido a
		* valores entre 0.0f y 1.0f.
		*/
		void SetMasterVolume(float volume) noexcept;

		/*
		* Crea una FreeAudioSource (fuente libre) la cual sera responsable de intertar reproducir el audioclip entregado con la posición,
		* volumen, tono, radio y prioridad tambien entregados. Esta funcion suele ser llamada por medio de la interfaz de la clase World, cuando
		* el usuerio quiere reproducir un audio3D que no este unido como component a un GameObject.
		*/
		/*void PlayAudioClip3D(std::shared_ptr<AudioClip> audioClip,
			const glm::vec3& position,
			float volume,
			float pitch,
			float radius,
			AudioSourcePriority priority
		);*/
		/*
		* Crea una FreeAudioSource (fuente libre) la cual sera responsable de intertar reproducir el audioclip entregado con el volumen,
		* tono y prioridad tambien entregados. Esta funcion suele ser llamada por medio de la interfaz de la clase World, cuando
		* el usuerio quiere reproducir un audio2D que no este unido como component a un GameObject.
		*/
		/*void PlayAudioClip2D(std::shared_ptr<AudioClip> audioClip,
			float volume,
			float pitch,
			AudioSourcePriority priority);*/

		/*
		* Libera la fuente de OpenAL que se encuentra en la posición index dentro del arreglo de estas mismas. Esta función es llamada
		* cada vez que una componente AudioSourceComponent es destruida.
		*/
		void RemoveOpenALSource(uint32_t index) noexcept;

		/*
		* Libera todas las fuentes de OpenAL
		*/
		void ClearSources() noexcept;

		int Play(const char* file);
	private:

		
	};
}
#endif