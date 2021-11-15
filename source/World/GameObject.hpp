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

	class GameObject {

	public:

		GameObject(entt::entity e, Scene* scene) : entity(e), m_scene(scene){}

		/*void CreateGameObject() {
			entt::registry registry = m_scene->registry;
			entity = (*registry).create();
		}*/

		template <typename T>
		T& AddComponent() {
			T& component = m_scene->registry.emplace<T>(entity);
			return component;
		}

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

		void StartUp() {
			if (HasComponent<BoxComponent, AudioComponent>()) {

				auto view = m_scene->registry.view<BoxComponent, AudioComponent>();

				auto& box = view.get<BoxComponent>(entity);
				auto& audio = view.get<AudioComponent>(entity);

				box.Init();
				audio.StartUp();
			} else if (HasComponent<BoxComponent>()) {
				auto view = m_scene->registry.view<BoxComponent>();

				auto& box = view.get<BoxComponent>(entity);

				box.Init();
			}
			else if (HasComponent<AudioComponent>()) {
				auto view = m_scene->registry.view<AudioComponent>();

				auto& audio = view.get<AudioComponent>(entity);

				audio.StartUp();
			}
		}

		template<typename... T>
		bool HasComponent()
		{
			return m_scene->registry.all_of<T ...>(entity);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_scene->registry.get<T>(entity);
		}

	private:

		entt::entity entity;
		Scene* m_scene;

	};



}
#endif