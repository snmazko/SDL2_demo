#include "stdafx.h"

CGraphics* CGraphics::focus = nullptr;
CGraphics* CGraphics::hover = nullptr;
CGraphics* CGraphics::press = nullptr;

CGraphics::CGraphics(CInit& ini)
	: init(ini)
{
	visible = false;
    width = height = 0;                                 //общий размер ректа
    rectSrc.x = rectSrc.y = rectSrc.w = rectSrc.h = 0;  //прямоугольник ректа который будет отображен на рендере
	pointDest.x = pointDest.y = 0;//точка на рендере которая будет вершиной прямоугольника для отображения rectSrc

	//**** параметры рамки ректа ***
    borderLeft = false;       //true - отображать левую границу, false - граница не отображается
    borderLeftThickness = 0;  // толщина левой границы
	borderLeftColor.r = borderLeftColor.g = borderLeftColor.b = borderLeftColor.a = 100;//Цвет левой границы ректа

	borderRight = false;
	borderRightThickness = 0;
	borderRightColor.r = borderRightColor.g = borderRightColor.b = borderRightColor.a = 100;

	borderTop = false;
	borderTopThickness = 0;
	borderTopColor.r = borderTopColor.g = borderTopColor.b = borderTopColor.a = 100;

	borderBottom = false;
	borderBottomThickness = 0;
	borderBottomColor.r = borderBottomColor.g = borderBottomColor.b = borderBottomColor.a = 100;
	//*** END ***

	fFill = false;
	colorFill.r = colorFill.g = colorFill.b = colorFill.a = 100;//цвет заливки контрола
	SetRectWork();
}


CGraphics::~CGraphics(void)
{
}

//*** устанавливает флаг отображается екземпеляр или нет
void CGraphics::SetVisible( bool f )
{
	visible = f;
}

//********** общий размер ректа
void CGraphics::SetWidth( int w )
{
	width = w;
	SetRectWork();
}
void CGraphics::SetHeight( int h )
{
	height = h;
	SetRectWork();
}
void CGraphics::SetWH( int w, int h )
{
	height = h;
	width = w;
	SetRectWork();
}

//прямоугольник ректа который будет отображен на рендере
void CGraphics::SetRectSrc( SDL_Rect &r )
{
	rectSrc.x = r.x, rectSrc.y = r.y, rectSrc.h = r.h, rectSrc.w = r.w;
}

void CGraphics::SetRectSrc( int x, int y, int w, int h )
{
	SDL_Rect r = {x, y, w, h};
	SetRectSrc(r);
}

//точка на рендере которая будет вершиной прямоугольника для отображения rectSrc
void CGraphics::SetPointDest( SDL_Point &p )
{
	pointDest.x = p.x, pointDest.y = p.y;
	SetRectWork();
}

void CGraphics::SetPointDest( int x, int y )
{
	SDL_Point p = {x , y};
	SetPointDest(p);
}

//**** ОБРАБОТЧИКИ РАМКИ ЕЛЕМЕНТА
void CGraphics::SetBorderLeft( bool f, int thick /*= -1*/, SDL_Color* color /*= nullptr*/ )
{
	borderLeft = f;
	borderLeftThickness = thick < 0 ? borderLeftThickness : thick;
	
	if(color != nullptr)
	{
		borderLeftColor.r = color->r;
		borderLeftColor.g = color->g;
		borderLeftColor.b = color->b;
		borderLeftColor.a = color->a;
	}
	SetRectWork();
}

void CGraphics::SetBorderRight( bool f, int thick /*= -1*/, SDL_Color* color /*= nullptr*/ )
{
	borderRight = f;
	borderRightThickness = thick < 0 ? borderRightThickness : thick;

	if(color != nullptr)
	{
		borderRightColor.r = color->r;
		borderRightColor.g = color->g;
		borderRightColor.b = color->b;
		borderRightColor.a = color->a;
	}
	SetRectWork();
}

void CGraphics::SetBorderTop( bool f, int thick /*= -1*/, SDL_Color* color /*= nullptr*/ )
{
	borderTop = f;
	borderTopThickness = thick < 0 ? borderTopThickness : thick;

	if(color != nullptr)
	{
		borderTopColor.r = color->r;
		borderTopColor.g = color->g;
		borderTopColor.b = color->b;
		borderTopColor.a = color->a;
	}
	SetRectWork();
}

