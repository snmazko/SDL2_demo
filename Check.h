#pragma once
#include "StdAfx.h"

class CCheck : public CGraphics
{
	int indent;//отступ от картинки до текста

	bool checked;

	char* pachFont;
	int size;
	SDL_Color* colorFont;

	//картинка фона
	SDL_Rect rectDestImg;
	SDL_Rect rectSrcImg;

    SDL_Texture* textureImageOn;	//указатель на текстуру картинки checked
    SDL_Texture* textureImageOff;	//указатель на текстуру картинки не checked
    char* pachImageOn;				//путь к файлу картинки checked
    char* pachImageOff;				//путь к файлу картинки не checked

	void TextAndImageInRect();		//распределить ректы текста и картинки

public:
	CCheck( CInit& ini, char* pOn, char* pOff, wchar_t* text = L"", int H = 18 );//Конструктор
	virtual ~CCheck(void);

	CText Text;//Текст контрола

	void DrawCheck();
	
	void SetIndent(int ind);
	int GetIndent()const { return indent; }

    void SetText(wchar_t* text);                      //Установить текст контрола
    void SetImage( char* pImageOn, char* pImageOff ); //Принимает путь к картинкам

	void SetChecked(bool f);
    MyEvent evSetChecked;   //Вызывается при вызове метода SetChecked когда передается параметр true
    MyEvent evUnSetChecked; //Вызывается при вызове метода SetChecked когда передается параметр false
	bool GetChecked() const { return checked; }

	void SetPachFont(char* font);
	void SetFontSize(int size);
	void SetColorFont(SDL_Color* color);
	void SetFont(char* font, int size, SDL_Color* color);

	//Переопределение методов родителя
	void SetPointDest(SDL_Point &p );
	void SetPointDest(int x, int y );
};

