#include "StdAfx.h"

//************ КОНСТРУКТОР ПО УМОЛЧАНИЮ (ПУСТОЙ) *****************
CText::CText( SDL_Renderer* renderer, wchar_t* text/*=L""*/, int size/*=16*/, SDL_Color* color /*= nullptr*/, char* file /*= nullptr*/ )
{
	FLAG_INIT = MYF_RENDERER_INIT;
	countFlag = 4;//количество флагов инициализации не включая последний общий флаг
	//GetFlag(MYF_RENDERER_INIT);

	this->renderer = renderer;

    caret = new CCaret(renderer); //Указатель на каретку текста
    fCaretka = false;             //true - текст работает с кареткой, false - каретка не отображается

	//елементы textList будут содержать длинну сивола строки
	//первый елемент имеет длинну 0 и соответсвует значению caretIndex = -1, что свидетельствует о 
	//нахождении каретки перед всеми символами строки, последний елемент нужен для корректной вставки
    textList.push_back(0);  //начало строки
    textList.push_back(0);  //конец строки

	caretIterator = ++textList.begin();//Итератор указывающий на элемент за которым находится каретка
	//установить на второй елемент списка

	caretIndex = -1;//Индекс текущего символа из строки где -1 указывает на положение перед 0 символом
	caretOffsetX = 0;//смещение позиции каретки по Х в пикселах для отображения в рендере

	texture = nullptr;
	info = nullptr;
	font = nullptr;
	fileFont = nullptr;

	textW = nullptr;
	textU = nullptr;

	ptsize = size;

	if(color == nullptr)
		fontColor.r = 250, fontColor.g = 250, fontColor.b = 250, fontColor.a = 255;
	else
		fontColor = NormalColor(*color);
	
	char* fl = "Fonts/Favorit.ttf";
	if(file != nullptr)
		fl = file;
	int n = static_cast<int>(strlen(fl));


	if(!FileExists(fl))
	{
		#ifdef _DEBUG
			printf("Ошибка! Отсутствует шрифт %s\n", fl);
		#endif
	}
	else
	{
		fileFont = new char[n + 1];
		strcpy_s(fileFont, n + 1, fl);
	}
	SetText(text);
}

//************ КОНСТРУКТОР КОПИРОВАНИЯ *****************
CText::CText( const CText& Cc )
{
#ifdef _DEBUG
	printf("Вызван конструктор копирования класса CText\n");
#endif

	renderer = Cc.GetRenderer();
	ptsize = Cc.GetPtsize();
	fontColor = GetFontColor();

	int n = static_cast<int>(strlen(Cc.GetFileFont()));
	fileFont = new char[n + 1];
	strcpy_s(fileFont, n + 1, Cc.GetFileFont());
	fileFont[n] = '\0';

	rectSrc = Cc.GetRectSrc();
	rectDst = Cc.GetRectDst();
	SetText(Cc.GetTextW());
}


//************ ПЕРЕГРУЗКА ОПЕРАТОРА = *****************
CText& CText::operator=( const CText& Cc )
{
#ifdef _DEBUG
	printf("Перегрузка оператора = класса CText\n");
#endif

	if(this == &Cc)
		return *this;

	renderer = Cc.GetRenderer();
	ptsize = Cc.GetPtsize();
	fontColor = GetFontColor();

	//caret = Cc.caret;

	int n = static_cast<int>(strlen(Cc.GetFileFont()));
	fileFont = new char[n + 1];
	strcpy_s(fileFont, n + 1, Cc.GetFileFont());
	fileFont[n] = '\0';

	rectSrc = Cc.GetRectSrc();
	rectDst = Cc.GetRectDst();
	SetText(Cc.GetTextW());

	return *this;
}


