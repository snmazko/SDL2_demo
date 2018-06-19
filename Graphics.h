/*
Базовый абстрактный класс для всех графических элементов (контролы, фон, сектор и прочее)
*/
#pragma once
#include "stdafx.h"

class CGraphics : public CBaseClass
{
	CInit& init;

    static CGraphics* focus;	//Экземпляр который находится в данный момент в фокусе
    static CGraphics* hover;	//Экземпляр который находится в данный момент в hover (под мышкой)
	static CGraphics* press;	//указатель на объект на котором произошло нажатие мышки

	bool visible;

    int width;            //Ширина екземпляра
    int height;           //Высота екземпляра
    SDL_Rect rectSrc;     //прямоугольник ректа который будет отображен на рендере
    SDL_Point pointDest;  //точка на рендере которая будет вершиной прямоугольника для отображения rectSrc

    SDL_Rect rectWork;    //рабочий рект с учетом рамки
	void SetRectWork();

	//**** параметры рамки ректа ***
    bool borderLeft;            //true - отображать левую границу, false - граница не отображается
    int borderLeftThickness;    // толщина левой границы
    SDL_Color borderLeftColor;  //Цвет левой границы ректа

	bool borderRight;
	int borderRightThickness;
	SDL_Color borderRightColor;

	bool borderTop;
	int borderTopThickness;
	SDL_Color borderTopColor;

	bool borderBottom;
	int borderBottomThickness;
	SDL_Color borderBottomColor;
	//*** END ***

    bool fFill;           //закрашивать или нет заливку
    SDL_Color colorFill;  //цвет заливки контрола

public:
	CGraphics(CInit& ini);
	virtual ~CGraphics(void);

	//*** FOCUS
    void SetFocus();                              //установка фокуса на елементе
    MyEvent evSetFocus;                           //Вызывается при вызове метода SetFocus
    void ResetFocus();                            //убрать фокус с элемента
    MyEvent evResetFocus;                         //Вызывается при вызове метода ResetFocus
    static void DropFocus();                      //Сброс фокуса с элемента который в данный момент в фокусе
    static CGraphics* GetFocus() {return focus; } //Возвращает ссылку на елемент который находтся в фокусе

	//*** HOVER
    void SetHover();                              //установка Hover на елементе
    MyEvent evSetHover;                           //Вызывается при вызове метода SetHover
    void ResetHover();                            //убрать Hover с элемента
    MyEvent evResetHover;                         //Вызывается при вызове метода ResetHover
    static void DropHover();                      //Сброс Hover с элемента который в данный момент в Hover
    static CGraphics* GetHover() {return hover; } //Возвращает ссылку на елемент который находтся в Hover

	//*** PRESS
    void SetPress();                              //установка Press на елементе
    MyEvent evSetPress;                           //Вызывается при вызове метода SetPress
    void ResetPress();                            //убрать Press с элемента
    MyEvent evResetPress;                         //Вызывается при вызове метода ResetPress
    static void DropPress();                      //Сброс Press с элемента который в данный момент в Press
    static CGraphics* GetPress() {return press; } //Возвращает ссылку на елемент который находтся в Press

	// ********** МЕТОДЫ КОТОРЫЕ БУДУТ ПЕРЕОПРЕДЕЛЕНЫ НАСЛЕДНИКАМИ ******
    virtual void Draw() = 0;          //Отобразить екзепляр
    virtual void HendlerEvent() = 0;  //Обработчик события экземпляра класса

    virtual void ReceiveFocus() = 0;  //екземпляр получил фокус
    virtual void LoseFocus() = 0;     //екземпляр потерял фокус

    virtual void ReceiveHover() = 0;  //екземпляр получил Hover
    virtual void LoseHover() = 0;     //екземпляр потерял Hover

    virtual void ReceivePress() = 0;  //екземпляр получил Press
    virtual void LosePress() = 0;     //екземпляр потерял Press
	//********** End ****

	bool GetVisible()const{ return visible; }
	void SetVisible(bool f);

	//общий размер ректа
	void SetWidth(int w);
	int GetWidth()const{ return width; }

	void SetHeight(int h);
	int GetHeight()const{ return height; }

	void SetWH(int w, int h);

	//прямоугольник ректа который будет отображен на рендере
	void SetRectSrc(SDL_Rect &r );
	void SetRectSrc(int x, int y, int w, int h );
	SDL_Rect GetRectSrc()const{ return rectSrc; }
	SDL_Rect GetRectWork()const{ return rectWork; }

	//точка на рендере которая будет вершиной прямоугольника для отображения rectSrc
	void SetPointDest(SDL_Point &p );
	void SetPointDest(int x, int y );
	SDL_Point GetPointDest()const{ return pointDest; }

	//**** Обработчики рамки елемента
	int GetBorderLeftThick()const{	return borderLeftThickness; }
	int GetBorderRightThick()const{ return borderRightThickness;	}
	int GetBorderTopThick()const{ return borderTopThickness;	}
	int GetBorderBottomThick()const{	return borderBottomThickness; }

	void SetBorderLeft(bool f, int thick = -1, SDL_Color* color = nullptr);
	void SetBorderRight(bool f, int thick = -1, SDL_Color* color = nullptr);
	void SetBorderTop(bool f, int thick = -1, SDL_Color* color = nullptr);
	void SetBorderBottom(bool f, int thick = -1, SDL_Color* color = nullptr);
	void SetBorder(bool f, int thick = -1, SDL_Color* color = nullptr);

	//**** Установка заливки елемента, возвращает текущий цвет заливки
	void SetIsFill(bool f);
	SDL_Color FillColor(SDL_Color* color = nullptr);

	CInit& GetInit()const{ return init; }
	SDL_Renderer* GetRenderer() const { return init.GetRenderer(); }
	SDL_Event* GetEvent() const { return init.GetMainEvent(); }

    void GraphicsDrawFon();                         //закрашивает рект экземпляра фоновым цветом
    void GraphicsDrawBorder();                      //отображает границы экземпляра
    bool FileExists(const char *fname);             //проверяет наличие файла по переданному пути
    bool PointInRect( SDL_Point* p, CGraphics* gr); //проверяет попадает ли точка в рект елемента

	//проверяет перекрываются ли прямоугольники графических Элементов, записывает в переданную переменную рект перекрытия
	bool IntersectRect(CGraphics* gr, SDL_Rect* re = nullptr);
	bool IntersectRect(SDL_Rect* rDest, SDL_Rect* re = nullptr);

	//разместить второй елемент по центру первого
	void SetCenterRect(CGraphics* gen, CGraphics* chaild);

	// ***********  НАДСТРОЙКИ НАД SDL2  **********
	//Устанавливает цвет в рендере, если он передается вторым параметром, и возвращает текущий цвет рендера
	SDL_Color RenderDrawColor( SDL_Color* color = nullptr );
};

