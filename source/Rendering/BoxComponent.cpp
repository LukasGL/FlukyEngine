#include "BoxComponent.hpp"
#include "../World/TransformComponent.hpp"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
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

	int BoxComponent::Init()
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

	BoxComponent::~BoxComponent()
	{
		//bgfx::destroy(ibh);
		//bgfx::destroy(vbh);
	}

	void BoxComponent::Update(TransformComponent& transform) noexcept
	{
		/*	float mtx[16];
			bx::mtxRotateXY(mtx, sizeX, sizeY);*/
		bgfx::setTransform(transform.mtx);

		bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);

		bgfx::submit(0, program);

		counter++;
	}


}