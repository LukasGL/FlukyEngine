#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

enum ComponentType {
	TransformComponent,
	CameraComponent,
	MeshComponent,
	AudioComponent
};

namespace Fluky {

	class Component {

	public:

		ComponentType GetType();
		void IsType();
		void ReceiveEvent();
		void Update();

	private:
		ComponentType Type;

	};



}
#endif