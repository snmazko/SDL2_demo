#pragma once
#include "StdAfx.h"

class CKeyState
{
private:

    static Uint32 delayFirstPress;  //Задержка обработки второго символа при зажатии клавиши
    static Uint32 delayMorePress;   //Задержка обработки следующих за вторым символов после зажатия клавиши

    Uint32 timeCheck; //Время нажатия клавиши

    Uint32 key;       //кейкод клавиши экземпляра
    bool isPress;     //true - клавиша нажата, false - клавиша опущена
    bool launchHand;  //true указывает что можно запускать обработчик клавиши
    bool delayFirst;  //true указывает что проверка задержки delayFirstPress уже применялась

	wchar_t* mas[5];

public:

	CKeyState(
		Uint32 key = SDLK_UNKNOWN,
		wchar_t engUpper[] = nullptr,
		wchar_t engLower[] = nullptr,
		wchar_t rusUpper[] = nullptr,
		wchar_t rusLower[] = nullptr
		);

    CKeyState(const CKeyState& Cc);				//конструктор копирования
	CKeyState& operator=(const CKeyState& Cc);	//Оператор присваиванивания

	~CKeyState(void);

	Uint32 GetKey()const{ return key; }
	Uint32 GetTimeCheck()const{ return timeCheck; }
	bool GetIsPress()const{return isPress;}
	bool GetLaunch()const{return launchHand;}
	bool GetDelayFirst()const{return delayFirst;}

	bool GetLaunchHand();

    bool SetKeyPress();   //обрабатывает нажатие на клавишу
    void SetKeyRelease(); //обрабатывает отпускание клавиши

	enum EN_CHAR { ENG_UP = 1, ENG_LOW, RUS_UP, RUS_LOW };
	const wchar_t* GetChar(EN_CHAR ind)const { return mas[ind]; }
};
