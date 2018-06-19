#pragma once
#include "StdAfx.h"

class CEffektExteriorShine
{
	SDL_Color* colorPerimeter;
	SDL_Color* colorFill;
	SDL_Rect rectControl;// Ограничивающий прямоугольник контрола
	SDL_Renderer* renderer;

	SDL_Rect rectEffect;
	SDL_Color colorEffect;

	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
	SDL_Texture* texture;
public:
	CEffektExteriorShine(CControls* Cc);
	~CEffektExteriorShine(void);

	void Show();
};

