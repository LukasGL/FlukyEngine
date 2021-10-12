#pragma once
#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <stdio.h>
#include <cstdio>
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "bx/math.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace Fluky {

	class Figures {

	public:
		friend class World;

		int Init();

		~Figures();

		void Update() noexcept;

		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;

		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;
		bgfx::ProgramHandle program;

		unsigned int counter;

		/*void StartUp() noexcept;
		void ShutDown() noexcept;
		void Update() noexcept;*/

	};

}
#endif