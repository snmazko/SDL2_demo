#include "StdAfx.h"


//************ КОНСТРУКТОРЫ *****************

CLineBox::CLineBox( CInit& ini, int w, int h )
	:CGraphics(ini), Text(GetRenderer())
{
#ifdef _DEBUG
	printf("Вызван конструктор класса CLineBox c 3 параметрами\n");
#endif

	Text.SetFCaretka(true);
	
    SetWH(w, h);          //общий размер ректа
    SetRectSrc(0,0,w,h);  //прямоугольник ректа который будет отображен на рендере
	SDL_Color color = {0, 100, 255, 255};
    SetBorder(true, 2, &color); //установить параметры рамки

    verticalAlign = CENTER;		//Вертикальное выравнивание текста в контрле
	horizontalAlign = LEFT;		//Горизонтальное выравнивание текста в контрле
	verticalIndent = 0;			//Отступ от края контрола по вертикали.
	horizontalIndent = 0;		//Отступ от края контрола по горизонтали.

	imageFonTexture = nullptr;
	imageFonPach = nullptr;
	
	fReturn = true;//флаг свидетельствует что кнопка ретурн после нажатия отпускалась
}

CLineBox::CLineBox( CInit& ini, char* pach )
	:CGraphics(ini), Text(GetRenderer())
{
#ifdef _DEBUG
	printf("Вызван конструктор класса CLineBox c 2 параметрами\n");
#endif

	Text.SetFCaretka(true);

    verticalAlign = CENTER;		//Вертикальное выравнивание текста в контрле
	horizontalAlign = LEFT;		//Горизонтальное выравнивание текста в контрле
	verticalIndent = 0;			//Отступ от края контрола по вертикали.
	horizontalIndent = 0;		//Отступ от края контрола по горизонтали.

	imageFonTexture = nullptr;
	imageFonPach = nullptr;

	SetImage( pach );

	fReturn = true;//флаг свидетельствует что кнопка ретурн после нажатия отпускалась
}
//******** END ***********

//************ ДЕСТРУКТОР *****************
CLineBox::~CLineBox()
{
	if(imageFonTexture != nullptr)	SDL_DestroyTexture(imageFonTexture); imageFonTexture = nullptr;

	if(imageFonPach != nullptr) delete [] imageFonPach; imageFonPach = nullptr;
}
//******** END ***********


//************* VIRTUAL ***************
//Отобразить екзепляр
void CLineBox::Draw() //virtual
{
	if(GetVisible())
	{
		SDL_Rect rDest = GetRectSrc();
		SDL_Point p = GetPointDest();
		rDest.x = p.x;
		rDest.y = p.y;

		if(imageFonTexture == nullptr)//если нету текстуры картинки рисуем заливки
		{
			GraphicsDrawFon();
			GraphicsDrawBorder();
		}
		else
			SDL_RenderCopy(GetRenderer(), imageFonTexture,  &GetRectSrc(),  &rDest);

		//Передвинуть текст и вывести
		TextInRect();
		Text.DrawText();
	}
}

//Обработчик событий
void CLineBox::HendlerEvent()	//virtual
{
	int MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);      //получить положение мышки
	SDL_Event* ev = GetEvent();
	switch(ev->type)
	{
	case SDL_KEYDOWN:
		if(ev->key.keysym.sym == SDLK_RETURN)
			SetReturn();
        Text.HendlerEvent(ev, MouseX, MouseY);  //запустить обработчик текста
		break;

	case SDL_KEYUP:
		if(ev->key.keysym.sym == SDLK_RETURN)
			UnsetReturn();
        Text.HendlerEvent(ev, MouseX, MouseY);  //запустить обработчик текста
		break;
	}
}

//екземпляр получил фокус
void CLineBox::ReceiveFocus() //virtual
{
	Text.TextSetFocus();
	SetFocus();
}

//екземпляр потерял фокус
void CLineBox::LoseFocus() //virtual
{
	Text.TextLostFocus();
	ResetFocus();
}

