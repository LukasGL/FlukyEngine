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

		void CreateGameObject(Scene& scene) {
			entt::registry* registry = &scene.GetRegistry();
			entity = (*registry).create();
		}

		template <typename T>
		void AddComponent(Scene& scene) {
			entt::registry* registry = &scene.GetRegistry();
			(*registry).emplace<T>(entity);
		}

		void Update(Scene& scene)
		{
			entt::registry* registry = &scene.GetRegistry();

			auto view = (*registry).view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto box = view.get<BoxComponent>(entity);

			box.Update(transf);
		};

		void ShutDown(Scene& scene) {

			entt::registry* registry = &scene.GetRegistry();

			auto view = (*registry).view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto& box = view.get<BoxComponent>(entity);

			box.~BoxComponent();

		}

	private:

		entt::entity entity;

	};



}
#endif