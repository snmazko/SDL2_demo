#pragma once
#include "StdAfx.h"

class CInit
{
private:
    SDL_Window* window;     //окно
    SDL_Renderer* renderer; //окно рендеринга
    SDL_Event* mainEvent;   //событие

	int ScreenWidth;
	int ScrinHeight;

    bool quit;              //флаг выхода из цикла

public:
	CInit
	(
		const char* title,
		int PosX,
		int PosY,
		int ScreenWidth,
		int ScrinHeight,
		Uint32 flagWindow = SDL_WINDOW_SHOWN,
		Uint32 flagRenderer = SDL_RENDERER_ACCELERATED
	);
	~CInit(void);

	void Quit(){ quit = true; }
	bool GetQuit() const { return quit; }

	SDL_Window* GetWindow() const { return window; }
	SDL_Renderer* GetRenderer() const { return renderer; }
	SDL_Event* GetMainEvent() const { return mainEvent; }

	int GetScreenWidth() const { return ScreenWidth; }
	int GetScrinHeight() const { return ScrinHeight; }
};
