#pragma once
#ifndef FIGURES_HPP
#define FIGURES_HPP


namespace Fluky {

	class Figures {

	public:
		friend class World;

		int Init();

		~Figures();

		void Update() noexcept;

		/*bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;

		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;
		bgfx::ProgramHandle program;*/

		unsigned int counter;

		/*void StartUp() noexcept;
		void ShutDown() noexcept;
		void Update() noexcept;*/

	};

}
#endif