#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "TransformComponent.hpp"
#include "../Rendering/BoxComponent.hpp"
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
			m_scene->gameObjectVector.push_back(*this);
			return component;
		}

		void Update()
		{
			auto view = m_scene->registry.view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto box = view.get<BoxComponent>(entity);

			box.Update(transf);
		};

		void ShutDown() 
		{

			auto view = m_scene->registry.view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto& box = view.get<BoxComponent>(entity);

			box.~BoxComponent();

		}

	private:

		entt::entity entity;
		Scene* m_scene;

	};



}
#endif