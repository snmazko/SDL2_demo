#pragma once
#include "StdAfx.h"

//Клас будет содержать флаги нажатых клавиш и устанавливать с какой скоростью обрабатывать нажатия клавиш
class CTextFlag
{
private:

	typedef pair<Uint32, CKeyState> Entry;

	map<Uint32, CKeyState> keyChar;

    bool KF_CAPS;       //флаг что включен Caps Loock
    bool f_CapsRelease; //флаг указывает что произошло отжатие клавиши Caps Loock

    bool KF_SHIFT;      //флаг что включен Shift

public:

	CTextFlag(void);
	~CTextFlag(void);

//Обработчик нажатия клавиши Caps Loock вернет состояние Caps Loock true - велючен, false - выключен 
	bool K_DownCaps();

//Обработчик ожатия клавиши Caps Loock
	void K_UpCaps(){ f_CapsRelease = true;}

    void K_DownShift(){ KF_SHIFT = true;} //Обработчик нажатия клавиши Shift
    void K_UpShift(){ KF_SHIFT = false;}  //Обработчик отжатия клавиши Shift

//проверяет наличие ключа в картах и обрабатывет нажатие клавиши, return true если клавиша есть, иначе false
	bool K_DownKey(Uint32 key, wchar_t* stroka);

//проверяет наличие ключа в картах и обрабатывет отжатие клавиши, return true если клавиша есть, иначе false
	bool K_UpKey(Uint32 key);

	enum LANG { ENG = 1, RUS = 3 } lang;

	void SetLang(LANG l){ lang = l; }
	LANG GetLang()const{ return lang; }	

};

