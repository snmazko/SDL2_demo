#pragma once
#include "StdAfx.h"


class CFlag
{
private:
	//**** Static area
    static CFlag* pMouseDown;   //указатель на объект на котором произошло нажатие мышки
    static CFlag* pMouseHover;  //указатель на объект на который наведена мышка

	//**** FLAG Ozers
    bool isMuved;       //Перемещаемый или нет екземпляр
    bool isVisible;     //Видимый или нет екземпляр

	//**** FLAG Events***
    bool mouseDown;     //указывает что произошло нажатие мышки на контроле
    bool mouseMuve;     //указывает что контрол подлежит перемещению соответственно с текущим положением мышким
    bool isHover;       //Над объектом мышка
    bool isPress;       //Кнопка зажата
    bool onDoublePress; //true - кнопка отжимаестя сразу, false - кнопка отпускается после повторного нажатия

    bool tempPress;     //Промежуточный флаг содержит состояние флага isPress перед обработкой нажатия
    bool tempPressUp;   //Устаналиваетс в false при обработке SDL_MOUSEBUTTONDOWN т true - SDL_MOUSEBUTTONUP

public:
	CFlag(void);
    CFlag(const CFlag& Cc);				//конструктор копирования
	CFlag& operator=(const CFlag& Cc);	//Оператор присваиванивания
	~CFlag(void);

    static void MouseUp();              //снимает флаг mouseDown с нажатого екземпляра
    static void MouseHover(CFlag* Cf);  //снимает флаг mouseDown с нажатого екземпляра

	//**** mouseDown
	void SetMouseDown(bool f);
	bool GetMouseDown() const { return mouseDown; }

	//**** mouseMuve
	void SetMouseMuve(bool f);
	bool GetMouseMuve() const { return mouseMuve; }

	//**** isMuved
	void SetIsMuved(bool f) { isMuved = f; }
	bool GetIsMuved() const { return isMuved; }

	//**** isVisible
	void SetIsVisible(bool f) { isVisible = f; }
	bool GetIsVisible() const { return isVisible; }

	//**** isHover
	void SetIsHover(bool f){ isHover = f; }
	bool GetIsHover() const { return isHover; }

	//**** isPress
	void SetIsPress(bool f){ isPress = f; }
	bool GetIsPress() const { return isPress; }

	//**** onDoublePres
	void SetOnDoublePress(bool f){ onDoublePress = f; }
	bool GetOnDoublePress() const { return onDoublePress; }

	//**** tempPress
	void SetTempPress(bool f){ tempPress = f; }
	bool GetTempPress() const { return tempPress; }

	//**** tempPressUp
	void SetTempPressUp(bool f){ tempPressUp = f; }
	bool GetTempPressUp() const { return tempPressUp; }

};
