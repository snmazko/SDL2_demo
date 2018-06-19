#include "StdAfx.h"


//************ КОНСТРУКТОР *****************
CTile::CTile( CInit& ini, char* pImage /*= nullptr*/, char* pImageHover /*= nullptr*/, char* pImagePress /*= nullptr*/, char* pImageHoverPress /*= nullptr */ )
	: CImage4Back( ini, pImage, pImageHover, pImagePress, pImageHoverPress ),
	Text(ini.GetRenderer()),
	fMoved(true)
{
	deltaX = 0;
	deltaY = 0;
}

//************ ДЕСТРУКТОР *****************
CTile::~CTile()
{

}

//******** END ***********

void CTile::SetText(wchar_t* text)
{
	Text.SetText(text);
}

//Разместить текст по центру вертикально и горизонатально, если не влазит - подобрать размер шрифта
void CTile::TextInRect()
{
	if(Text.GetFlag(Text.MYF_INFO_INIT))
	{
		SDL_Rect rSrc = GetRectSrc();
		SDL_Point pDest = GetPointDest();

		//поулучить размеры строки
		int wText = Text.GetW();
		int hText = Text.GetH();

		//обрезать высоту и ширину принимающего ректа до размеров контрола
		wText = wText > rSrc.w ? rSrc.w : wText;
		hText = hText > rSrc.h ? rSrc.h : hText;

		//получить начало прямоугольника текста по X и Y чтобы он был по центру
		int y = pDest.y + (rSrc.h / 2) - (hText / 2);
		int x = pDest.x + (rSrc.w / 2) - (wText / 2);		

		Text.SetRectDst(x, y, wText, hText);//Задать прямоугольник на рендере в который будет выведен текст
		Text.SetRectSrc(0, 0, wText, hText);//Задать прямоугоьник изображения из текстуры текста который нужно вывести
	}
#ifdef _DEBUG
	else
		cout << "Внимание! Вызов CTile::TextInRect() при не инициалзированном шрифте\n" << endl;
#endif
}

void CTile::MuveTile()
{
	int MouseX, MouseY;
	SDL_GetMouseState(&MouseX, &MouseY);//получить положение мышки
	SDL_Point p = GetPointDest();
	p.x = MouseX - deltaX;
	p.y = MouseY - deltaY;
	SetPointDest( p );
}

void CTile::SetDeltaXY()
{
	int MouseX, MouseY;
	SDL_GetMouseState(&MouseX, &MouseY);//получить положение мышки
	SDL_Point p = GetPointDest();
	deltaX = MouseX - p.x;
	deltaY = MouseY - p.y;
}
//************* VIRTUAL ***************
//Отобразить екзепляр
void CTile::Draw()												//virtual
{
	if(GetVisible())
	{
		if(GetIsPress() && fMoved)
			MuveTile();

		SDL_Texture* texture = GetImage();
		SDL_Rect rDest = GetRectSrc();
		SDL_Point p = GetPointDest();
		rDest.x = p.x;
		rDest.y = p.y;

		if(texture == nullptr)//если нету текстуры картинки рисуем заливки
		{
			GraphicsDrawFon();
			GraphicsDrawBorder();
		}
		else
			SDL_RenderCopy(GetRenderer(), texture,  &GetRectSrc(),  &rDest);

		//Передвинуть текст и вывести
		TextInRect();
		Text.DrawText();
	}
}

//Обработчик событий
void CTile::HendlerEvent()	//virtual
{

}

//екземпляр получил фокус
void CTile::ReceiveFocus() //virtual
{
	SetFocus();
}

//екземпляр потерял фокус
void CTile::LoseFocus() //virtual
{
	ResetFocus();
}

//екземпляр получил Hover
void CTile::ReceiveHover() //virtual
{
	SetIsHover(true);//установить флаг что плитка под мышкой
	SetHover();
}

//екземпляр потерял Hover
void CTile::LoseHover()	//virtual
{
	SetIsHover(false);//установить флаг что плитка ушла с мышки
	ResetHover();
}

//екземпляр получил Press
void CTile::ReceivePress() //virtual
{
	SetIsPress(true);//поставить флаг что нажата кнопка мышки
	SetDeltaXY();
	SetPress();
}

//екземпляр потерял Press
void CTile::LosePress() //virtual
{
	SetIsPress(false);//поставить флаг что кнопку отжали
	ResetPress();
}

//**** End VIRTUAL ***************

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CTile::RunMyEvent( string metod )
{

}

//********** End ****
