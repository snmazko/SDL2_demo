/*
Клас будет базовым абсолютно для всех классов, и будет содержать интерфейсы для взаимодействия контролов между собой
Вложенный класс CMyEvent содержит название события и екземпляр который нужно вызвать с событием
*/
#pragma once
#include "stdafx.h"


class CBaseClass
{
	static void HendlMyEvent(CBaseClass* base, string metod);

public:
	CBaseClass(void);
	virtual ~CBaseClass(void);

	class CMyEvent
	{
        CBaseClass* base; //Указатель на екземпляр базового класса который должен вызвать свой метод
        string metod;     //название метода

	public:
		CMyEvent(void);
		~CMyEvent(void);

		void Run();
		void SetRunMetod(CBaseClass* _base, string _metod);
	};

	virtual void RunMyEvent(string metod) = 0;
};