//************ ДЕСТРУКТОР *****************
CText::~CText(void)
{
	if(texture != nullptr)
        SDL_DestroyTexture(texture);  //освободить текстуру
	texture = nullptr;

	if(info != nullptr)
        SDL_FreeSurface(info);        //освободить структуру
	info = nullptr;

	if(font != nullptr)
        TTF_CloseFont(font);          //освободить шрифт
	font = nullptr;

	if(fileFont != nullptr)
        delete fileFont;              //освободить указатель на путь к файлу шрифта
	fileFont = nullptr;

	if(textW != nullptr)
		delete textW;
	textW = nullptr;

	if(textU != nullptr)
		delete textU;
	textU = nullptr;

	delete caret;
	caret = nullptr;
}

bool CText::FileExists( const char *fname )
{
	return _access(fname, 0) != -1;
}


Uint16* CText::NormalText( wchar_t* text )
{
	int n = static_cast<int>(wcslen(text));
	Uint16* Text = new Uint16[n+1];
	for(int i = 0; i < n; ++i)
		Text[i] = text[i];
	Text[n] = '\0';
	return Text;
}


void CText::SetTexture()
{
    if(GetFlag(MYF_INFO_INIT))      //проверка инфо
	{
        if(GetFlag(MYF_FONT_INIT))  //проверка фонт
		{
			if(GetFlag(MYF_TEXTURE_INIT))
			{
				SDL_DestroyTexture(texture);//освободить текстуру
				texture = nullptr;
			}
			texture = SDL_CreateTextureFromSurface(renderer, info);
			if(texture == 0)
			{
				texture = nullptr;
				SetFlag(MYF_TEXTURE_INIT, 0);
	#ifdef _DEBUG
				cout << "Ошибка! SDL_CreateTextureFromSurface вернула 0\n" << endl;
	#endif
			}
			else
				SetFlag(MYF_TEXTURE_INIT);
		}
#ifdef _DEBUG
		else
			cout << "Внимание! Вызов SetTexture() в Text.cpp при не инициалзированном font\n" << endl;
#endif
	}
#ifdef _DEBUG
	else
		cout << "Внимание! Вызов SetTexture() в Text.cpp при не инициалзированном info\n" << endl;
#endif
}

void CText::SetInfo()
{
	if(GetFlag(MYF_FONT_INIT))
	{
		if(textU != nullptr)
		{
            if(GetFlag(MYF_INFO_INIT))  //если структура инициализирована
			{
                SDL_FreeSurface(info);  //освободить структуру
				info = nullptr;
			}
			//создание поверхности с текстом обычного текста
			if(0 == wcslen(textW))
			{
				Uint16* text = NormalText(L" ");
				info = TTF_RenderUNICODE_Blended(font, text, fontColor);
			}
			else
				info = TTF_RenderUNICODE_Blended(font, textU, fontColor);
			if(info == NULL)
			{
				info = nullptr;
				SetFlag(MYF_INFO_INIT, 0);
#ifdef _DEBUG
				cout << "Ошибка! TTF_RenderUNICODE_Blended вернула NULL\n" << endl;
#endif
			}
			else
			{
				SetFlag(MYF_INFO_INIT);
				SetRectSrc(0, 0, info->w, info->h);
				caret->SetCaretH(info->h);
				SetTexture();
			}
		}
#ifdef _DEBUG
		else
			cout << "Внимание! Вызов SetInfo() в Text.cpp при textU=nullptr\n" << endl;
#endif
	}
#ifdef _DEBUG
	else
		cout << "Внимание! Вызов SetInfo() в Text.cpp при не инициалзированном шрифте\n" << endl;
#endif
}

void CText::SetFont()
{
	if(fileFont != nullptr)//Если существует путь к шрифту и сам файл шрифта по этому пути
	{
        if(GetFlag(MYF_FONT_INIT))  //если шрифт инициализирован
		{
            TTF_CloseFont(font);    //освободить шрифт
			font = nullptr;
		}

		font = TTF_OpenFont(fileFont, ptsize);
		SetFlag(MYF_FONT_INIT);
		caret->SetCaretH(TTF_FontHeight(font));

		SetInfo();
	}
#ifdef _DEBUG
	else
	{
		cout << "Внимание! Вызов SetFont() в Text.cpp при не инициалзированном пути к шрифту\n" << endl;
	}
#endif
}

