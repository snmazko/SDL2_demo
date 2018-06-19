#pragma once
#include "StdAfx.h"

class CText: private CTextFlag
{
private:
	//********** ЗАКРЫТЫЕ ПОЛЯ
	//********** ФЛАГИ *********
	int FLAG_INIT;//Переменная содержащая флаги состояний инициализации из перечисления
	int countFlag;//количество флагов не включая последний общий флаг
	int GetBit(int i);
	void SetFlag(int fl, int p = 1);

    TTF_Font* font;				//указатель на загруженный шрифт
	SDL_Color fontColor;		//цвет шрифта
	int ptsize;							//Размер шрифта
    char* fileFont;				//Путь к файлу шрифта#FFFFFF

    wchar_t* textW;				//текст в формате wchar_t
    Uint16* textU;				//текст в формате Uint16

	SDL_Surface* info;			//информационная структура к загруженному тексту
	SDL_Texture* texture;		//указатель на текстуру созданную из шрифта

    SDL_Rect rectSrc;			//прямоугольник в который вписан текст
    SDL_Rect rectDst;			//прямоугольник на отображаемой поверхности в который будет вписан rectSrc

    SDL_Renderer* renderer;     //указатель окна рендеринга
	
	//***** КАРЕТКА ТЕКСТА *****
    CCaret* caret;                      //Указатель на каретку текста
    bool fCaretka;                      //true - текст работает с кареткой, false - в тексте нету каретки
    list<int> textList;                 //Лист будет содержать длинну сивола строки
    list<int>::iterator caretIterator;  //Итератор указывающий на элемент за которым находится каретка
    int caretIndex;                     //Индекс текущего символа из строки
    int caretOffsetX;                   //смещение позиции каретки по Х в пикселах для отображения в рендере

	//*** перемещение каретки
	bool C_Left(int step = 1);
	bool C_Right(int step = 1);
	void C_Home();
	void C_End();

	//*** вставка удаление символов в строку
    bool C_Add(wchar_t* cr);  //добавить сивол в позицию каретки
    bool C_Del(int amo = 1);  //удалить сиволы находящиеся перед кареткой
    bool C_Back(int amo = 1); //удалить сиволы нахдящиеся за кареткой

	//******* ЗАКРЫТЫЕ МЕТОДЫ
	Uint16* NormalText( wchar_t* text );//преобразует текст из wchar_t в Uint16
	void SetTexture();
	void SetInfo();
	void SetFont();
	void SetText(Uint16* text);
	//помещает в mas размеры символов переданных в text, len - длинна строки
	void GetWidthSimvol(Uint16* text, int mas[], int len);

public:
	CText
	(
		SDL_Renderer* renderer,
		wchar_t* text=L"", 
		int size=26, 
		SDL_Color* color = nullptr, 
		char* file = nullptr
	);
    CText(const CText& Cc);				//конструктор копирования
	CText& operator=(const CText& Cc);	//оператор присваиванивания
	~CText(void);

	//********** МЕТОДЫ УСТАНОВКИ ПОЛЕЙ ******
	void SetText(wchar_t* text);
	void SetPtsize(int size);
	void SetFileFont(const char* font);

	void SetFontColor(SDL_Color color);
	void SetFontColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetFontColor(int r, int g, int b, int a);

	void SetFontParam(char* font, int size, SDL_Color* color);

	void SetRectSrc(SDL_Rect r);
	void SetRectSrc(int x, int y, int w, int h);

	void SetRectDst(SDL_Rect r);
	void SetRectDst(int x, int y, int w, int h);
	void SetRectDst(SDL_Point p);
	//********** End ****


	//******** МЕТОДЫ ВОЗВРАТА ПОЛЕЙ ******
	wchar_t* GetTextW() const { return textW; }
	Uint16* GetTextU() const { return textU; }
	int GetPtsize() const { return ptsize; }
	const char* GetFileFont() const { return fileFont; }
	SDL_Color GetFontColor() const { return fontColor; }
	SDL_Rect GetRectSrc() const { return rectSrc; }
	SDL_Rect GetRectDst() const { return rectDst; }
	SDL_Surface* GetInfo() const { return info; }
	SDL_Renderer* GetRenderer() const { return renderer; }
	//********** End ****

	bool FileExists(const char *fname);
	Uint8 NormalColor(Uint8 t);
	SDL_Color NormalColor(SDL_Color t);

	void DrawText();//Выводит текст на текстуру

	//TTF_STYLE_NORMAL
	//TTF_STYLE_BOLD
	//TTF_STYLE_ITALIC
	//TTF_STYLE_UNDERLINE
	//TTF_STYLE_STRIKETHROUGH
	void SetStyleFont(int style);

	void HendlerEvent(SDL_Event* ev, int X, int Y);//Обработчик событий текста
	//******* КАРЕТКА
	void SetFCaretka(bool f){ fCaretka = f; }
	bool GetFCaretka() const { return fCaretka; }

	enum{
        MYF_FONT_INIT = 0x1,                                                            //0x1 1
        MYF_INFO_INIT = MYF_FONT_INIT << 1,                                             //0x2 10
        MYF_RENDERER_INIT = MYF_INFO_INIT << 1,                                         //0x4 100
        MYF_TEXTURE_INIT = MYF_RENDERER_INIT << 1,                                      //0x8 1000
        MYF_FULL_INIT = MYF_TEXTURE_INIT|MYF_FONT_INIT|MYF_INFO_INIT|MYF_RENDERER_INIT  //0x17, 1111
	};
    int GetW(); //Возвращает длинну строки
    int GetH(); //Возвращает высоту строки

	//**** возрат флагов инициализации
	int GetFlag(int fl);
	int GetFullFlag();

	//**** обработка нажатия клавиш
	void KeyDown(Uint32 key);
	void KeyUp(Uint32 key);

	//**** ФОКУС
	void TextSetFocus();//текст получил фокус
	void TextLostFocus();//текст потерял фокус
};