void CGraphics::SetBorderBottom( bool f, int thick /*= -1*/, SDL_Color* color /*= nullptr*/ )
{
	borderBottom = f;
	borderBottomThickness = thick < 0 ? borderBottomThickness : thick;

	if(color != nullptr)
	{
		borderBottomColor.r = color->r;
		borderBottomColor.g = color->g;
		borderBottomColor.b = color->b;
		borderBottomColor.a = color->a;
	}
	SetRectWork();
}

void CGraphics::SetBorder( bool f, int thick /*= -1*/, SDL_Color* color /*= nullptr*/ )
{
	SetBorderLeft(f, thick, color);
	SetBorderRight(f, thick, color);
	SetBorderTop(f, thick, color);
	SetBorderBottom(f, thick, color);
}

//**** Установка заливки елемента, возвращает текущий цвет заливки
SDL_Color CGraphics::FillColor( SDL_Color* color /*= nullptr*/ )
{
	SDL_Color c(colorFill);
	if(color != nullptr)
	{
		colorFill.r = color->r;
		colorFill.g = color->g;
		colorFill.b = color->b;
		colorFill.a = color->a;
	}
	return c;
}

bool CGraphics::FileExists( const char *fname )
{
	return _access(fname, 0) != -1;
}

//проверяет попадает ли точка в рект елемента расположенного на рендере
bool CGraphics::PointInRect( SDL_Point* p, CGraphics* gr )
{
	SDL_Rect r = gr->GetRectSrc();
	SDL_Point pDest = gr->GetPointDest();
	r.x = pDest.x;
	r.y = pDest.y;

	if(p->x >= r.x && p->x <= (r.x + r.w) && p->y >= r.y && p->y <= (r.y + r.h))
		return true;
	else
		return false;
}

//Установить фокус на елементе. Если фокус имеет другой елемент - вызвать его метод сброса фокуса, иначе установить фокус  на текущий елемент
//**** FOCUS ****
void CGraphics::SetFocus()
{
	if(focus != this)
	{
		if(focus != nullptr)
			focus->LoseFocus();//сбросить фокус
		focus = this;
		evSetFocus.Run();//Запустить событие
	}
}

//если фокус установлен на текущем елементе - обнуляем его
void CGraphics::ResetFocus()
{
	if(focus == this)
	{
		evResetFocus.Run();
		focus = nullptr;
	}
}

//Сброс фокуса с элемента который в данный момент в фокусе
void CGraphics::DropFocus()//static
{
	if(focus != nullptr)
		focus->LoseFocus();
	focus = nullptr;
}

//**** HOVER ****
void CGraphics::SetHover()
{
	if(hover != this)
	{
		if(hover != nullptr)
			hover->LoseHover();//сбросить hover
		hover = this;
		evSetHover.Run();
	}
}

void CGraphics::ResetHover()
{
	if(hover == this)
	{
		evResetHover.Run();
		hover = nullptr;
	}
}

void CGraphics::DropHover()//static
{
	if(hover != nullptr)
		hover->LoseHover();
	hover = nullptr;
}

//**** PRESS ****
void CGraphics::SetPress()
{
	if(press != this)
	{
		if(press != nullptr)
			press->LosePress();//сбросить press
		press = this;
		evSetPress.Run();
	}
}

void CGraphics::ResetPress()
{
	if(press == this)
	{
		evResetPress.Run();
		press = nullptr;
	}
}

void CGraphics::DropPress()//static
{
	if(press != nullptr)
		press->LosePress();
	press = nullptr;
}

//Устанавливает цвет в рендере, если он передается и возвращает текущий цвет рендера
SDL_Color CGraphics::RenderDrawColor( SDL_Color* color/* = nullptr */ )
{
	SDL_Color colorOld;
	colorOld.r = 100, colorOld.g = 100, colorOld.b = 100, colorOld.a = 100;
	SDL_GetRenderDrawColor(init.GetRenderer(), &colorOld.r, &colorOld.g, &colorOld.b, &colorOld.a);
	if(color != nullptr)
		SDL_SetRenderDrawColor( init.GetRenderer(), color->r, color->g, color->b, color->a );
	return colorOld;
}