//метод private
void CText::SetText( Uint16* text )
{
	textU = text;
	if(GetFlag(MYF_FONT_INIT))
		SetInfo();
	else
		SetFont();
    if(GetFlag(MYF_INFO_INIT))  //если структура инициализирована ставим каретку за последним символом
	{
        caretOffsetX = 0;       //установить смещение каретки за последний символ
		if(textU != nullptr)
		{
			caretIndex = wcslen(textW) - 1;//установить индекс на последний символ
			//сбросить лист размеров и записать его заново
			textList.clear();
            textList.push_back(0);  //начало строки
            textList.push_back(0);  //конец строки
            caretIterator = ++textList.begin(); //установить на второй елемент списка
			int widthSimvol = 0;
            int * mas = new int[caretIndex + 1];  //указатель на масив который будет содержать рзмеры символов
			GetWidthSimvol( textU, mas, caretIndex + 1 );
			for(int i = 0; i <= caretIndex; ++i)
			{
				widthSimvol = mas[i];
				textList.insert(caretIterator, widthSimvol);//вставить символ на место каретки
				caretOffsetX += widthSimvol;
			}
			delete mas;
			caretIterator--;
			int w, h;
			TTF_SizeUNICODE(font, textU, &w, &h);
		}
#ifdef _DEBUG
		else
		{
			cout << "Внимание! Вызов SetText() в Text.cpp не привел к инициализации строки textW = nullptr\n" << endl;
		}
#endif
	}
}

//метод public
void CText::SetText( wchar_t* text )
{
	int n = wcslen(text);
	textW = new wchar_t[n + 1];
	wcscpy_s(textW, n + 1, text);
	Uint16* tText = NormalText(text);
	SetText( tText );
}

void CText::SetFontParam( char* font, int size, SDL_Color* color )
{
	if(font != nullptr && FileExists(font))
	{
		if(fileFont != nullptr) delete[]fileFont;
		fileFont = nullptr;

		int n = static_cast<int>(strlen(font));
		fileFont = new char[n + 1];
		strcpy_s(fileFont, n + 1, font);
	}
#ifdef _DEBUG
	else
		printf("Внимание в CText::SetFontParam! Отсутствует шрифт либо передан NULL %s\n", font);
#endif

	ptsize = size <= 0 ? 26 : size;

	if(color != nullptr)
	{
		fontColor.r = NormalColor(color->r);
		fontColor.g = NormalColor(color->g);
		fontColor.b = NormalColor(color->b);
		fontColor.a = NormalColor(color->a);
	}

	SetFont();
}

void CText::SetPtsize( int size )
{
	ptsize = size;
	SetFont();
}

void CText::SetFileFont(const char* font )
{
	if(font != nullptr && FileExists(font))
	{
		if(fileFont != nullptr) delete[]fileFont;
		fileFont = nullptr;

		int n = static_cast<int>(strlen(font));
		fileFont = new char[n + 1];
		strcpy_s(fileFont, n + 1, font);
		SetFont();
	}
#ifdef _DEBUG
	else
		printf("Ошибка в CText::SetFontParam! Отсутствует шрифт %s\n", font);
#endif
}

void CText::SetFontColor( SDL_Color color )
{
	fontColor.r = NormalColor(color.r);
	fontColor.g = NormalColor(color.g);
	fontColor.b = NormalColor(color.b);
	fontColor.a = NormalColor(color.a);

	SetInfo();
}

void CText::SetFontColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
	SDL_Color color = {r, g, b, a};
	SetFontColor(color);
}

void CText::SetFontColor( int r, int g, int b, int a )
{
	SetFontColor( static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a) );
}

Uint8 CText::NormalColor( Uint8 t )
{
	Uint8 v;
	v = t < 0 ? 0 : t;
	v = v > 255 ? 255 : v;
	return v;
}

SDL_Color CText::NormalColor( SDL_Color t )
{
	SDL_Color ret;
	ret.r = NormalColor(t.r);
	ret.g = NormalColor(t.g);
	ret.b = NormalColor(t.b);
	ret.a = NormalColor(t.a);
	return ret;
}

