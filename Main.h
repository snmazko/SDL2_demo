#pragma once
#include "StdAfx.h"


class CMain
{
	CInit& init;
	
	vector<CSection*> listLesson;		//Вектор с указателями на все секции которые представляют собой упражнения
    int indLesson;						//индекс текущего упражнения из ListLesson

	//***** Упражнения
	CSectionLessBlink* sectionLessBlink;

	//***** Прочие секции
	CSectionStartPage* sectionStartPage;
	CSectionEndPage* sectionEndPage;

    const Uint32 delayDraw; //Задержка отображения графики
    Uint32 timeCheck;       //Время последнего отображения

    bool daraw;             //флаг указывает что можно выводить графику
public:
	CMain(CInit& ini);
	~CMain(void);

    void Begin();           //Получить следующее сообщение очистить рендер
    void Refresh();         //Обновить рендер
    void MainLoop();        //Рабочий Цикл

    void InitAllSection();  //инициализация секций
    void HandlingSection(); //обработка секций

    void SetFlagDraw();     //Установка флага для отображения графики
};
