#pragma once

class Graphics;
extern Graphics *GRAPHICS;
class Graphics
{
public:
	Graphics();
	~Graphics();

	void DrawTexture(unsigned x, unsigned y, RECT &screenRect, Texture &texture);
};
