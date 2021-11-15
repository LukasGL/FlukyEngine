#include "AudioComponent.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

static void list_audio_devices(const ALCchar* devices)
{
	const ALCchar* device = devices, * next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}

bool load_wav_file(const char* audiofile, ALuint bufferId)
{
	/* loading the wav file to OpenAL */
	struct WavData {
		unsigned int channels = 0;
		unsigned int sampleRate = 0;
		drwav_uint64 totalPCMFrameCount = 0;
		std::vector<uint16_t> pcmData;
		drwav_uint64 GetTotalSamples() const { return totalPCMFrameCount * channels; }
	};

	/*
	* Primero se cargan los datos del archivo ubicado en audioFilePath
	* usando la libreria drwav (https://github.com/mackron/dr_libs)
	*/

	WavData audioData;
	drwav_int16* sampleData = drwav_open_file_and_read_pcm_frames_s16(
		audiofile,
		&audioData.channels,
		&audioData.sampleRate,
		&audioData.totalPCMFrameCount,
		nullptr);

	if (!sampleData)
	{
		std::cerr << "Audio Clip Error: Failed to load file " << audiofile << std::endl;
		drwav_free(sampleData, nullptr);
		return false;
	}
	else if (audioData.GetTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max()))
	{
		std::cerr << "Audio Clip Error: File " << audiofile << " is to big to be loaded." << std::endl;
		drwav_free(sampleData, nullptr);
		return false;
	}

	/*at this point, the wav file is correctly loaded */

	//Si la carga usando dr_wav fue exitosa se comienza el transpaso de estos datos a OpenAL.
	audioData.pcmData.resize(size_t(audioData.GetTotalSamples()));

	//Primero se copian todos los datos a un vector de uint16_t, para luego liberar los datos recien copiados.
	std::memcpy(audioData.pcmData.data(), sampleData, audioData.pcmData.size() * 2);
	drwav_free(sampleData, nullptr);

	assert(bufferId != 0);

	alBufferData(
		bufferId,
		audioData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
		audioData.pcmData.data(),
		audioData.pcmData.size() * 2,
		audioData.sampleRate);

	/* end loading wav to OpenAL */
}

namespace Fluky {


	ALuint source;
	ALuint buffer;
	ALCcontext* context;

	int AudioComponent::Play(const char* file) {
		if (!load_wav_file(file, buffer)) return -1;

		std::cout << "wav file loaded correctly" << std::endl;

		alSource3i(source, AL_POSITION, Position[0], Position[1], Position[2]);
		/* Binding the buffer with the data to source */
		alSourcei(source, AL_BUFFER, buffer);

		/* Playing the source */
		alSourcePlay(source);
	}

	int AudioComponent::ShutDown() noexcept
	{
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return 1;
	}

	void AudioComponent::SetPosition(float x, float y, float z){
		Position = {x, y, z};
	}

	void AudioComponent::Update() {
		alSource3f(source, AL_POSITION, Position[0], Position[1], Position[2]);
		
	}

	int AudioComponent::StartUp() noexcept
	{
		/* Conecting to the default device */
		ALCdevice* device = alcOpenDevice(NULL);
		if (device == nullptr) return -1;

		/* Checking if our OpenAL support enumeration of devices */
		ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
		if (enumeration == AL_FALSE)
			std::cout << "enumeration not supported" << std::endl;
		else
			std::cout << "enumeration supported" << std::endl;


		list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context))
		{
			std::cout << "failed to make context current OpenAL" << std::endl;
			return -1;
		}


		//bool success = OPENALCALL(alcMakeContextCurrent(context));
		//if (!success) return -1;

		std::cout << "OpenAL context OK" << std::endl;

		/* Setting up the listener */
		/*ALfloat listenerOrigin[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

		OPENALCALL(alListener3f(AL_POSITION, 0.0f, 0.0f, 1.0f));
		OPENALCALL(alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f));
		OPENALCALL(alListenerfv(AL_ORIENTATION, listenerOrigin));*/
		ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

		alListener3f(AL_POSITION, 0, 0, 0);
		// check for errors
		alListener3f(AL_VELOCITY, 0, 0, 0);
		// check for errors
		alListenerfv(AL_ORIENTATION, listenerOri);
		// check for errors


		/*OPENALCALL(alGenSources((ALuint)1, &source));
		OPENALCALL(alSourcef(source, AL_PITCH, 1));
		OPENALCALL(alSourcef(source, AL_GAIN, 1));
		OPENALCALL(alSource3f(source, AL_POSITION, 0, 0, 0));
		OPENALCALL(alSource3f(source, AL_VELOCITY, 0, 0, 0));
		OPENALCALL(alSourcei(source, AL_LOOPING, AL_FALSE));*/
		alGenSources((ALuint)1, &source);
		// check for errors

		alSourcef(source, AL_PITCH, 1);
		// check for errors
		alSourcef(source, AL_GAIN, 1);
		// check for errors
		alSource3f(source, AL_POSITION, 0.f, 0.f, 0.f);
		// check for errors
		alSource3f(source, AL_VELOCITY, 0, 0, 0);
		// check for errors
		alSourcei(source, AL_LOOPING, AL_TRUE);
		// check for errros


		//OPENALCALL(alGenBuffers((ALuint)1, &buffer));
		alGenBuffers((ALuint)1, &buffer);

		return 1;
	}
}