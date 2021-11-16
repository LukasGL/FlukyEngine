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
	/**
	 * Defines a components assigned to a game object
	 */
	class Component {

	public:
  /**
	 * Returns the type of the component
   * 
   * @return {ComponentType}  : 
   */
		ComponentType GetType();

		
  /**
	 * Checks if the component is of a certain type
   * 
   */
		void IsType();
  /**
	 * What to do when it receives an event
   * 
   */
		void ReceiveEvent();
		
  /**
	 * what to do when the component updates
   * 
   */
		void Update();

	private:
		ComponentType Type;

	};



}
#endif