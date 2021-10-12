#include "Figures.hpp"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "bx/math.h"
#include <iostream>

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
};


static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

bgfx::ShaderHandle loadShader(const char* FILENAME)
{


	const char* shaderPath = "???";

	switch (bgfx::getRendererType()) {
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:  shaderPath = "../thirdParty/bgfx-full/shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "../thirdParty/bgfx-full/shaders/dx11/";  break;
	case bgfx::RendererType::Gnm:        shaderPath = "../thirdParty/bgfx-full/shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "../thirdParty/bgfx-full/shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "../thirdParty/bgfx-full/shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "../thirdParty/bgfx-full/shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "../thirdParty/bgfx-full/shaders/spirv/"; break;
	}

	size_t shaderLen = strlen(shaderPath);
	size_t fileLen = strlen(FILENAME);
	char* filePath = (char*)calloc(1, shaderLen + fileLen + 1);//(char*)malloc(shaderLen + fileLen);
	memcpy(filePath, shaderPath, shaderLen);
	memcpy(&filePath[shaderLen], FILENAME, fileLen);

	FILE* file = fopen(filePath, "rb");
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return bgfx::createShader(mem);
}

namespace Fluky {


	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;

	bgfx::ShaderHandle vsh;
	bgfx::ShaderHandle fsh;
	bgfx::ProgramHandle program;

	int Figures::Init()
	{
		bgfx::VertexLayout pcvDecl;
		pcvDecl.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
		vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), pcvDecl);
		ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList)));

		vsh = loadShader("vs_cubes.bin");
		fsh = loadShader("fs_cubes.bin");
		program = bgfx::createProgram(vsh, fsh, true);

		counter = 0;

		std::cout << "Figure initialized succesfully!" << std::endl;

		return 1;
	}
	Figures::~Figures()
	{
		bgfx::destroy(ibh);
		bgfx::destroy(vbh);
	}
	void Figures::Update() noexcept
	{

		float mtx[16];
		bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
		bgfx::setTransform(mtx);

		bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);

		bgfx::submit(0, program);

		counter++;

		///*bgfx::IndexBufferHandle ibh = m_ibh[m_pt];
		//uint64_t state = 0
		//	| (m_r ? BGFX_STATE_WRITE_R : 0)
		//	| (m_g ? BGFX_STATE_WRITE_G : 0)
		//	| (m_b ? BGFX_STATE_WRITE_B : 0)
		//	| (m_a ? BGFX_STATE_WRITE_A : 0)
		//	| BGFX_STATE_WRITE_Z
		//	| BGFX_STATE_DEPTH_TEST_LESS
		//	| BGFX_STATE_CULL_CW
		//	| BGFX_STATE_MSAA
		//	| s_ptState[m_pt]
		//	;*/

		//// Submit 11x11 cubes.
		//for (uint32_t yy = 0; yy < 11; ++yy)
		//{
		//	for (uint32_t xx = 0; xx < 11; ++xx)
		//	{
		//		float mtx[16];
		//		//bx::mtxRotateXY(mtx, time + xx * 0.21f, time + yy * 0.37f);
		//		mtx[12] = -15.0f + float(xx) * 3.0f;
		//		mtx[13] = -15.0f + float(yy) * 3.0f;
		//		mtx[14] = 0.0f;

		//		// Set model matrix for rendering.
		//		bgfx::setTransform(mtx);

		//		// Set vertex and index buffer.
		//		bgfx::setVertexBuffer(0, m_vbh);
		//		//bgfx::setIndexBuffer(ibh);

		//		// Set render states.
		//		//bgfx::setState(state);

		//		// Submit primitive for rendering to view 0.
		//		//bgfx::submit(0, m_program);
		//	}
		//}
	}

	
}