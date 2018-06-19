#include "StdAfx.h"


CEffektExteriorShine::CEffektExteriorShine(CControls* Cc)
{
	renderer = Cc->GetRenderer();
	colorPerimeter = Cc->GetColorPerimeter();
	colorFill = Cc->GetColorFill();
	rectControl = Cc->GetRectControl();

	rectEffect.x = rectControl.x - 20;
	rectEffect.y = rectControl.y - 20;
	rectEffect.h = rectControl.h + 40;
	rectEffect.w = rectControl.w + 40;

	colorEffect.r = 120, colorEffect.g = 120, colorEffect.b = 120, colorEffect.a = 100;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    surface = SDL_CreateRGBSurface(0, 100, 100, 32,
                                   rmask, gmask, bmask, amask);
    if(surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
       // exit(1);
    }
		texture = SDL_CreateTextureFromSurface(renderer, surface);
}


CEffektExteriorShine::~CEffektExteriorShine(void)
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);//освободить текстуру
}

void CEffektExteriorShine::Show()
{
	if(renderer != nullptr)
	{

		SDL_RenderCopy(renderer, texture, &rectEffect, &rectEffect);
    /* or using the default masks for the depth: */
  //  surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);


// 		SDL_Color colorOld;//получить текущий цвет
// 		SDL_GetRenderDrawColor(renderer, &colorOld.r, &colorOld.g, &colorOld.b, &colorOld.a);
// 
// 		//установить цвет в рендере
// 		SDL_SetRenderDrawColor( renderer, colorEffect.r, colorEffect.g, colorEffect.b, colorEffect.a );
// 
// 		//отобразить эффект
// 		SDL_RenderFillRect(renderer, &rectEffect);
// 
// 		//вернуть цвет по умолчанию
// 		SDL_SetRenderDrawColor( renderer, colorOld.r, colorOld.g, colorOld.b, colorOld.a );
	}
}