//екземпляр получил Hover
void CLineBox::ReceiveHover() //virtual
{
	SetHover();
}

//екземпляр потерял Hover
void CLineBox::LoseHover() //virtual
{
	ResetHover();
}

//екземпляр получил Press
void CLineBox::ReceivePress() //virtual
{
	SetPress();
}

//екземпляр потерял Press
void CLineBox::LosePress() //virtual
{
	ResetPress();
}

//**** End VIRTUAL ***************


void CLineBox::SetText( wchar_t* text )
{
	Text.SetText(text);
	TextInRect();
}

void CLineBox::TextInRect()
{
	if(Text.GetFlag(Text.MYF_INFO_INIT))
	{
		//точка на рендере в которой будет верхний левый угол екземпляра
		SDL_Point pDest = GetPointDest();

		//Размеры экземпляра
		int wGr = GetWidth();
		int hGr = GetHeight();

		//поулучить размеры строки
		int wT = Text.GetW();
		int hT = Text.GetH();

		//Рект на рендере за границы которого не должен выступать текст
		SDL_Rect rWork = GetRectWork();

		//** добавить границы отступов
		//вертикальные отступы
        if(verticalAlign == TOP) {
          rWork.y += verticalIndent;
          rWork.h -= verticalIndent;
          rWork.h = rWork.h < 0 ? 0 : rWork.h;
        } else if(verticalAlign == BOTTOM) {
          rWork.h -= verticalIndent;
          rWork.h = rWork.h < 0 ? 0 : rWork.h;
        }

		//горизонтальные отступы
        if(horizontalAlign == LEFT) {
          rWork.x += horizontalIndent;
          rWork.w -= horizontalIndent;
          rWork.w = rWork.w < 0 ? 0 : rWork.w;
        } else if(horizontalAlign == RIGHT) {
          rWork.w -= horizontalIndent;
          rWork.w = rWork.w < 0 ? 0 : rWork.w;
        }

		SDL_Rect rDestText = rWork;//рект на рендере который примет текст из rSrcText изначально он не должен выходить за пределы rWork
        SDL_Rect rSrcText;          //рект на текстуре текста который будет отображен в rDestText

// *****************************************************
		//обрезать высоту и ширину принимающего ректа по параметрам текста и самого экземпляра
		//Изначально будет выводится с крайнего левого угла рабочего прямоугольника
		rDestText.w = wT > rWork.w ? rWork.w : wT;
		rDestText.h = hT > rWork.h ? rWork.h : hT;

		//Получить рект который будет взят с текста для вывода на рендер где x = 0, y = по центру текста
		int destCentr = rDestText.y + (rDestText.h / 2);

		rSrcText.x = 0;
		rSrcText.y = destCentr + hT / 2 > rDestText.y + rDestText.h ? (hT / 2 - rDestText.h / 2) : 0;
		rSrcText.w = rDestText.w;
		rSrcText.h = rDestText.h;

		//Обработка вертикальных выравниваний
		if(verticalAlign == CENTER)
			rDestText.y = pDest.y + hGr / 2 - rDestText.h / 2;
		else if(verticalAlign == BOTTOM)
		{
			rDestText.y = rWork.y + rWork.h - rDestText.h;
		}

		//Обработка горизонтальных выравниваний
		if(horizontalAlign == CENTER)
			rDestText.x = pDest.x + wGr / 2 - rDestText.w / 2;
		else if(horizontalAlign == RIGHT)
		{
			rDestText.x = rWork.x + rWork.w - rDestText.w;
		}

		Text.SetRectDst(rDestText);//Задать прямоугольник на рендере в который будет выведен текст
		Text.SetRectSrc(rSrcText);//Задать прямоугоьник изображения из текстуры текста который нужно вывести
	}
#ifdef _DEBUG
	else
		cout << "Внимание! Вызов TextInRect() в CLineBox::LineBox.cpp при не инициалзированном шрифте\n" << endl;
#endif
}


