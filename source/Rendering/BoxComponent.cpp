#include "BoxComponent.hpp"
#include "../World/TransformComponent.hpp"

#include "bgfx_utils.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include <bx/bx.h>
#include <bx/math.h>
#include <iostream>


struct PosNormalTangentTexcoordVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_normal;
	uint32_t m_tangent;
	int16_t m_u;
	int16_t m_v;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosNormalTangentTexcoordVertex::ms_layout;

static PosNormalTangentTexcoordVertex s_cubeVertices_Tex[24] =
{
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
};

static const uint16_t s_cubeIndices_Tex[36] =
{
	 0,  2,  1,
	 1,  2,  3,
	 4,  5,  6,
	 5,  7,  6,

	 8, 10,  9,
	 9, 10, 11,
	12, 13, 14,
	13, 15, 14,

	16, 18, 17,
	17, 18, 19,
	20, 21, 22,
	21, 23, 22,
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
	case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
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
	bgfx::TextureHandle loadTexture(const char* FILENAME) {
		const char* texturePath = "../thirdParty/bgfx-full/textures/";

		size_t textureLen = strlen(texturePath);
		size_t fileLen = strlen(FILENAME);
		char* filePath = (char*)calloc(1, textureLen + fileLen + 1);//(char*)malloc(shaderLen + fileLen);
		memcpy(filePath, texturePath, textureLen);
		memcpy(&filePath[textureLen], FILENAME, fileLen);

		FILE* file = fopen(filePath, "rb");
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
		fread(mem->data, 1, fileSize, file);
		mem->data[mem->size - 1] = '\0';
		fclose(file);

		return bgfx::createTexture(mem);
	}

	void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices)
	{
		struct PosTexcoord
		{
			float m_x;
			float m_y;
			float m_z;
			float m_pad0;
			float m_u;
			float m_v;
			float m_pad1;
			float m_pad2;
		};

		float* tangents = new float[6 * _numVertices];
		bx::memSet(tangents, 0, 6 * _numVertices * sizeof(float));

		PosTexcoord v0;
		PosTexcoord v1;
		PosTexcoord v2;

		for (uint32_t ii = 0, num = _numIndices / 3; ii < num; ++ii)
		{
			const uint16_t* indices = &_indices[ii * 3];
			uint32_t i0 = indices[0];
			uint32_t i1 = indices[1];
			uint32_t i2 = indices[2];

			bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position, _layout, _vertices, i0);
			bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i0);

			bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position, _layout, _vertices, i1);
			bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i1);

			bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position, _layout, _vertices, i2);
			bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i2);

			const float bax = v1.m_x - v0.m_x;
			const float bay = v1.m_y - v0.m_y;
			const float baz = v1.m_z - v0.m_z;
			const float bau = v1.m_u - v0.m_u;
			const float bav = v1.m_v - v0.m_v;

			const float cax = v2.m_x - v0.m_x;
			const float cay = v2.m_y - v0.m_y;
			const float caz = v2.m_z - v0.m_z;
			const float cau = v2.m_u - v0.m_u;
			const float cav = v2.m_v - v0.m_v;

			const float det = (bau * cav - bav * cau);
			const float invDet = 1.0f / det;

			const float tx = (bax * cav - cax * bav) * invDet;
			const float ty = (bay * cav - cay * bav) * invDet;
			const float tz = (baz * cav - caz * bav) * invDet;

			const float bx = (cax * bau - bax * cau) * invDet;
			const float by = (cay * bau - bay * cau) * invDet;
			const float bz = (caz * bau - baz * cau) * invDet;

			for (uint32_t jj = 0; jj < 3; ++jj)
			{
				float* tanu = &tangents[indices[jj] * 6];
				float* tanv = &tanu[3];
				tanu[0] += tx;
				tanu[1] += ty;
				tanu[2] += tz;

				tanv[0] += bx;
				tanv[1] += by;
				tanv[2] += bz;
			}
		}

		for (uint32_t ii = 0; ii < _numVertices; ++ii)
		{
			const bx::Vec3 tanu = bx::load<bx::Vec3>(&tangents[ii * 6]);
			const bx::Vec3 tanv = bx::load<bx::Vec3>(&tangents[ii * 6 + 3]);

			float nxyzw[4];
			bgfx::vertexUnpack(nxyzw, bgfx::Attrib::Normal, _layout, _vertices, ii);

			const bx::Vec3 normal = bx::load<bx::Vec3>(nxyzw);
			const float    ndt = bx::dot(normal, tanu);
			const bx::Vec3 nxt = bx::cross(normal, tanu);
			const bx::Vec3 tmp = bx::sub(tanu, bx::mul(normal, ndt));

			float tangent[4];
			bx::store(tangent, bx::normalize(tmp));
			tangent[3] = bx::dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;

			bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _layout, _vertices, ii);
		}

		delete[] tangents;
	}
}

