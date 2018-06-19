#pragma once
#include "StdAfx.h"

class CCaret
{
private:
    static CCaret* currentCaret;          //Указатель на екземпляр который владеет кареткой
    SDL_Rect caretRect;                   //Размеры каретки
    SDL_Color caretColor;                 //цвет каретки
    bool fActivCaret;                     //показывает что каретка активна

    Uint32 timeCheck;                     //переменная будет содержать милисекунды
    Uint32 timeDelay;                     //Задержка моргания в милисекундах

    bool fShow;                           //показывает скрыта или отображена каретка

    SDL_Renderer* renderer;               //указатель окна ренденинга

    Uint8 NormalColor( Uint8 t );         //Приводит переданное число в рамки 0 - 255
    SDL_Color NormalColor( SDL_Color t ); //Приводит стркутуру в рамки 0 - 255

public:
	CCaret(
		SDL_Renderer* rend,
		SDL_Rect* Rect = nullptr,
		SDL_Color* Color = nullptr,
		Uint32 Delay = 400);
	~CCaret(void);

	//********** МЕТОДЫ УСТАНОВКИ возврата ПОЛЕЙ ******
	void SetCaretRect(SDL_Rect r);
	void SetCaretRect(int x, int y, int w, int h);
	SDL_Rect GetCaretRect() const { return caretRect; }

	void SetCaretX(int x) { caretRect.x = x; }
	int GetCaretX() const { return caretRect.x; }

	void SetCaretY(int y) { caretRect.y = y; }
	int GetCaretY() const { return caretRect.y; }

	void SetCaretW(int w) { caretRect.w = w; }
	int GetCaretW() const { return caretRect.w; }

	void SetCaretH(int h) { caretRect.h = h; }
	int GetCaretH() const { return caretRect.h; }

	void SetCaretColor(SDL_Color color);
	void SetCaretColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetCaretColor(int r, int g, int b, int a);
	SDL_Color GetCaretColor() const { return caretColor; }
	
	CCaret* GetCurrentCaret() const { return currentCaret; }

	void SetActivCaret( bool f = true );//активировать каретку
	bool GetActivCaret() const { return fActivCaret; }

	void SetTimeDelay(Uint32 delay);
	Uint32 GetTimeDelay() const { return timeDelay; }

	SDL_Renderer* GetRenderer() const { return renderer; }

	void DrawCaret();
};
