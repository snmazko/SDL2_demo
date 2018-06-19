#pragma once
#include "StdAfx.h"


CRadioBox::CRadioBox( CCell& c, int x/* = 0*/, int y/* = 0*/, char* font /*= nullptr*/, int size/*=26*/, SDL_Color* color /*= nullptr */ )
	: cell(c)
{
	pachFont = nullptr;
	colorFont = nullptr;
	checkedBox = nullptr;

	destX = x;
	destY = y;

	SetFont( font, size, color );
}

CRadioBox::~CRadioBox(void)
{
	if(pachFont != nullptr) delete[]pachFont;
	pachFont = nullptr;

	if(colorFont != nullptr) delete colorFont;
	colorFont = nullptr;

	vector<CCheckBox*>::iterator it;
	for(it = ListCheckBox.begin(); it != ListCheckBox.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
}

bool CRadioBox::FileExists( const char *fname )
{
	return _access(fname, 0) != -1;
}

void CRadioBox::SetPachFont( char* font )
{
	if(font != nullptr)
	{
		if(FileExists(font))
		{
			if(pachFont != nullptr) delete[]pachFont;
			pachFont = nullptr;

			int n = static_cast<int>(strlen(font));
			pachFont = new char[n + 1];
			strcpy_s(pachFont, n + 1, font);

			SetFontAll();
		}
#ifdef _DEBUG
		else
			printf("Ошибка в CRadioBox::SetPachFont! Отсутствует шрифт %s\n", font);
#endif
	}
}

void CRadioBox::SetFontSize( int size )
{
	this->size = size <= 0 ? 26 : size;
	SetFontAll();
}

void CRadioBox::SetColorFont( SDL_Color* color )
{
	if(color != nullptr)
	{
		if(colorFont != nullptr) delete colorFont;
		colorFont = nullptr;

		colorFont = new SDL_Color(*color);
		SetFontAll();
	}
}

void CRadioBox::SetFont( char* font, int size, SDL_Color* color )
{
//Установка шрифта
	if(font != nullptr)
	{
		if(FileExists(font))
		{
			if(pachFont != nullptr) delete[]pachFont;
			pachFont = nullptr;

			int n = static_cast<int>(strlen(font));
			pachFont = new char[n + 1];
			strcpy_s(pachFont, n + 1, font);
		}
#ifdef _DEBUG
		else
			printf("Ошибка в CRadioBox::SetFont! Отсутствует шрифт %s\n", font);
#endif
	}

//установка размера шрифта
	this->size = size <= 0 ? 26 : size;

//установка цвета шрифта
	if(color != nullptr)
	{
		if(colorFont != nullptr) delete colorFont;
		colorFont = nullptr;
		colorFont = new SDL_Color(*color);
	}

	SetFontAll();
}

void CRadioBox::SetFontAll()
{
	vector<CCheckBox*>::iterator it;
	for(it = ListCheckBox.begin(); it != ListCheckBox.end(); it++)
		(*it)->SetFont(pachFont, size, colorFont);
}

void CRadioBox::SetChecked( CCheckBox* param1 )
{
	if(checkedBox == nullptr)
	{
		checkedBox = param1;
		checkedBox->SetChecked(true);
	}
	else if(checkedBox != param1)
	{
		checkedBox->SetChecked(false);
		checkedBox = param1;
		checkedBox->SetChecked(true);
	}
}

void CRadioBox::Add( char* pOn, char* pOff, int x, int y, wchar_t* text /*= L""*/ )
{
	CCheckBox* temp = new CCheckBox(cell.GetInit(), pOn, pOff, this, text);
	temp->SetPointDest(x, y);
	temp->SetVisible(true);
    ListCheckBox.push_back(temp); //Добавить в лист чекбоксов
    cell.AddGraphics(temp);       //добавить на обработку в лист ячейки которой принадлежит данный радиобокс
}