void CGraphics::GraphicsDrawFon()
{
	if(fFill)
	{
		SDL_Color colorOld = RenderDrawColor();//получить текущий цвет

		//*** Отобразить заливку ***
		//Установить цвет
		RenderDrawColor(&FillColor());
		//Залить рект цветом заливки
		SDL_Rect r = {pointDest.x, pointDest.y, width, height};
		SDL_RenderFillRect(init.GetRenderer(), &r);

		RenderDrawColor(&colorOld);//вернуть цвет по умолчанию
	}
}

void CGraphics::GraphicsDrawBorder()
{
	SDL_Color colorOld = RenderDrawColor();//получить текущий цвет

	//*** Отобразить левую границу  ***
	if(borderLeft)
	{
		SDL_Rect re = { pointDest.x, pointDest.y, borderLeftThickness, height	};			
		RenderDrawColor(&borderLeftColor);//Установить цвет			
		SDL_RenderFillRect(init.GetRenderer(), &re);//Залить рект цветом заливки
	}

	//*** Отобразить правую границу  ***
	if(borderRight)
	{
		SDL_Rect re = { pointDest.x + width - borderRightThickness, pointDest.y, borderRightThickness, height	};			
		RenderDrawColor(&borderRightColor);//Установить цвет			
		SDL_RenderFillRect(init.GetRenderer(), &re);//Залить рект цветом заливки
	}

	//*** Отобразить верхнюю границу  ***
	if(borderTop)
	{
		SDL_Rect re = { pointDest.x, pointDest.y, width, borderTopThickness };
		RenderDrawColor(&borderTopColor);//Установить цвет			
		SDL_RenderFillRect(init.GetRenderer(), &re);//Залить рект цветом заливки
	}

	//*** Отобразить нижнюю границу  ***
	if(borderBottom)
	{
		SDL_Rect re = { pointDest.x, pointDest.y + height - borderBottomThickness, width, borderBottomThickness };
		RenderDrawColor(&borderBottomColor);//Установить цвет			
		SDL_RenderFillRect(init.GetRenderer(), &re);//Залить рект цветом заливки
	}
		
	RenderDrawColor(&colorOld);//вернуть цвет по умолчанию
}

void CGraphics::SetIsFill( bool f )
{
	fFill = f;
}

//проверяет перекрываются ли прямоугольники графических Элементов, записывает в переданную переменную рект перекрытия
bool CGraphics::IntersectRect( CGraphics* gr, SDL_Rect* re /*= nullptr*/ )
{
	SDL_Point p = gr->GetPointDest();
	SDL_Rect r = {p.x, p.y, gr->GetWidth(), gr->GetHeight()};

	return IntersectRect( &r, re /*= nullptr*/ );
}

bool CGraphics::IntersectRect( SDL_Rect* rDest, SDL_Rect* re /*= nullptr*/ )
{
	SDL_Rect r1 = {pointDest.x, pointDest.y, width, height};

	SDL_Rect res;

	SDL_bool fl = SDL_IntersectRect(&r1, rDest, &res);

	if(re != nullptr)
	{
		re->x = res.x;
		re->y = res.y;
		re->w = res.w;
		re->h = res.h;
	}

	return fl == SDL_TRUE;
}

//разместить второй елемент по центру первого
void CGraphics::SetCenterRect( CGraphics* gen, CGraphics* chaild )
{
	//Прямоугольник GENERAL
	SDL_Point p1 = gen->GetPointDest();
	SDL_Rect dG = {p1.x, p1.y, gen->GetWidth(), gen->GetHeight()};

	//Прямоугольник CHAILD
	SDL_Point p2 = gen->GetPointDest();
	SDL_Rect dC = {p2.x, p2.y, chaild->GetWidth(), chaild->GetHeight()};

	dC.x = dG.x + (dG.w/2) - (dC.w/2);
	dC.y = dG.y + (dG.h/2) - (dC.h/2);

	SDL_Point pCh = {dC.x, dC.y};
	chaild->SetPointDest(pCh);
}

void CGraphics::SetRectWork()
{
	rectWork.x = pointDest.x + borderLeftThickness;
	rectWork.y = pointDest.y + borderTopThickness;
	rectWork.w = width - borderLeftThickness - borderRightThickness;
	rectWork.h = height - borderTopThickness - borderBottomThickness;
}
