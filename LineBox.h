#pragma once
#include "StdAfx.h"


class CLineBox : public CGraphics
{
private:

    Align verticalAlign;		//Вертикальное выравнивание текста в контрле
	Align horizontalAlign;		//Горизонтальное выравнивание текста в контрле
	int verticalIndent;			//Отступ от края контрола по вертикали. Считается в зависимости от выравнивания
	int horizontalIndent;		//Отступ от края контрола по горизонтали. Считается в зависимости от выравнивания
	//*** Текст контрола ***
    void TextInRect();          //вписать текст в зависимости от форматирования текста

	//картинка фона
    SDL_Texture* imageFonTexture;	//указатель на текстуру картинки фона
    char* imageFonPach;				//путь к файлу картинки фона

	bool fReturn;
	void SetReturn();
	void UnsetReturn();
public:

	void SetVid(int vid);

	//***** КОНСТРУКТОРЫ МЕТОДЫ ПЕРЕОПРЕДЕЛЕНИЯ
	CLineBox( CInit& ini, int w, int h );//Конструктор
	CLineBox( CInit& ini, char* pach );//Конструктор

    virtual ~CLineBox(); //Деструктор
	//********** End ****

	CText Text;//Текст контрола

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

	MyEvent evSetReturn;//Вызывается при вызове метода SetReturn
	MyEvent evUnsetReturn;//Вызывается при вызове метода UnsetReturn

	void SetVerticalAlign(Align align);
	Align GetVerticalAlign()const { return verticalAlign; }

	void SetHorizontalAlign(Align align);
	Align GetHorizontalAlign()const { return horizontalAlign; }

	void SetVerticalIndent(int indent);
	int GetVerticalIndent()const { return verticalIndent; }

	void SetHorizontalIndent(int indent);
	int GetHorizontalIndent()const { return horizontalIndent; }

	void SetAlignAndIndent(Align vAlign, int vIndent, Align hAlign, int hIndent);

    void SetText(wchar_t* text);  //Установить текст контрола
    void SetImage(char* pImage);  //Принимает путь к картинке
};
