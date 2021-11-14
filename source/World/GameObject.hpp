#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "entt/entt.hpp"

namespace Fluky {

	class GameObject {

	public:

		void CreateGameObject(entt::registry& registry) {
			entity = registry.create();
		}

		template <typename T>
		void AddComponent(entt::registry& registry) {

		}

		void Update(entt::registry& registry)
		{
			auto view = registry.view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto box = view.get<BoxComponent>(entity);

			box.Update(transf);
		};

		void ShutDown(entt::registry& registry) {

			auto view = registry.view<TransformComponent, BoxComponent>();

			auto& transf = view.get<TransformComponent>(entity);
			auto& box = view.get<BoxComponent>(entity);

			box.~BoxComponent();

		}

	private:

		entt::entity entity;

	};



}
#endif