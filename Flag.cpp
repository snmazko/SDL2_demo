#include "StdAfx.h"

//********** ИНИЦИАЛИЗАЦИЯ СТАТИЧЕСКИХ ПОЛЕЙ *****
CFlag* CFlag::pMouseDown = nullptr;
CFlag* CFlag::pMouseHover = nullptr;
// ********* End *********

CFlag::CFlag(void)
{
	isMuved = false;
	isVisible = true;
	mouseDown = false;
	mouseMuve = false;
	isHover = false;
    isPress = false;      //Кнопка зажата
	tempPress = false;
    onDoublePress = true; //true - кнопка отжимаестя сразу
    tempPressUp = true;   //true - на кнопке не произошло отжатие
}

CFlag::CFlag( const CFlag& Cc )
{
	isMuved = Cc.GetIsMuved();
	isVisible = Cc.GetIsVisible();
	mouseDown = Cc.GetMouseDown();
	mouseMuve = Cc.GetMouseMuve();
	isHover = Cc.GetIsHover();
    isPress = Cc.GetIsPress();              //Кнопка зажата
	tempPress = false;
    onDoublePress = Cc.GetOnDoublePress();  //true - кнопка отжимаестя сразу
	tempPressUp = true;
}

CFlag& CFlag::operator=( const CFlag& Cc )
{
	if(this == &Cc)
		return *this;

	isMuved = Cc.GetIsMuved();
	isVisible = Cc.GetIsVisible();
	mouseDown = Cc.GetMouseDown();
	mouseMuve = Cc.GetMouseMuve();
	isHover = Cc.GetIsHover();
    isPress = Cc.GetIsPress();              //Кнопка зажата
	tempPress = false;
    onDoublePress = Cc.GetOnDoublePress();  //true - кнопка отжимаестя сразу
	tempPressUp = true;

	return *this;
}

CFlag::~CFlag(void)
{

}

void CFlag::SetMouseDown( bool f )
{
	if(f)
	{
		if(pMouseDown != this)
		{
			if(pMouseDown != nullptr)
			{
				pMouseDown->mouseDown = false;
				pMouseDown->mouseMuve = false;
			}
			pMouseDown = this;
		}
		mouseDown = true;
		SetMouseMuve(true);
	}
	else
	{
		pMouseDown = pMouseDown == this ? nullptr : pMouseDown;
		mouseDown = false;
		SetMouseMuve(false);
	}
}

void CFlag::SetMouseMuve( bool f )
{
	if(isMuved)//если екземпляр не перемещаемый то флаг не обрабатывается и постаянно находится с false
		mouseMuve = f;
}

//static
//обрабатывает отпускание кнопи событие SDL_MOUSEBUTTONUP
void CFlag::MouseUp()
 {
	if(pMouseDown != nullptr)
	{
        pMouseDown->SetTempPressUp(true); //устанавливаем что произошло отжатие кнопки
		//обрабатываем флаги
        if(pMouseDown->GetOnDoublePress())  //если кнопка отжимается сразу
            pMouseDown->SetIsPress(false);  //отжимаем
		else
			pMouseDown->SetIsPress(!pMouseDown->GetTempPress());//инвертируем

		pMouseDown->mouseDown = false;
		pMouseDown->mouseMuve = false;
		pMouseDown = nullptr;
	}
}

void CFlag::MouseHover( CFlag* Cf )
{
	if(Cf != nullptr)
	{
		if(pMouseHover != Cf && pMouseHover != nullptr)
			pMouseHover->SetIsHover(false);
		pMouseHover = Cf;
		pMouseHover->SetIsHover(true);
	}
	else
		if(pMouseHover != nullptr)
		{
			pMouseHover->SetIsHover(false);
			pMouseHover = nullptr;
		}
}
