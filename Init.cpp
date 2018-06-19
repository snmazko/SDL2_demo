#include "StdAfx.h"


CInit::CInit(const char* title, int PosX, int PosY, int ScreenWidth, int ScrinHeight, Uint32 flagWindow, Uint32 flagRenderer)
{
	window = NULL;
	renderer = NULL;
	mainEvent = NULL;
	quit = false;
	this->ScreenWidth = ScreenWidth;
	this->ScrinHeight = ScrinHeight;

	//Инициализация SDL2
	if ( SDL_Init( SDL_INIT_EVERYTHING|SDL_INIT_AUDIO ) == -1 )
	{
		printf("Failed to initialize SDL, Error:  %s\n", SDL_GetError());
		Quit();
	}
	
	//Инициализация окна
	//Для отображения в зависимости от экрана, в финале убрать либо модифицировать
	SDL_DisplayMode mode;
	if(0 == SDL_GetDesktopDisplayMode(0,&mode))
	{
		ScreenWidth = ScreenWidth > mode.w ?	mode.w : ScreenWidth;
		ScrinHeight = ScrinHeight > mode.h - 88 ? mode.h - 88 : ScrinHeight;
#ifdef _DEBUG
		cout << "Высота " << mode.h << endl;
		cout << "Ширина " << mode.w << endl;
#endif
	}

	window = SDL_CreateWindow(title, PosX, PosY, ScreenWidth, ScrinHeight, flagWindow);
	if(window == NULL)
	{
		printf("Window now created, Error: %s\n", SDL_GetError());
		Quit();
	}

	//Инициализация РЕНДЕРА
	renderer = SDL_CreateRenderer(window, -1, flagRenderer);
	if(renderer == NULL)
	{
		printf("Renderer now created, Error: %s\n", SDL_GetError());
		Quit();
	}

	//инициализация текстовых фукций
	if (TTF_Init())
	{
		printf("%s\n", TTF_GetError());
		Quit();
	}

	//инициализация звукового микшера
	if(0 == Mix_Init(MIX_INIT_MP3))
	{
		printf("Ошибка инициализации звукового микшера\n");
		Quit();
	}
	//Открыть микшер в определенном аудио формате
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	mainEvent = new SDL_Event();
}

CInit::~CInit(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	delete mainEvent;
}