void CText::SetRectSrc( int x, int y, int w, int h )
{
	rectSrc.x = x;
	rectSrc.y = y;
	rectSrc.w = w;
	rectSrc.h = h;
}

void CText::SetRectSrc( SDL_Rect r )
{
	SetRectSrc( r.x, r.y, r.w, r.h );
}

//прямоугольник на рендере в который будет выведено прямоугольник SetRectSrc
void CText::SetRectDst( int x, int y, int w, int h )
{
	rectDst.x = x;
	rectDst.y = y;
	rectDst.w = w;
	rectDst.h = h;

	caret->SetCaretX(x + caretOffsetX);
	caret->SetCaretY(y);
	if(h < caret->GetCaretH())
		caret->SetCaretH(h);
}

void CText::SetRectDst( SDL_Rect r )
{
	SetRectDst( r.x, r.y, r.w, r.h );
}

void CText::SetRectDst( SDL_Point p )
{
	rectDst.x = p.x;
	rectDst.y = p.y;
}

//************************* ОТРИСОВКА ТЕКСТА И КАРЕТКИ ***************
void CText::DrawText()
{
	if(GetFullFlag())
	{
		//получить текущий цвет
		SDL_Color colorOld;
		SDL_GetRenderDrawColor(renderer, &colorOld.r, &colorOld.g, &colorOld.b, &colorOld.a);

		//Установить цвет текста
		SDL_SetRenderDrawColor( renderer, fontColor.r, fontColor.g, fontColor.b, fontColor.a );

		//Отобразить текст на рендере
		SDL_RenderCopy(renderer, texture, &rectSrc, &rectDst);

		//вернуть цвет по умолчанию
		SDL_SetRenderDrawColor( renderer, colorOld.r, colorOld.g, colorOld.b, colorOld.a );

		if(GetFCaretka())//обрабатывем каретку если она включена для данного текста
		{
			//спрятать или показать каретку по размерам ректа текста
			caret->SetCaretX(rectDst.x + caretOffsetX);
			if(caretOffsetX >= 0 && caretOffsetX <= rectDst.w )
				caret->DrawCaret();
		}
	}
}
//************************* ОБРАБОТЧИК СОБЫТИЙ ТЕКСТА ***************
void CText::HendlerEvent( SDL_Event* ev, int X, int Y )
{
	switch(ev->type)
	{
	case SDL_KEYDOWN:
		KeyDown(ev->key.keysym.sym);
		break;

	case SDL_KEYUP:
		KeyUp(ev->key.keysym.sym);
		break;
	default:
		break;
	}
}

//TTF_STYLE_NORMAL
//TTF_STYLE_BOLD
//TTF_STYLE_ITALIC
//TTF_STYLE_UNDERLINE
//TTF_STYLE_STRIKETHROUGH
void CText::SetStyleFont( int style )//Установка стиля шрифта
{
	if(GetFlag(MYF_FONT_INIT))
	{
		TTF_SetFontStyle(font, style );
		SetInfo();
	}
}


//********************* ФЛАГИ *****************************
//возвращает состояние флага по указанному индексу
int CText::GetBit( int i )
{
	int val = FLAG_INIT;
	return (!!(val&1<<i));
}

//Принимает маску флага и возвращает его статус 0 или 1. При передаче 0 вернет -1
//Работает только с единичными флагами, где только одна 1 а все остальные 0
int CText::GetFlag( int fl )
{
	if(fl == 0)//Защищаемся от случая, когда передан 0 чтобы не попасть в вечный цикл
		return -1;

	int n = 0;//ищем номер бита который нужно проверять
	while((fl & 1) == 0) {
		++n; 
		fl >>= 1;	
	}

	return GetBit(n); 
}

//Проверяет флаги в переменной содержащей все последовательно идущие флаги.
int CText::GetFullFlag()
{
	int flDest = FLAG_INIT;

	for(int i = 0; i < countFlag; ++i)
		if((flDest & 1) == 0)
			return 0;
		else
			flDest >>= 1;
	return 1;
}

