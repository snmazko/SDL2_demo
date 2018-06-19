#pragma once
#include "StdAfx.h"

class CCell;

class CRadioBox
{
	CCell& cell;
    vector<CCheckBox*> ListCheckBox;  //Вектор с указателями на все чекбоксы
    CCheckBox* checkedBox;            //указатель на чекбокс который нажат в данный момент

	//string strDo;
	//string strPosle;

	//координаты верхнего левого угла на рендере от которого будет отщитываться координаты каждого чекбокса радиобокса
	int destX;
	int destY;

	char* pachFont;
	int size;
	SDL_Color* colorFont;
	void SetFontAll();

public:
	CRadioBox(CCell& c, int x = 0, int y = 0,	char* font = nullptr, int size=26, SDL_Color* color = nullptr );
	~CRadioBox(void);

	void Add(char* pOn, char* pOff, int x, int y, wchar_t* text = L"");
	void SetChecked( CCheckBox* param1 );

	void SetPachFont(char* font);
	void SetFontSize(int size);
	void SetColorFont(SDL_Color* color);
	void SetFont(char* font, int size, SDL_Color* color);

	bool FileExists(const char *fname);//проверяет наличие файла по переданному пути
};

