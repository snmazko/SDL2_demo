#pragma once
#include "stdafx.h"


CBaseClass::CBaseClass(void)
{

}


CBaseClass::~CBaseClass(void)
{
}

CBaseClass::CMyEvent::CMyEvent( void )
{
	base = nullptr;
}

CBaseClass::CMyEvent::~CMyEvent( void )
{

}

void CBaseClass::HendlMyEvent( CBaseClass* base, string metod )
{
	if(base != nullptr && metod != "")
		base->RunMyEvent(metod);
}

void CBaseClass::CMyEvent::Run()
{
	if(base != nullptr && metod != "")
		HendlMyEvent(base, metod);
}

void CBaseClass::CMyEvent::SetRunMetod( CBaseClass* _base, string _metod )
{
	base = _base;
	metod = _metod;
}