//Принимает ссылку на переменную которая содержит все флаги и флаг который нужно установить
//1 - установить, 0 - сбросить
void CText::SetFlag( int fl, int p /*= 1*/ )
{
	if(p) FLAG_INIT |= fl;
	else FLAG_INIT &= ~fl;
}

//**************** КАРЕТКА **********************

// *************** LEFT ***************
//перемещает каретку на step сиволов в лево, если перемещать уже некуда вернет false
bool CText::C_Left( int step /*= 1*/ )
{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод CaretMuveLeft() в Text.cpp когда textW = nullptr\n" << endl;
#endif
		return false;
	}

	if(caretIndex < 0)//каретка уже в крайнем левом положении
		return false;

	step = step > caretIndex + 1 ? caretIndex + 1 : step;
	for(int i = 0; i < step; ++i)
	{
		caretOffsetX -= *caretIterator;
		--caretIterator;
	}

	caretIndex -= step;

	if(caretIndex < 0)
		return false;
	else
		return true;
}


// *************** RIGHT ***************
//перемещает каретку на step сиволов в право, если перемещать уже некуда вернет false
bool CText::C_Right( int step /*= 1*/ )
{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод CaretMuveRight() в Text.cpp когда textW = nullptr\n" << endl;
#endif
		return false;
	}

	int n = wcslen(textW);
	if(caretIndex == n - 1)//если каретка на последнем символе
		return false;

	//проветрить чтобы шаг не выходил за пределы длины строки
	step = caretIndex + 1 + step > n ? n - (caretIndex + 1) : step;
	for(int i = 0; i < step; ++i)
	{
        ++caretIterator;                //сдвинуть итератор вперед
        caretOffsetX += *caretIterator; //увеличить офсет на размер символа под итератором
	}

	caretIndex += step;

	if(caretIndex == n - 1)
        return false; //достигнут край строки
	else
        return true;  //еще остались символы в строке
}


// *************** AND ***************
//перемещает каретку на конец строки
void CText::C_End()

{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод CaretMuveEnd() в Text.cpp когда textW = nullptr\n" << endl;
#endif
	}
	else
	{		
		int n = wcslen(textW);
        if(caretIndex == n - 1)     //если каретка уже в конце строки

		for(;caretIndex < n - 1; ++caretIndex)
		{
            ++caretIterator;        //сместить итератор на символ в право
			caretOffsetX += *caretIterator;//увеличить офсет на размер символа под итератором
		}
	}
}


// *************** HOME ***************
//перемещает каретку на начало строки
void CText::C_Home()
{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод CaretMuveHome() в Text.cpp когда textW = nullptr\n" << endl;
#endif
	}
	else
	{
		if(caretIndex > 0)//если каретка уже не в начале строки
		{
			for(;caretIndex != -1; --caretIndex)
			{
				caretOffsetX -= *caretIterator;//уменьшить офсет на размер символа под итератором
				--caretIterator;//сместить итератор на символ в лево
			}
		}
	}
}


