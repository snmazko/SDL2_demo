#pragma once
#include "stdafx.h"


class CControls : public CFlag
{
private:	
	//Вектор с указателями на все контролы
	static vector<CControls*> ListControl;

	static CInit* init;

	//Контрол который находится в данный момент в фокусе
	static CControls* сontrolInFocus;

	//Текущие координаты мышки
	static int MouseX;
	static int MouseY;

	//смещение от верхней левой точки екземпляра до точки где была нажата мышка
	int deltaX;
	int deltaY;

	// ************ ПОЗИЦИЯ КОНТРОЛА
    SDL_Rect rectControl; // Ограничивающий прямоугольник контрола
    int xCenter;          //Округленная позиция центра прямоугольника по Х
    int yCenter;          //Округленная позиция центра прямоугольника по Y
	//********** End ****

	//******** ПЕРЕИМЕТР, ЗАЛИВКА, КАРТИНКА КОНТРОЛА
	SDL_Color* colorPerimeter;
	SDL_Color* colorFill;

	//картинка 
    SDL_Texture* image;				//указатель на текстуру картинки ПО УМОЛЧАНИЮ
    SDL_Texture* imagePress;		//указатель на текстуру картинки НАЖАТОЙ
    SDL_Texture* imageHover;		//указатель на текстуру картинки ПОД МЫШКОЙ
    SDL_Texture* imageHoverPress;	//указатель на текстуру картинки ПОД МЫШКОЙ НАЖАТОЙ

    char* imagePach;				//путь к файлу картинки ПО УМОЛЧАНИЮ
    char* imagePressPach;			//путь к файлу картинки НАЖАТОЙ
    char* imageHoverPach;			//путь к файлу картинки ПОД МЫШКОЙ
    char* imageHoverPressPach;		//путь к файлу картинки ПОД МЫШКОЙ НАЖАТОЙ

    int widthImage;   //Ширина картинки
    int heightImage;  //высота картинки
	SDL_Rect flipRect;//рект который берется с картинки и выводится на рендер

	//принимает путь к картинке, ссылку на поле в которое записать путь картинки и ссылку на текстуру в которую создать новую текстуру из указанной картинки
	bool SetImagePr(char* img, char* (& destPach), SDL_Texture* (& destTexture));//Принимает путь к картинке
	//********** End ****

public:
	//***** КОНСТРУКТОРЫ МЕТОДЫ ПЕРЕОПРЕДЕЛЕНИЯ
	CControls(//Конструктор для картинок
		char* pImage, 
		char* pImagePress = nullptr,
		char* pImageHover = nullptr, 
		char* pImageHoverPress = nullptr 
	);

	CControls(//Конструктор по умолчанию
		SDL_Rect* pRectControl = nullptr,
		SDL_Color* pPerimeter = nullptr,
		SDL_Color* pFill = nullptr
	);

    CControls(const CControls& Cc);				//конструктор копирования
	CControls& operator=(const CControls& Cc);	//Оператор присваиванивания
    virtual ~CControls();						//Деструктор
	//********** End ****


	//***** СТАТИЧЕСКИЕ МЕТОДЫ ***участвуют в обработке других статических методов
    static void DrawControls();               //Запустить метод DrawChaild для элементов ListControl
    static void EventControls();              //Обработчик событий общий для Контролов
    static CControls* GetControlUnderMouse(); //найти и вернуть ссылку на верхний контрол на котором находится мышка
    static void InitControls(CInit* ini);     //Присваивает ссылку CInit полю init

	//Возвращает true если точка находится в прямоугольнике контрола если не найдено возвращает nullptr
	static bool PointInRect(SDL_Point* p, CControls* Cc);
    static void ResetFocus();                 //сбросить фокус с экземпляра который в фокусе.
	//********** End ****

	
	// ********** МЕТОДЫ КОТОРЫЕ БУДУТ ПЕРЕОПРЕДЕЛЕНЫ НАСЛЕДНИКАМИ ******
    virtual void DrawChaild() = 0;                    //Отобразить екзепляр
    virtual void HendlerEventChaild(SDL_Event*) = 0;  //Обработчик события экземпляра класса
    virtual void InFocus() = 0;                       //екземпляр получил фокус
    virtual void OutFocus() = 0;                      //ееземпляр потерял фокус
	//********** End ****


	//********** ПРОСТО МЕТОДЫ ******
	//ФОКУС
    void SetFocus();                  //Контрол получил фокус
    void LoseFocus();                 //Контрол потерял фокус
    CControls* GetControlInFocus();   //Вернуть ссылку на контрол который в данный моент в фокусе

    void SetCenterRect();             //установка координат центра прямоугольника контрола
    void SetDeltaXY();                //нахождение смещения от положения мышки до верхнего левого угла контрола

    bool AddControl();                //Добавить указатель на экземпляр класса CControls в ListControl

    void ChangeIndex();               //Поставить контрол в начало обработки (в начало вектора ListControl)
	
    int GetIndex();                   //Возвращает индекс контрола либо -1 в ListControl

	//изменить позицию контрола. По умолчанию на текущую позиуию мышки с применением сдвига до лев. верх угла прямоугольника
	void ChangePositionControl(int X = MouseX, int Y = MouseY, bool fDelta = true);

	//проверяет чтобы координаты переданого первым параметром прямоугольника не выходили за пределы прямоугольника из второго параметра
	//Вторым параметром по умолчанию будет nulptr что обозначает сравнение со всем окном приложения
	void NormalizeRect(SDL_Rect* rChaild, SDL_Rect* rParent = nullptr);

	//********** End ****

	
	void SetColorPerimeter(SDL_Color* color);
	SDL_Color* GetColorPerimeter()const { return colorPerimeter; }

	void SetColorFill(SDL_Color* color);
	SDL_Color* GetColorFill()const { return colorFill; }

	
	bool SetImage(//Принимает путь к картинке
		char* pImage,	
		char* pImagePress = nullptr,
		char* pImageHover = nullptr, 
		char* pImageHoverPress = nullptr	);

	//возвращает нужную текстуру для вывода
	SDL_Texture* GetImage()const;

	char* GetImagePach()const{ return imagePach; }
	char* GetImagePressPach()const{ return imagePressPach; }
	char* GetImageHoverPach()const{ return imageHoverPach; }
	char* GetImageHoverPressPach()const{ return imageHoverPressPach; }

	int GetWidthImage()const{ return widthImage; }
	int GetHeightImage()const{ return heightImage; }

	// методы установки возврата ректа флипа
	SDL_Rect GetFlipRect()const{ return flipRect; }
	void SetFlipRect(SDL_Rect &r);
	void SetFlipRectX(int x);
	void SetFlipRectY(int y);
	void SetFlipRectW(int w);
	void SetFlipRectH(int h);

	SDL_Rect GetRectControl() const { return rectControl; }

	int GetXCenter()const { return xCenter; }
	int GetYCenter()const { return yCenter; }
	
	int GetMouseX() { return MouseX; }
	int GetMouseY() { return MouseY; }

	int GetDeltaX() { return deltaX; }
	int GetDeltaY() { return deltaY; }

	void SetRenderDrawColor(SDL_Color* color);
	SDL_Color GetRenderDrawColor();
	SDL_Renderer* GetRenderer();

	bool FileExists(const char *fname);
	enum{
        BOTTON = 0x1,				//0x1 1
        BOTTON_PRESS = BOTTON << 1,	//0x2 10
        HOVER = BOTTON_PRESS << 1	//0x4 100
	};
};
