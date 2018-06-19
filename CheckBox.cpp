#pragma once
#include "StdAfx.h"


CCheckBox::CCheckBox( CInit& ini, char* pOn, char* pOff, CRadioBox* radioB/* = nullptr*/, wchar_t* text /*= L""*/, int H /*= 18 */ )
	: CCheck(ini, pOn, pOff, text, H)
{
	losPr = true;
	radioBox = radioB;
}


CCheckBox::~CCheckBox(void)
{
}

//************* VIRTUAL ***************
//Отобразить екзепляр
void CCheckBox::Draw() //virtual
{
	if(GetVisible())
		DrawCheck();
}

//Обработчик событий
void CCheckBox::HendlerEvent() //virtual
{
}

//екземпляр получил фокус
void CCheckBox::ReceiveFocus() //virtual
{
	Text.TextSetFocus();
	SetFocus();
}

//екземпляр потерял фокус
void CCheckBox::LoseFocus() //virtual
{
	Text.TextLostFocus();
	ResetFocus();
}

//екземпляр получил Hover
void CCheckBox::ReceiveHover() //virtual
{
	SetHover();
}

//екземпляр потерял Hover
void CCheckBox::LoseHover() //virtual
{
	ResetHover();
}

//екземпляр получил Press
void CCheckBox::ReceivePress() //virtual
{
	if(losPr)
	{
		losPr = false;
		if(radioBox == nullptr)
			SetChecked(!GetChecked());
		else
			radioBox->SetChecked(this);
	}
	SetPress();
}

//екземпляр потерял Press
void CCheckBox::LosePress() //virtual
{
	losPr = true;
	ResetPress();
}

//**** End VIRTUAL ***************

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CCheckBox::RunMyEvent( string metod )
{

}
//********** End ****