// *************** ADD ***************
//добавить сивол или строку в позицию каретки и сместить каретку на символ
bool CText::C_Add( wchar_t* cr )
{
	if(GetFlag(MYF_FONT_INIT))
	{
		int nNew = wcslen(cr);
		int n = 0;
		if(textW != nullptr)//если есть строка
			n = wcslen(textW);
		else
		{
			textList.clear();
			textList.push_back(0);//начало строки
			textList.push_back(0);//конец строки
			caretIterator = ++textList.begin();//установить на второй елемент списка
		}

		wchar_t* newStr = new wchar_t[nNew + n + 1];//Новая строка

		if(n > 0)
			for(int i = 0; i <= caretIndex; ++i)//Записать строку до каретки включительно
				newStr[i] = textW[i];

		for(int i = caretIndex + 1, Ni = 0; Ni < nNew; ++i, ++Ni)//Записать вставляемую строку
			newStr[i] = cr[Ni];

		if(n > 0)
			for(int i = caretIndex + 1, Ni = caretIndex + 1 + nNew; i < n; ++i, ++Ni)//Записать строку после каретки
				newStr[Ni] = textW[i];

		newStr[nNew + n] = L'\0';

		caretIndex += nNew;
		if(textW != nullptr) delete textW;
		if(textU != nullptr) delete textU;
		textW = nullptr;
		textU = nullptr;

		textW = newStr;
		textU = NormalText(newStr);

		//Заполнить textList 
		for(int i = 0; i < nNew; ++i)
			textList.insert(caretIterator, 0);//вставить символ на место каретки итератор смещается вперед
		
		//перещитать размеры символов
		list<int>::iterator tempIter = textList.begin();//установить на первый елемент списка;
		int * mas = new int[nNew + n];//указатель на масив который будет содержать рзмеры символов
		GetWidthSimvol( textU, mas, nNew + n );
		for(int i = 0; i < nNew + n; ++i)
			*(++tempIter) = mas[i];
		delete mas;

		//перещитать смещение каретки
		tempIter = textList.begin();//установить на первый елемент списка;
		caretOffsetX = 0;
		for(int i = 0; i <= caretIndex; ++i)
			caretOffsetX += *(++tempIter);

		SetInfo();

		return true;
	}
	else
	{
		return false;
#ifdef _DEBUG
	cout << "Внимание! Вызван метод AddChar() в Text.cpp при неинициализированном font\n" << endl;
#endif
	}
}


// *************** DEL ***************
//удалить amo сиволов перед кареткой, если достигнут конец строки - вернет false
bool CText::C_Del( int amo /*= 1*/ )
{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод DeleteChar() в Text.cpp когда textW = nullptr\n" << endl;
#endif
		return false;
	}

	int n = wcslen(textW);
	if(caretIndex == n - 1)//если каретка за последним символом удалять нечего
		return false;

	//предупредить выход за пределы массива
	amo = caretIndex + 1 + amo > n ? n - (caretIndex - 1) : amo;
	wchar_t* newStr = new wchar_t[n + 1 - amo];//Новая строка с запасом на \0 и вычетом колич удаленных

	for(int i = 0; i <= caretIndex; ++i)//Записать строку до каретки включительно
		newStr[i] = textW[i];

	//i - продолжение индекса строки newStr
	//Ni - индекс символа который идет за удаленным в строке textW
	for(int i = caretIndex + 1, Ni = caretIndex + 1 + amo; Ni < n; ++i, ++Ni)//Записать строку после каретки
		newStr[i] = textW[Ni];

	newStr[n - amo] = L'\0';

	if(textW != nullptr) delete textW;
	if(textU != nullptr) delete textU;
	textW = nullptr;
	textU = nullptr;

	textW = newStr;
	textU = NormalText(newStr);

	list<int>::iterator tempIter = caretIterator;
	for(int i = 0; i < amo; ++i)
	{
		tempIter++;
		textList.erase(caretIterator);//удалить символ под итератором
		caretIterator = tempIter;
	}

	//перещитать размеры символов
	int * mas = new int[n - amo];//указатель на масив который будет содержать рзмеры символов
	GetWidthSimvol( textU, mas, n - amo );
	tempIter = textList.begin();//установить на первый елемент списка
	for(int i = 0; i < n - amo; ++i)
		*(++tempIter) = mas[i];
	delete mas;

	SetInfo();

	if(caretIndex == n - amo - 1)//если достигнут конец строки
		return false;
	else//еще есть символы перед кареткой
		return true;

}


