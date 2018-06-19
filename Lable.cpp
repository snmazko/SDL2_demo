#pragma once
#include "StdAfx.h"


CLable::CLable( CInit& ini, wchar_t* text)/*Конструктор */
	:CGraphics(ini), Text(GetRenderer())
{
	SetText( text );
}

CLable::~CLable(void)
{
}

//************* VIRTUAL ***************
//Отобразить екзепляр
void CLable::Draw() //virtual
{
	if(GetVisible())
	{
		GraphicsDrawFon();
		GraphicsDrawBorder();

		Text.SetRectDst(GetPointDest());
		Text.DrawText();
	}
}

//Обработчик событий
void CLable::HendlerEvent()	//virtual
{

}

//екземпляр получил фокус
void CLable::ReceiveFocus() //virtual
{
	SetFocus();
}

//екземпляр потерял фокус
void CLable::LoseFocus() //virtual
{
	ResetFocus();
}

//екземпляр получил Hover
void CLable::ReceiveHover() //virtual
{
	SetHover();
}

//екземпляр потерял Hover
void CLable::LoseHover() //virtual
{
	ResetHover();
}

//екземпляр получил Press
void CLable::ReceivePress() //virtual
{
	SetPress();
}

//екземпляр потерял Press
void CLable::LosePress() //virtual
{
	ResetPress();
}

//**** End VIRTUAL ***************

void CLable::SetFontName( char* name )
{
	Text.SetFileFont( name );
	BildRect();
}

void CLable::SetFontSize( int size )
{
	Text.SetPtsize( size );
	BildRect();
}

void CLable::SetFontColor( SDL_Color* color )
{
	Text.SetFontColor( *color );
}

void CLable::SetFontColor( int r, int g, int b, int a )
{
	Text.SetFontColor(r, g, b, a);
}

void CLable::SetFontStyle( int style )
{
	Text.SetStyleFont( style );
	BildRect();
}

void CLable::SetText( wchar_t* text)
{
	Text.SetText( text );
	BildRect();
}

void CLable::SetFontParam( char* font, int size, SDL_Color* color )
{
	Text.SetFontParam(font, size, color);
	BildRect();
}

void CLable::BildRect()
{
	SDL_Rect r = Text.GetRectSrc();
	SDL_Point p = GetPointDest();
	SetRectSrc(r);
	SetWH(r.w, r.h);
	Text.SetRectDst(p.x, p.y, r.w, r.h);
}

wchar_t* CLable::GetTextW() const
{
	return Text.GetTextW();
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CLable::RunMyEvent( string metod )
{

}
//********** End ****
