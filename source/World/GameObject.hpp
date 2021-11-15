#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "TransformComponent.hpp"
#include "../Rendering/BoxComponent.hpp"
#include "PlayerComponent.hpp"
#include "../Platform/Window.hpp"
#include "Scene.hpp"
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
			if (HasComponent<BoxComponent, TransformComponent, PlayerComponent>()) {
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

		template<typename... T>
		bool HasComponent()
		{
			return m_scene->registry.all_of<T ...>(entity);
			//return m_scene->registry.has<T>(entity);
			//return m_scene->m_Registry.has<T>(m_EntityHandle);
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