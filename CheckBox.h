#pragma once
#include "StdAfx.h"

class CRadioBox;

class CCheckBox : public CCheck
{
	CRadioBox* radioBox;//указатель на екземпеляр радио бокса которому принадлежит данный чекбокс
	bool losPr;//Указывает что отпускание произошло
public:

	CCheckBox( CInit& ini, char* pOn, char* pOff, CRadioBox* radioB = nullptr, wchar_t* text = L"", int H = 18 );
	virtual ~CCheckBox(void);

	// ********** МЕТОДЫ КОТОРЫЕ БУДУТ ПЕРЕОПРЕДЕЛЕНЫ  ******
    virtual void Draw();			//Отобразить екзепляр
    virtual void HendlerEvent();	//Обработчик события экземпляра класса

    virtual void ReceiveFocus();	//екземпляр получил фокус
    virtual void LoseFocus();		//екземпляр потерял фокус

    virtual void ReceiveHover();	//екземпляр получил Hover
    virtual void LoseHover();		//екземпляр потерял Hover

    virtual void ReceivePress();	//екземпляр получил Press
    virtual void LosePress();		//екземпляр потерял Press
	//********** End ****

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****

	//CMyEvent evReceivePress;
};

