#include "Precompiled.h"

Graphics *GRAPHICS = nullptr;

Graphics::Graphics()
{
	GRAPHICS = this;
}

Graphics::~Graphics()
{
	GRAPHICS = nullptr;
}

void Graphics::DrawTexture(unsigned x, unsigned y, RECT &screenRect, Texture &texture)
{
	assert(ENGINE != nullptr);
}
