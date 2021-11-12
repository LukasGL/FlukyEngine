#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "entt/entt.hpp"

namespace Fluky {

	class GameObject {

	public:

		void CreateGameObject();
		void AddComponent(class Component comp);
		void Update() 
		{
			auto view = registry.view<const TransformComponent, const BoxComponent>();
			for (auto entity : view)
			{
				auto& transf = view.get<const TransformComponent>(entity);
				auto& box = view.get<const BoxComponent>(entity);

				box.Update(transf);
			}
		};

	private:

		entt::registry Registry;
		Component comp;

	};



}
#endif