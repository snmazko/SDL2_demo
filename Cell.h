/*
Секции будут содержать свои контролы и другие елементы также методы обработки событий и отрисовки
*/
#pragma once
#include "stdafx.h"

class CCell : public CGraphics
{
	vector<CGraphics*> ListGraphics;//Вектор с указателями на все графические элементы сектора

	//картинка фона. Картинка будет выводится и увеличиваться/уменьшаться чтобы вписаться в рект секции без трансформации
    SDL_Texture* imageFonTexture;	//указатель на текстуру картинки фона
    char* imageFonPach;				//путь к файлу картинки фона
    SDL_Rect rectImageFonSrc;       //прямоугольник из картинки который будет отображен на рендере

public:
	CCell(CInit& ini, int w, int h);
	~CCell(void);
	
    virtual void Draw();          //Отобразить екзепляр
    virtual void HendlerEvent();  //Обработчик события экземпляра класса

    virtual void ReceiveFocus();  //екземпляр получил фокус
    virtual void LoseFocus();     //екземпляр потерял фокус

    virtual void ReceiveHover();  //екземпляр получил Hover
    virtual void LoseHover();     //екземпляр потерял Hover

    virtual void ReceivePress();  //екземпляр получил Press
    virtual void LosePress();     //екземпляр потерял Press

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****

	void AddGraphics(CGraphics* gr);

	void SetImage(char* pImage);//Принимает путь к картинке		

	//запускает для всех елементов вектора ListGraphics виртуальный метод Draw()
	void DrawGraphicsList();

	//найти и вернуть ссылку на верхний контрол из ListGraphics на котором находится мышка либо nullptr
	CGraphics* GetGraphicsUnderMouse();

    void SetTopInVector(CGraphics* gr); //Поставить елемент в начало обработки (в начало вектора ListGraphics)

    int GetIndex(CGraphics* gr);        //Возвращает индекс контрола либо -1 в ListGraphics
};