// *************** BACKSPACE ***************
//удалить amo сиволов за кареткой, если достигнуто начало строки - вернет false
bool CText::C_Back( int amo /*= 1*/ )
{
	if(textW == nullptr)
	{
#ifdef _DEBUG
		cout << "Внимание! Вызван метод BackspaceChar() в Text.cpp когда textW = nullptr\n" << endl;
#endif
		return false;
	}

	if(caretIndex < 0)//каретка в начале строки
		return false;

	int n = wcslen(textW);
	//предупредить выход за пределы массива
	amo = caretIndex + 1 < amo ? caretIndex + 1 : amo;
	wchar_t* newStr = new wchar_t[n - amo + 1];//Новая строка

	for(int i = 0; i <= caretIndex - amo; ++i)//Записать строку до нового положения каретки включительно
		newStr[i] = textW[i];
	//Записать строку после текущего положения каретки
	for(int i = caretIndex + 1, Ni = caretIndex - amo + 1; i < n; ++i, ++Ni)
		newStr[Ni] = textW[i];

	newStr[n - amo] = L'\0';

	caretIndex -= amo;
	if(textW != nullptr) delete textW;
	if(textU != nullptr) delete textU;
	textW = nullptr;
	textU = nullptr;

	textW = newStr;
	textU = NormalText(newStr);

	list<int>::iterator tempIter = caretIterator;
	for(int i = 0; i < amo; ++i)
	{
		--tempIter;
		caretOffsetX -= *caretIterator;//уменьшить офсет на значение под итератором
		textList.erase(caretIterator);//удалить символ под итератором
		caretIterator = tempIter;//уменьшить итератор
	}

	//перещитать размеры символов
	int * mas = new int[n - amo];//указатель на масив который будет содержать рзмеры символов
	GetWidthSimvol( textU, mas, n - amo );
	tempIter = textList.begin();//установить на первый елемент списка
	for(int i = 0; i < n - amo; ++i)
		*(++tempIter) = mas[i];
	delete mas;

	SetInfo();

	if(caretIndex < 0)//если достигнут конец строки
		return false;
	else//еще есть символы перед кареткой
		return true;
}


void CText::GetWidthSimvol( Uint16* text, int mas[], int len )
{
	if(GetFlag(MYF_FONT_INIT))
	{
		int w = 0;
		int h = 0;
		int dlina = 0;//общая длина строки
		Uint16 * bufer = new Uint16[len + 1];
		for(int i = 0; i < len; ++i)
		{
			bufer[i] = text[i];
			bufer[i + 1] = '\0';
			TTF_SizeUNICODE(font, bufer, &w, &h);
			mas[i] = w - dlina;
			dlina = w;
		}
		delete bufer;
	}
#ifdef _DEBUG
	else
		cout << "Внимание! Вызван метод GetWidthSimvol() в Text.cpp без инициализации font\n" << endl;
#endif
}

void CText::KeyDown(Uint32 key)
{
	wchar_t buf [2];

	switch(key)
	{
	case SDLK_LEFT:
		if(K_DownKey(key, buf))	C_Left();
		break;
	case SDLK_RIGHT:
		if(K_DownKey(key, buf))	C_Right();
		break;
	case SDLK_DELETE:
		if(K_DownKey(key, buf))	C_Del();
		break;
	case SDLK_BACKSPACE:
		if(K_DownKey(key, buf))	C_Back();
		break;
	case SDLK_CAPSLOCK:
		K_DownCaps();
		break;
	case SDLK_LSHIFT:
		K_DownShift();
		break;
	default:
		if(K_DownKey(key, buf))	C_Add(buf);
		break;
	}
}

void CText::KeyUp(Uint32 key)
{
	switch(key)
	{
	case SDLK_CAPSLOCK:
		K_UpCaps();
		break;
	case SDLK_LSHIFT:
		K_UpShift();
		break;
	default:
		K_UpKey(key);
		break;
	}
}

int CText::GetW()
{
	if(GetFlag(MYF_INFO_INIT))//проверка инфо
		if(0 != wcslen(textW))
			return info->w;
	return 0;
}

int CText::GetH()
{
	if(GetFlag(MYF_INFO_INIT))//проверка инфо
		return info->h;
	else
		return 0;
}

void CText::TextSetFocus()
{
	if(GetFCaretka())//обрабатывем каретку если она включена для данного текста
	{
		caret->SetActivCaret();
	}
}

void CText::TextLostFocus()
{
	if(GetFCaretka())//обрабатывем каретку если она включена для данного текста
	{
		caret->SetActivCaret(false);
	}
}
