#include "StdAfx.h"

CCaret* CCaret::currentCaret = nullptr;


//************ КОНСТРУКТОР ПО УМОЛЧАНИЮ (ПУСТОЙ) *****************
CCaret::CCaret( SDL_Renderer* rend, SDL_Rect* Rect /*= nullptr*/, SDL_Color* Color /*= nullptr*/, Uint32 Delay /*= 400*/ )
{
#ifdef _DEBUG
	printf("Вызван конструктор по умолчанию класса CCaret\n");
#endif

	renderer = rend;

	if(Rect == nullptr)
		caretRect.x = 0, caretRect.y = 0, caretRect.w = 1, caretRect.h = 14;
	else
		caretRect = *Rect;

	if(Color == nullptr)
		caretColor.r = 0, caretColor.g = 0, caretColor.b = 0, caretColor.a = 255;
	else
		caretColor = NormalColor(*Color);

	fShow = false;
	timeDelay = Delay;
	fActivCaret = false;
	timeCheck = SDL_GetTicks();
}

//************ ДЕСТРУКТОР *****************
CCaret::~CCaret(void)
{
	if(currentCaret == this)
		currentCaret = nullptr;
}

Uint8 CCaret::NormalColor( Uint8 t )
{
	Uint8 v;
	v = t < 0 ? 0 : t;
	v = v > 255 ? 255 : v;
	return v;
}

SDL_Color CCaret::NormalColor( SDL_Color t )
{
	SDL_Color ret;
	ret.r = NormalColor(t.r);
	ret.g = NormalColor(t.g);
	ret.b = NormalColor(t.b);
	ret.a = NormalColor(t.a);
	return ret;
}

void CCaret::SetCaretColor( SDL_Color color )
{
	caretColor.r = NormalColor(color.r);
	caretColor.g = NormalColor(color.g);
	caretColor.b = NormalColor(color.b);
	caretColor.a = NormalColor(color.a);
}

void CCaret::SetCaretColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_Color color = {r, g, b, a};
	SetCaretColor(color);
}

void CCaret::SetCaretColor( int r, int g, int b, int a )
{
	SetCaretColor( static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a) );
}

void CCaret::SetCaretRect( SDL_Rect r )
{
	SetCaretRect( r.x, r.y, r.w, r.h );
}

void CCaret::SetCaretRect( int x, int y, int w, int h )
{
	caretRect.x = x;
	caretRect.y = y;
	caretRect.w = w;
	caretRect.h = h;
}

//активировать каретку и сделать ее текущей для отобржения
void CCaret::SetActivCaret( bool f )
{
	fActivCaret = f;
	if(f)
	{
		if(currentCaret != nullptr && currentCaret != this)
			currentCaret->SetActivCaret(false);
		currentCaret = this;
	}
}

//Задержка моргания каретки больше 10 и меньше 100
void CCaret::SetTimeDelay( Uint32 delay )
{
	timeDelay = delay < 10 ? 10 : delay;
	timeDelay = delay > 100 ? 100 : delay;
}

void CCaret::DrawCaret()
{
	if(fActivCaret)
	{
		if(fShow)
		{
			//получить текущий цвет
			SDL_Color colorOld;
			SDL_GetRenderDrawColor(renderer, &colorOld.r, &colorOld.g, &colorOld.b, &colorOld.a);

			//установить цвет заливки Каретки
			SDL_SetRenderDrawColor( renderer, caretColor.r, caretColor.g, caretColor.b, caretColor.a );
			//Отобразить каретку на рендере
			SDL_RenderFillRect(renderer, &caretRect);

			//вернуть цвет по умолчанию
			SDL_SetRenderDrawColor( renderer, colorOld.r, colorOld.g, colorOld.b, colorOld.a );
		}

		if(timeCheck + timeDelay < SDL_GetTicks())
		{
			fShow = !fShow;
			timeCheck = SDL_GetTicks();
		}
	}
}
