#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "TransformComponent.hpp"
#include "../Rendering/BoxComponent.hpp"
#include "PlayerComponent.hpp"
#include "../Platform/Window.hpp"
#include "Scene.hpp"
#include "../Audio/AudioComponent.hpp"
#include "entt/entt.hpp"


namespace Fluky {
	/**
	 * Class in charge of define the game objects 
	 */
	class GameObject {

	public:
  /**
   * GameObject constructor
   * 
   * @param  {entt::entity} e : 
   * @param  {Scene*} scene   : 
   */
		GameObject(entt::entity e, Scene* scene) : entity(e), m_scene(scene){}

		/**
		 * Add a certain type of component to the entity
		 * 
		 */
		template <typename T>
		T& AddComponent() {
			T& component = m_scene->registry.emplace<T>(entity);
			return component;
		}
  /**
   * Updates all the game object components
	 * 
   * @param  {Window} window : 
   */
		void Update(Window window)
		{
			if (HasComponent<TransformComponent, BoxComponent, PlayerComponent, AudioComponent>()) {
				auto view = m_scene->registry.view<TransformComponent, BoxComponent, PlayerComponent, AudioComponent>();

				auto& transf = view.get<TransformComponent>(entity);
				auto& box = view.get<BoxComponent>(entity);
				auto& player = view.get<PlayerComponent>(entity);
				auto& audio = view.get<AudioComponent>(entity);

				box.Update(transf);
				player.Update(window.joyInput);
				audio.Update();
			}
			else if (HasComponent<BoxComponent, TransformComponent, PlayerComponent>()) {
				auto view = m_scene->registry.view<TransformComponent, BoxComponent, PlayerComponent>();

				auto& transf = view.get<TransformComponent>(entity);
				auto& box = view.get<BoxComponent>(entity);
				auto& player = view.get<PlayerComponent>(entity);

				box.Update(transf);
				player.Update(window.joyInput);
			}
			else if (HasComponent<BoxComponent, TransformComponent>()) {
				auto view = m_scene->registry.view<TransformComponent, BoxComponent>();

				auto& transf = view.get<TransformComponent>(entity);
				auto& box = view.get<BoxComponent>(entity);

				box.Update(transf);
			}

			
		};
  /**
	 * Initializes all the game object components
   * 
   * @param  {Scene} sc : 
   */
		void StartUp(Scene& sc) {
			if (HasComponent<BoxComponent, AudioComponent>()) {

				auto view = m_scene->registry.view<BoxComponent, AudioComponent>();

				auto& box = view.get<BoxComponent>(entity);
				auto& audio = view.get<AudioComponent>(entity);

				box.Init();
				audio.StartUp(sc);
			} else if (HasComponent<BoxComponent>()) {
				auto view = m_scene->registry.view<BoxComponent>();

				auto& box = view.get<BoxComponent>(entity);

				box.Init();
			}
			else if (HasComponent<AudioComponent>()) {
				auto view = m_scene->registry.view<AudioComponent>();

				auto& audio = view.get<AudioComponent>(entity);

				audio.StartUp(sc);
			}
		}

		/**
		 * Checks if the game object has a certain type of component
		 * 
		 */ 
		template<typename... T>
		bool HasComponent()
		{
			return m_scene->registry.all_of<T ...>(entity);
		}

		/**
		 * Returns a certain type of component of the game object
		 * 
		 */ 
		template<typename T>
		T& GetComponent()
		{
			return m_scene->registry.get<T>(entity);
		}
  /**
	 * checks if the game object is equal to another
   * 
   * @param  {GameObject} gO : 
   * @return {bool}          : 
   */
		bool equal(GameObject gO) {
			bool b = this->entity == gO.entity;
			return this->entity == gO.entity;
		}
		
  /**
	 * entity destructor
   * 
   */
		void ShutDown() {

			//m_scene->registry.erase<BoxComponent>(entity);
			m_scene->registry.destroy(entity);
		}

	private:

		entt::entity entity;
		Scene* m_scene;

	};



}
#endif