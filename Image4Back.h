/*
Класс будет виртуальным. расшираяет класс CGraphics добавляя 4 фоновые картинки и методы их обработки
Картинки будут соотвтвовать 4 положениям: обычное, нажатое, ховер, ховер-нажатое
*/
#pragma once
#include "StdAfx.h"

class CImage4Back : public CGraphics
{
	bool isHover;	//Над объектом мышка
	bool isPress;	//Кнопка зажата
	//картинка 
    SDL_Texture* image;				//указатель на текстуру картинки ПО УМОЛЧАНИЮ
    SDL_Texture* imageHover;		//указатель на текстуру картинки ПОД МЫШКОЙ
    SDL_Texture* imagePress;		//указатель на текстуру картинки НАЖАТОЙ
    SDL_Texture* imageHoverPress;	//указатель на текстуру картинки ПОД МЫШКОЙ НАЖАТОЙ

    char* imagePach;				//путь к файлу картинки ПО УМОЛЧАНИЮ
    char* imageHoverPach;			//путь к файлу картинки ПОД МЫШКОЙ
    char* imagePressPach;			//путь к файлу картинки НАЖАТОЙ
    char* imageHoverPressPach;		//путь к файлу картинки ПОД МЫШКОЙ НАЖАТОЙ

    int widthImage;   //Ширина картинки
    int heightImage;  //высота картинки

	//принимает путь к картинке, ссылку на поле в которое записать путь картинки и ссылку на текстуру в которую создать новую текстуру из указанной картинки
	bool SetImagePr(char* img, char* (& destPach), SDL_Texture* (& destTexture));


public:
	CImage4Back(//Конструктор для картинок
		CInit& ini,
		char* pImage, 
		char* pImageHover, 
		char* pImagePress,
		char* pImageHoverPress 
		);
	virtual ~CImage4Back(void);

	bool SetImage(//Принимает путь к картинке
		char* pImage,
		char* pImageHover, 
		char* pImagePress,
		char* pImageHoverPress
		);

	//возвращает нужную текстуру для вывода
	SDL_Texture* GetImage()const;

	char* GetImagePach()const{ return imagePach; }
	char* GetImagePressPach()const{ return imagePressPach; }
	char* GetImageHoverPach()const{ return imageHoverPach; }
	char* GetImageHoverPressPach()const{ return imageHoverPressPach; }

	int GetWidthImage()const{ return widthImage; }
	int GetHeightImage()const{ return heightImage; }

	//**** isHover
	void SetIsHover(bool f){ isHover = f; }
	bool GetIsHover() const { return isHover; }

	//**** isPress
	void SetIsPress(bool f){ isPress = f; }
	bool GetIsPress() const { return isPress; }
};

