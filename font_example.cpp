#include "stdafx.h"

#pragma comment(lib, "librarys/SDL2/lib/x86/SDL2.lib")
#pragma comment(lib, "librarys/SDL2_image/lib/x86/SDL2_image.lib")
#pragma comment(lib, "librarys/SDL2_mixer/lib/x86/SDL2_mixer.lib")
#pragma comment(lib, "librarys/SDL2_ttf/lib/x86/SDL2_ttf.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand( static_cast<unsigned int>(time( 0 )) ); // автоматическая рандомизация

	CInit cInit(//Инициализация SDL2
		"SDL2-Demo",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1000,
		680
		//,SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN
		);

	CMain cmain(cInit);//Запуск основного класса работы приложения

	cmain.MainLoop();//вечный цикл работы приложения


	//system("pause");
	return 0;
}