#include "Text.hpp"

#include "common.h"
#include "bgfx_utils.h"

#include <bx/timer.h>
#include <bx/string.h>
#include <bx/math.h>

#include "font/font_manager.h"
#include "font/text_buffer_manager.h"
#include "entry/input.h"

#include <iconfontheaders/icons_font_awesome.h>
#include <iconfontheaders/icons_kenney.h>

#include <stdio.h>
#include <wchar.h>

//long int fsize(FILE* _file)
//{
//	long int pos = ftell(_file);
//	fseek(_file, 0L, SEEK_END);
//	long int size = ftell(_file);
//	fseek(_file, pos, SEEK_SET);
//	return size;
//}
//
//TrueTypeHandle loadTtf(FontManager* _fm, const char* _filePath)
//{
//	FILE* file = fopen(_filePath, "rb");
//	if (NULL != file)
//	{
//		uint32_t size = (uint32_t)fsize(file);
//		uint8_t* mem = (uint8_t*)malloc(size + 1);
//		size_t ignore = fread(mem, 1, size, file);
//		BX_UNUSED(ignore);
//		fclose(file);
//		mem[size - 1] = '\0';
//		TrueTypeHandle handle = _fm->createTtf(mem, size);
//		free(mem);
//		return handle;
//	}
//
//	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
//	return invalid;
//}
//
//static const char* s_fontFilePath[] =
//{
//	"../thirdParty/bgfx-full/font/droidsans.ttf",
//	"../thirdParty/bgfx-full/font/chp-fire.ttf",
//	"../thirdParty/bgfx-full/font/bleeding_cowboys.ttf",
//	"../thirdParty/bgfx-full/font/mias_scribblings.ttf",
//	"../thirdParty/bgfx-full/font/ruritania.ttf",
//	"../thirdParty/bgfx-full/font/signika-regular.ttf",
//	"../thirdParty/bgfx-full/font/five_minutes.otf",
//};

namespace Fluky {

	/*FontManager* m_fontManager;
	TextBufferManager* m_textBufferManager;


	TextBufferHandle m_transientText;
	TextBufferHandle m_staticText;

	static const uint32_t numFonts = BX_COUNTOF(s_fontFilePath);
	TrueTypeHandle m_fontFiles[numFonts];
	FontHandle m_fonts[numFonts];*/

	int Text::Init()
	{

		//// Init the text rendering system.
		//m_fontManager = new FontManager(512);
		//m_textBufferManager = new TextBufferManager(m_fontManager);

		//// Load some TTF files.
		//for (uint32_t ii = 0; ii < numFonts; ++ii)
		//{
		//	// Instantiate a usable font.
		//	m_fontFiles[ii] = loadTtf(m_fontManager, s_fontFilePath[ii]);
		//	m_fonts[ii] = m_fontManager->createFontByPixelSize(m_fontFiles[ii], 0, 32);

		//	// Preload glyphs and blit them to atlas.
		//	m_fontManager->preloadGlyph(m_fonts[ii], L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

		//	// You can unload the truetype files at this stage, but in that
		//	// case, the set of glyph's will be limited to the set of preloaded
		//	// glyph.
		//	m_fontManager->destroyTtf(m_fontFiles[ii]);
		//}

		//for (uint32_t ii = 0; ii < numFonts; ++ii)
		//{
		//	// Add some text to the buffer.
		//	// The position of the pen is adjusted when there is an endline.
		//	m_textBufferManager->appendText(m_staticText, m_fonts[ii], L"The quick brown fox jumps over the lazy dog\n");
		//}

		return 0;
	}
	Text::~Text()
	{
		/*for (uint32_t ii = 0; ii < numFonts; ++ii)
		{
			m_fontManager->destroyFont(m_fonts[ii]);
		}

		m_textBufferManager->destroyTextBuffer(m_staticText);
		m_textBufferManager->destroyTextBuffer(m_transientText);*/
	}
	void Text::Update() noexcept
	{
	}
}