void CLineBox::SetVerticalAlign( Align align )
{
	if(align == CENTER || align == TOP  || align == BOTTOM)
	{
		verticalAlign = align;
		TextInRect();
	}		
#ifdef _DEBUG
	else
		printf("Ошибка! Методу CLineBox::SetVerticalAlign() передан не верный параметр - %i\n", align);
#endif
}


void CLineBox::SetHorizontalAlign( Align align )
{
	if(align == CENTER || align == LEFT || align == RIGHT)
	{
		horizontalAlign = align;
		TextInRect();
	}
#ifdef _DEBUG
	else
		printf("Ошибка! Методу CLineBox::SetHorizontalAlign() передан не верный параметр - %i\n", align);
#endif
}


void CLineBox::SetVerticalIndent( int indent )
{
	verticalIndent = indent < 0 ? verticalIndent : indent;
	TextInRect();
}


void CLineBox::SetHorizontalIndent( int indent )
{
	horizontalIndent = indent < 0 ? horizontalIndent : indent;
	TextInRect();
}

void CLineBox::SetAlignAndIndent( Align vAlign, int vIndent, Align hAlign, int hIndent )
{
	//*** вертикальное выравнивание
	if(vAlign == CENTER || vAlign == TOP  || vAlign == BOTTOM)
		verticalAlign = vAlign;
#ifdef _DEBUG
	else
		printf("Ошибка! Методу CLineBox::SetAlignAndIndent() передан не верный параметр вертикального выравнивания - %i\n", vAlign);
#endif

	//*** вертикальный отступ
	verticalIndent = vIndent < 0 ? verticalIndent : vIndent;

	//*** горизонтальное выравнивание
	if(hAlign == CENTER || hAlign == LEFT || hAlign == RIGHT)
		horizontalAlign = hAlign;
#ifdef _DEBUG
	else
		printf("Ошибка! Методу CLineBox::SetHorizontalAlign() передан не верный параметр горизонтального выравнивания - %i\n", hAlign);
#endif

	//*** горизонтальный отступ
	horizontalIndent = hIndent < 0 ? horizontalIndent : hIndent;

	TextInRect();
}

void CLineBox::SetImage( char* pImage )
{
	if(pImage != nullptr)
	{
		if(FileExists(pImage))
		{
			//скопировать путь к файлу картинки
			int n = strlen(pImage);
			if(imageFonPach != nullptr)
				delete [] imageFonPach;
			imageFonPach = new char[n + 1];
			strcpy_s(imageFonPach, n + 1, pImage);

			if(imageFonTexture != nullptr)
				SDL_DestroyTexture(imageFonTexture);
			imageFonTexture = nullptr;

			imageFonTexture = IMG_LoadTexture(GetRenderer(), pImage);

			//установить размеры прямоугольника на картинке который будет отображаться по размерам переданной картинке
			Uint32 format;
			int access;
			int	w = 0;
			int h = 0;
			if(0 == SDL_QueryTexture(imageFonTexture, &format, &access, &w, &h))
			{
				SetWH(w,h);//общий размер ректа
				SetRectSrc(0,0,w,h);//прямоугольник ректа который будет отображен на рендере
			}
#ifdef _DEBUG
			else
				printf("Ошибка в методе CLineBox::SetImage! Функция SDL_QueryTexture вернула ошибку \n" );
#endif
		}
#ifdef _DEBUG
		else
			printf("Ошибка в методе CLineBox::SetImage! Отсутствует файл картинки %s\n", pImage);
#endif
	}
#ifdef _DEBUG
	else
		printf("Ошибка в методе CLineBox::SetImage! Передан пустой указатель на путь к картинке фона \n");
#endif
}

void CLineBox::SetReturn()
{
	if(fReturn)
	{
		fReturn = false;
		evSetReturn.Run();
	}
}

void CLineBox::UnsetReturn()
{
	if(!fReturn)
	{
		fReturn = true;
		evUnsetReturn.Run();
	}
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CLineBox::RunMyEvent( string metod )
{

}
//********** End ****
