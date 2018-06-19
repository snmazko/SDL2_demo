#pragma once
#include "stdafx.h"


CMyEvent::CMyEvent(void)
{
	pFun = nullptr;
	base = nullptr;
}


CMyEvent::~CMyEvent(void)
{

}

void CMyEvent::Run()
{
	if(pFun != nullptr && base != nullptr && metod != "")
		pFun(base, metod);
}

void CMyEvent::SetMetod( void (*_pFun)(CBaseClass*, string), CBaseClass* _base, string _metod )
{
	pFun = _pFun;
	base = _base;
	metod = _metod;
}

void CMyEvent::SetMetod( string _metod )
{
	metod = _metod;
}

void CMyEvent::SetMetod( CBaseClass* _base )
{
	base = _base;
}