#include "StdAfx.h"

/*Конструктор для картинок */
CImage4Back::CImage4Back( 
		CInit& ini, 
		char* pImage, 
		char* pImageHover, 
		char* pImagePress, 
		char* pImageHoverPress 
	)
	: CGraphics(ini)
{
	isPress = false;
	isHover = false;

	image = nullptr;
    imageHover = nullptr;
    imagePress = nullptr;
    imageHoverPress = nullptr;

    imagePach = nullptr;
    imageHoverPach = nullptr;
    imagePressPach = nullptr;
    imageHoverPressPach = nullptr;

	widthImage = 0;
	heightImage = 0;

	SetImage(pImage, pImageHover, pImagePress, pImageHoverPress);
}


CImage4Back::~CImage4Back(void)
{
	if(image != nullptr)	SDL_DestroyTexture(image); image = nullptr;
	if(imagePress != nullptr)	SDL_DestroyTexture(imagePress); imagePress = nullptr;
	if(imageHover != nullptr)	SDL_DestroyTexture(imageHover); imageHover = nullptr;
	if(imageHoverPress != nullptr)	SDL_DestroyTexture(imageHoverPress); imageHoverPress = nullptr;

	if(imagePach != nullptr) delete [] imagePach; imagePach = nullptr;
	if(imagePressPach != nullptr) delete [] imagePressPach; imagePressPach = nullptr;
	if(imageHoverPach != nullptr) delete [] imageHoverPach; imageHoverPach = nullptr;
	if(imageHoverPressPach != nullptr) delete [] imageHoverPressPach; imageHoverPressPach = nullptr;
}

bool CImage4Back::SetImagePr( char* img, char* (& destPach), SDL_Texture* (& destTexture) )
{
	if(img != nullptr && FileExists(img))
	{
		//скопировать путь к файлу картинки
		int n = strlen(img);
		if(destPach != nullptr)
			delete [] destPach;
		destPach = new char[n + 1];
		strcpy_s(destPach, n + 1, img);

		if(destTexture != nullptr)
			SDL_DestroyTexture(destTexture);
		destTexture = nullptr;

		destTexture = IMG_LoadTexture(GetRenderer(), img);
		return true;
	}
	return false;
}

/*Принимает путь к картинке */ 
bool CImage4Back::SetImage( 
	char* pImage,
	char* pImageHover,
	char* pImagePress, 
	char* pImageHoverPress )
{
	if(SetImagePr(pImage, imagePach, image))
	{
		Uint32 format;
		int access, w, h;
		if(0 == SDL_QueryTexture(image, &format, &access, &w, &h))
		{
			widthImage = w;
			heightImage = h;
			SetWH(w, h);//Установить рект екземпляра
			SetRectSrc(0, 0, w, h);//Установить рект екземпляра

			SetImagePr(pImagePress, imagePressPach, imagePress);
			SetImagePr(pImageHover, imageHoverPach, imageHover);
			SetImagePr(pImageHoverPress, imageHoverPressPach, imageHoverPress);

			return true;
		}
#ifdef _DEBUG
		else
			printf("Ошибка в методе CImage4Back::SetImage! Функция SDL_QueryTexture вернула ошибку \n" );
#endif
	}
#ifdef _DEBUG
	else
		printf("Ошибка в методе CImage4Back::SetImage! Не получилось установить главную картинку \n");
#endif
	return false;
}

SDL_Texture* CImage4Back::GetImage() const
{
	//если кнопка включена и под мышкой
	if(GetIsPress() && GetIsHover())
		if(imageHoverPress != nullptr) return imageHoverPress;
		else return nullptr;

	//если кнопка под мышкой
	if(GetIsHover())
		if(imageHover != nullptr) return imageHover;
		else return nullptr;

	//если кнопка нажата
	if(GetIsPress())
		if(imagePress != nullptr) return imagePress;
		else return nullptr;

	//просто кнопка
	if(image != nullptr)
		return image;

	return nullptr;
}