namespace Fluky {

	

	int BoxComponent::Init()
	{
		PosNormalTangentTexcoordVertex::init();

		//hasTexture = ((textureColor != NULL) && (textureColor[0] == '\0'));

		Fluky::calcTangents(s_cubeVertices_Tex
			, BX_COUNTOF(s_cubeVertices_Tex)
			, PosNormalTangentTexcoordVertex::ms_layout
			, s_cubeIndices_Tex
			, BX_COUNTOF(s_cubeIndices_Tex)
		);

		bgfx::VertexLayout pcvDecl;
		pcvDecl.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

		if (hasTexture) {
			vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices_Tex, sizeof(s_cubeVertices_Tex)), PosNormalTangentTexcoordVertex::ms_layout);
			ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices_Tex, sizeof(s_cubeIndices_Tex)));
		}
		else {
			vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), pcvDecl);
			ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList)));
		}

		// Create texture sampler uniforms.
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
		s_texNormal = bgfx::createUniform("s_texNormal", bgfx::UniformType::Sampler);

		vsh = loadShader(shader_vs);
		fsh = loadShader(shader_fs);
		program = bgfx::createProgram(vsh, fsh, true);

		if (hasTexture) {
			// Load diffuse texture.
			m_textureColor = Fluky::loadTexture(textureColor);

			// Load normal texture.
			m_textureNormal = Fluky::loadTexture(textureNormal);
		}

		counter = 0;

		std::cout << "Figure initialized succesfully!" << std::endl;

		return 1;
	}

	BoxComponent::~BoxComponent()
	{
		//bgfx::destroy(ibh);
		//bgfx::destroy(vbh);
	}

	void BoxComponent::Update() noexcept
	{
		/*	float mtx[16];
			bx::mtxRotateXY(mtx, sizeX, sizeY);*/
		if (attached) {

			/*float mtx[16];
			colobj->GetTransform().getOpenGLMatrix(mtx);
			mtx[0] = shape.x;
			mtx[5] = shape.y;
			mtx[10] = shape.z;
			bgfx::setTransform(mtx);*/


			////bx::mtxScale(mtx, shape.x, shape.y, shape.z);
			////*transf = *transf + PhysMtxtoTransfMtx(colobj->GetTransform());
			//bgfx::setTransform(mtx);
			btVector3 origin = colobj->GetTransform().getOrigin();
			transf->GetMatrix()[12] = origin.getX();
			transf->GetMatrix()[13] = origin.getY();
			transf->GetMatrix()[14] = origin.getZ();

			bgfx::setTransform(transf->GetMatrix());
			
		}
		else {
			bgfx::setTransform(transf->GetMatrix());
		}


		

		bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);

		if (hasTexture) {
			// Bind textures.
			bgfx::setTexture(0, s_texColor, m_textureColor);
			bgfx::setTexture(1, s_texNormal, m_textureNormal);
		}

		// Set render states.
		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_MSAA
		);

		bgfx::submit(0, program);

		counter++;
	}


}