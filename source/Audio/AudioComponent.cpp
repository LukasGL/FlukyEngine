#include "AudioComponent.hpp"

#include <iostream>
#include <cassert>
#include <vector>


namespace Fluky {


	int AudioComponent::Play(const char* file) {
		
		
		//p_sc->audioManager.Play(file, source, buffer);
		return p_sc->audioManager.Play(file, source, buffer);
	}

	int AudioComponent::ShutDown() noexcept
	{
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
		return 1;
	}

	void AudioComponent::SetPitch(float p) {
		Pitch = p;
	}

	void AudioComponent::SetPosition(float x, float y, float z){
		Position = {x, y, z};
	}

	void AudioComponent::Update() {
		alSource3f(source, AL_POSITION, Position[0], Position[1], Position[2]);
	}

	int AudioComponent::StartUp(Scene& sc)
	{

		std::vector<ALuint> sources = sc.sources;
		std::vector<ALuint> buffers = sc.buffers;


		alGenSources((ALuint)sc.sources.size()+1, &source);

		source = (ALuint)sc.sources.size() + 1;

		alSourcef(source, AL_PITCH, Pitch);
		alSourcef(source, AL_GAIN, 1);
		alSource3f(source, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		alSourcei(source, AL_LOOPING, AL_TRUE);

		sc.sources.push_back(source);

		if (sc.buffers.size() < 1) {
			StartUpBuffer(sc);
		}


		buffer = (ALuint)1;

		p_sc = &sc;

		return 1;
	}

	int AudioComponent::StartUpSource(ALuint source) noexcept
	{
		alGenSources((ALuint)1, &source);

		alSourcef(source, AL_PITCH, 1);
		alSourcef(source, AL_GAIN, 1);
		alSource3f(source, AL_POSITION, 0.f, 0.f, 0.f);
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		alSourcei(source, AL_LOOPING, AL_TRUE);

		alGenBuffers((ALuint)1, &buffer);

		return 1;
	}

	int AudioComponent::StartUpBuffer(Scene& sc) noexcept
	{

		alGenBuffers((ALuint)1, &buffer);

		sc.buffers.push_back(buffer);

		return 1;
	}
}