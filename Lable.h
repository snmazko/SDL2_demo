#pragma once
#include "StdAfx.h"


class CLable : public CGraphics
{
	CText Text;
	void BildRect();

public:
	CLable(	CInit& ini, wchar_t* text );//Конструктор
	virtual ~CLable(void);
	

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

	void SetText(wchar_t* text);
	void SetFontName(char* name);
	void SetFontSize(int size);
	void SetFontColor(SDL_Color* color);
	void SetFontColor(int r, int g, int b, int a);
	void SetFontStyle(int style);
	void SetFontParam(char* font, int size, SDL_Color* color);

	wchar_t* GetTextW() const;
};

