#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include "entt/entt.hpp"
#include "../Audio/AudioManager.hpp"

namespace Fluky {
	/**
	 * Class in charge of define the scene assigned to a world
	 */ 
	class Scene {
	public:
		friend class World;
		friend class GameObject;
		friend class AudioComponent;
  /**
	 * Creates a game object and assigns it to the registry
   * 
   * @return {GameObject}  : 
   */
		class GameObject CreateGameObject();
  /**
   * Scene destructor
   */
		void ShutDownScene();
  /**
   * Scene initializer
   */
		void StartUp();


	private:

		std::vector<GameObject> gameObjectVector;

		entt::registry registry;

		std::vector<ALuint> sources;

		std::vector<ALuint> buffers;

		AudioManager audioManager;
	};



}
#endif