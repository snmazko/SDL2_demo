#pragma once
#include "stdafx.h"


class CMyEvent
{
	void (*pFun)(CBaseClass* _base, string _metod);//указатель на статический метод класса который вызовет нужный метод обработки
    CBaseClass* base; //Указатель на екземпляр базового класса который должен вызвать свой метод
    string metod;     //название метода

public:
	CMyEvent(void);
	~CMyEvent(void);

	void Run();
	void SetMetod(void (*_pFun)(CBaseClass*, string), CBaseClass* _base, string _metod);
	void SetMetod(string _metod);
	void SetMetod(CBaseClass* _base);
};

