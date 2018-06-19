#pragma once
#include "stdafx.h"


class CSectionEndPage : public CSection
{
public:
	CSectionEndPage(CInit& ini);
	virtual ~CSectionEndPage(void);

    virtual void RunEvent();              //Обработать события выполняемой в данный момент секцией
    virtual SectionState RunDraw();       //Обобрзить графические элементы выполняемой в данный момент секциеи
    virtual void Pause( bool f = true );  //Останавливает рабту секции
    virtual SectionState Play();          //проигрывает секцию
	virtual void InitSection();

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****
};

