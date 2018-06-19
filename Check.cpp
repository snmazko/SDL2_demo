#pragma once
#include "StdAfx.h"


CCheck::CCheck( CInit& ini, char* pOn, char* pOff, wchar_t* text /*= L""*/, int H /*= 18 */ )
	:CGraphics(ini), Text(GetRenderer(), text, H)
{
	indent = 10;//отступ от картинки до текста

	checked = false;

	pachFont = nullptr;
	size = H;
	colorFont = nullptr;

    textureImageOn = nullptr;	//указатель на текстуру картинки checked
    textureImageOff = nullptr;  //указатель на текстуру картинки не checked
    pachImageOn = nullptr;		//путь к файлу картинки checked
    pachImageOff = nullptr;		//путь к файлу картинки не checked

	rectDestImg.x = rectDestImg.y = rectDestImg.w = rectDestImg.h = 0;
	rectSrcImg.x = rectSrcImg.y = rectSrcImg.w = rectSrcImg.h = 0;

	SetImage(pOn, pOff);
}

CCheck::~CCheck(void)
{
	if(textureImageOn != nullptr)	SDL_DestroyTexture(textureImageOn); textureImageOn = nullptr;
	if(textureImageOff != nullptr)	SDL_DestroyTexture(textureImageOff); textureImageOff = nullptr;

	if(pachFont != nullptr) delete [] pachFont; pachFont = nullptr;
	if(colorFont != nullptr) delete colorFont; colorFont = nullptr;

	if(pachImageOn != nullptr) delete [] pachImageOn; pachImageOn = nullptr;
	if(pachImageOff != nullptr) delete [] pachImageOff; pachImageOff = nullptr;
}

void CCheck::SetIndent( int ind )
{
	indent = ind < 0 ? 0 : ind;
}

void CCheck::SetText( wchar_t* text )
{
	Text.SetText(text);
	TextAndImageInRect();
}

void CCheck::SetImage( char* pImageOn, char* pImageOff  )
{
	if(pImageOn != nullptr && pImageOff != nullptr )
	{
		if(FileExists(pImageOn) && FileExists(pImageOff))
		{
			//скопировать путь к файлу картинки On
			int n = strlen(pImageOn);
			if(pachImageOn != nullptr) delete [] pachImageOn;
			pachImageOn = new char[n + 1];
			strcpy_s(pachImageOn, n + 1, pImageOn);

			//скопировать путь к файлу картинки Off
			n = strlen(pImageOff);
			if(pachImageOff != nullptr) delete [] pachImageOff;
			pachImageOff = new char[n + 1];
			strcpy_s(pachImageOff, n + 1, pImageOff);

			if(textureImageOn != nullptr) SDL_DestroyTexture(textureImageOn);
			textureImageOn = nullptr;

			if(textureImageOff != nullptr) SDL_DestroyTexture(textureImageOff);
			textureImageOff = nullptr;

			textureImageOn = IMG_LoadTexture(GetRenderer(), pImageOn);

			textureImageOff = IMG_LoadTexture(GetRenderer(), pImageOff);

			//установить размеры прямоугольника на картинке который будет отображаться по размерам картинки textureImageOff
			Uint32 format;
			int access;
			int w = 0;
			int h = 0;
			if(0 == SDL_QueryTexture(textureImageOff, &format, &access, &w, &h))
			{
				rectDestImg.w = rectSrcImg.w = w;
				rectDestImg.h = rectSrcImg.h = h;
			}
#ifdef _DEBUG
			else
				printf("Ошибка в методе CCheck::SetImage! Функция SDL_QueryTexture вернула ошибку \n" );
#endif
			TextAndImageInRect();//разместить принимающие ректы
		}
#ifdef _DEBUG
		else
			printf("Ошибка в методе CCheck::SetImage! Отсутствует файл картинки \"%s\" либо \"%s\".\n", pImageOn, pImageOff);
#endif
	}
#ifdef _DEBUG
	else
		printf("Ошибка в методе CCheck::SetImage! Передан пустой указатель на путь к одной либо обоим картинкам \n");
#endif
}

void CCheck::TextAndImageInRect()
{
	//точка на рендере в которой будет верхний левый угол екземпляра
	SDL_Point pDest = GetPointDest();

	int hText = Text.GetH();
	int wText = Text.GetW();
	int hImg = rectSrcImg.h;
	int wImg = rectSrcImg.w;

	SDL_Rect rSrc = {0,0,0,0};
	rSrc.h = hText > hImg ? hText : hImg;
	rSrc.w = wText + wImg + indent;

	SetWH(rSrc.w, rSrc.h);//общий размер ректа
    SetRectSrc(rSrc);     //прямоугольник ректа который будет отображен на рендере

	//определить принимающий рект картинки
	rectDestImg.x = pDest.x;
	rectDestImg.y = pDest.y + (rSrc.h / 2) - (hImg / 2);//разместить картинку слева по центру
	rectDestImg.h = hImg;
	rectDestImg.w = wImg;

	//определить принимающий рект текста
	Text.SetRectDst(
        pDest.x + wImg + indent,              //разместить текст после картинки и отступа
        pDest.y + (rSrc.h / 2) - (hText / 2), //разместить текст вертикально по центру
		wText,
		hText	);

}

void CCheck::DrawCheck()
{
	if(checked)
	{
		if(textureImageOn != nullptr)
		{
			SDL_RenderCopy(GetRenderer(), textureImageOn,  &rectSrcImg,  &rectDestImg);
			Text.DrawText();
		}
#ifdef _DEBUG
		else
			cout << "Внимание! Вызов CCheck::DrawCheck.cpp при не инициалзированном textureImageOn\n" << endl;
#endif
	}
	else
	{
		if(textureImageOff != nullptr)
		{
			SDL_RenderCopy(GetRenderer(), textureImageOff,  &rectSrcImg,  &rectDestImg);
			Text.DrawText();
		}
#ifdef _DEBUG
		else
			cout << "Внимание! Вызов CCheck::DrawCheck.cpp при не инициалзированном textureImageOff\n" << endl;
#endif
	}
}

//Переопределение методов родителя
void CCheck::SetPointDest( SDL_Point &p )
{
	CGraphics::SetPointDest(p);
	TextAndImageInRect();
}

void CCheck::SetPointDest( int x, int y )
{
	CGraphics::SetPointDest(x, y);
	TextAndImageInRect();
}

void CCheck::SetPachFont( char* font )
{
	Text.SetFileFont(font);
	TextAndImageInRect();
}

void CCheck::SetFontSize( int size )
{
	Text.SetPtsize(size);
	TextAndImageInRect();
}

void CCheck::SetColorFont( SDL_Color* color )
{
	Text.SetFontColor(*color);
}

void CCheck::SetFont( char* font, int size, SDL_Color* color )
{
	Text.SetFontParam(font, size, color);
	TextAndImageInRect();
}

void CCheck::SetChecked( bool f )
{
	if(checked != f)
	{
		checked = f;
		if(f) evSetChecked.Run();
		else evUnSetChecked.Run();
	}
}

//**** End VIRTUAL ***************
