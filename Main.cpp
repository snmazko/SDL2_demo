#include "StdAfx.h"

CMain::CMain( CInit& ini ) :init(ini), delayDraw(5)//Задержка отображения графики
{
	indLesson = -1;
	sectionLessBlink = nullptr;
	sectionStartPage = nullptr;
	sectionEndPage = nullptr;

	daraw = true;
	timeCheck = 0;
}

CMain::~CMain()
{
	//***** Упражнения
	if(sectionLessBlink != nullptr)
		delete sectionLessBlink;

	//***** Прочие секции
	if(sectionStartPage != nullptr)
		delete sectionStartPage;
	if(sectionEndPage != nullptr)
		delete sectionEndPage;
}

void CMain::Begin()
{
	SDL_PollEvent(init.GetMainEvent());
	if(daraw)
		SDL_RenderClear(init.GetRenderer());
}

void CMain::Refresh()
{
	if(daraw)
	{
		SDL_RenderPresent(init.GetRenderer());
		daraw = false;
	}
}
void CMain::MainLoop()
{

	InitAllSection();

	while(!init.GetQuit() && init.GetMainEvent()->type != SDL_QUIT)
	{
        SetFlagDraw();      //установить флаг вывода графики

        Begin();            //получить следующее событие и очистить рендер

        HandlingSection();  //обработать текущую секцию и вывести результаты ее работы

        Refresh();          //отобразить графику на рендер
	}

}

//Инициализация секций (подпрограмм)
void CMain::InitAllSection()
{
	//**** Инициализация секций упражнений
	sectionLessBlink = new CSectionLessBlink(init);
	listLesson.push_back(sectionLessBlink);
	++indLesson;

	//**** Инициализация прочих секций
	sectionStartPage = new CSectionStartPage(init);
	sectionEndPage = new CSectionEndPage(init);

	CSection::SetCurrentSection( sectionLessBlink );//сделать секцию текущей
}

//Управление работающими в данный момент секциями
void CMain::HandlingSection()
{
	SectionState sState = CSection::RunCurrentSection(daraw);
	switch(sState)
	{
	case SECT_ERROR:
#ifdef _DEBUG
		cout << "Метод CSection::StartSection() в CMain::HandlingSection() завершился ошибкой" << endl;
#endif
		break;
	case SECT_NULL:
#ifdef _DEBUG
		cout << "Вызов CMain::HandlingSection() когда currentSection = nullptr." << endl;
#endif
		break;
	case SECT_CURR_LESS:
		break;
	case SECT_NEXT_LESS:
		{
			int t = listLesson.size();
			indLesson++;
			if(indLesson + 1 < t)//если закончились упражнения - отправляем
				CSection::SetCurrentSection(listLesson[indLesson]);
			else
			{
				indLesson = 0;
				CSection::SetCurrentSection(sectionEndPage);
			}
		}
		break;
	case SECT_LESS_BLINK:
		CSection::SetCurrentSection(sectionLessBlink);
		break;
	case SECT_START_PAGE:
		CSection::SetCurrentSection(sectionStartPage);
		break;
	case SECT_END_PAGE:
		CSection::SetCurrentSection(sectionEndPage);
		break;
	default:

		break;
	}
}

void CMain::SetFlagDraw()
{
	Uint32 currentTime = SDL_GetTicks();
	if(timeCheck + delayDraw <= currentTime)
	{
		timeCheck = currentTime;
		daraw = true;
	}
}
