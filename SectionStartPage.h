#pragma once
#include "stdafx.h"

class CSectionStartPage : public CSection
{
public:
	CSectionStartPage(CInit& ini);
	virtual ~CSectionStartPage(void);

    virtual void RunEvent();              //Обработать события выполняемой в данный момент секцией
    virtual SectionState RunDraw();       //Обобрзить графические элементы выполняемой в данный момент секциеи
    virtual void Pause( bool f = true );  //Останавливает рабту секции (упражнения)
    virtual SectionState Play();          //проигрывает секцию упражнение
	virtual void InitSection();

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****
};

