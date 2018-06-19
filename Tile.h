#pragma once
#include "StdAfx.h"


class CTile : public CImage4Back
{
	//смещение от верхней левой точки екземпляра до точки где была нажата мышка
	int deltaX;
	int deltaY;

	bool fMoved;

public:

	//***** КОНСТРУКТОРЫ МЕТОДЫ ПЕРЕОПРЕДЕЛЕНИЯ
    CTile( //Конструктор
		CInit& ini,
		char* pImage, 
		char* pImageHover, 
		char* pImagePress,
		char* pImageHoverPress 
		);
    virtual ~CTile(); //Деструктор
	//********** End ****

	CText Text;

	// ********** МЕТОДЫ КОТОРЫЕ БУДУТ ПЕРЕОПРЕДЕЛЕНЫ  ******
    virtual void Draw();          //Отобразить екзепляр
    virtual void HendlerEvent();  //Обработчик события экземпляра класса

    virtual void ReceiveFocus();  //екземпляр получил фокус
    virtual void LoseFocus();     //екземпляр потерял фокус

    virtual void ReceiveHover();  //екземпляр получил Hover
    virtual void LoseHover();     //екземпляр потерял Hover

    virtual void ReceivePress();  //екземпляр получил Press
    virtual void LosePress();     //екземпляр потерял Press
	//********** End ****

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****

	void ChangePosition(int deltaX, int deltaY);

	void SetText(wchar_t* text);//Установить текст контрола

	void TextInRect();//Разместить текст по центру вертикально и горизонатально, если не влазит - подобрать размер шрифта

    void MuveTile();  //Переместить позицию контрола за мышкой

	void SetDeltaXY();//получить смещение от верхней левой точки екземпляра до точки где была нажата мышка

	void SetMoved(bool f){ fMoved = f; }
};

