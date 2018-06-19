#include "stdafx.h"


CCell::CCell(CInit& ini, int w, int h)
	:CGraphics(ini)
{
    SetWH(w,h);                 //общий размер ректа сектора
    SetRectSrc(0,0,w,h);        //прямоугольник ректа который будет отображен на рендере

    imageFonTexture = nullptr;  //указатель на текстуру картинки фона
	imageFonPach = nullptr;
	rectImageFonSrc.x = rectImageFonSrc.y = rectImageFonSrc.w = rectImageFonSrc.h = 0;
}


CCell::~CCell(void)
{
	if(imageFonTexture != nullptr)	SDL_DestroyTexture(imageFonTexture); imageFonTexture = nullptr;

	if(imageFonPach != nullptr) delete [] imageFonPach; imageFonPach = nullptr;
}

//************* VIRTUAL ***************
//Отобразить екзепляр
void CCell::Draw()	//virtual
{
	if(GetVisible())
	{
		SDL_Rect rDest = GetRectSrc();
		SDL_Point p = GetPointDest();
		rDest.x = p.x;
		rDest.y = p.y;

		if(imageFonTexture == nullptr)//если нету текстуры фона - закрашиваем рект цветом фона
			GraphicsDrawFon();
		else
			SDL_RenderCopy(GetRenderer(), imageFonTexture,  &rectImageFonSrc,  &rDest);

		//отобразить рамку елемента
		GraphicsDrawBorder();	

		//отобразить графику елементов сектора
		DrawGraphicsList();
	}
}

//Обработчик событий
void CCell::HendlerEvent()	//virtual
{
	if(GetVisible())//если раздел видим
	{
		//Обработать события для раздела
		CGraphics* contr = nullptr;
		switch(GetEvent()->type)
		{	
		case SDL_MOUSEMOTION:
			contr = GetGraphicsUnderMouse();
			if(contr != nullptr)
                contr->ReceiveHover();  //установить хувер на экземпляр над которым мышка
			else
                DropHover();            //сбросить хувер если он установлен на какам либо экземпляре
			break;
		case SDL_MOUSEBUTTONDOWN:
			contr = GetGraphicsUnderMouse();
            if(contr != nullptr){       //если событие над кнопкой, обрабатываем нажатие
                SetTopInVector(contr);  //Поставить елемент в начало обработки (в начало вектора ListGraphics)
				contr->ReceiveFocus();
				contr->ReceivePress();
			}
			else
                DropFocus();            //если нажатие на пустом месте, сбрасываем фокус
			break;
		case SDL_MOUSEBUTTONUP:
			contr = GetPress();
			if(contr != nullptr)
				contr->LosePress();
			break;
		}

		//отдать события елементу раздела который в фокусе и должен дальше обрабатывать события
		contr = GetFocus();
		if(contr != nullptr && contr != this)
			contr->HendlerEvent();
	}
}

//екземпляр получил фокус
void CCell::ReceiveFocus() //virtual
{
	SetFocus();
}

//екземпляр потерял фокус
void CCell::LoseFocus() //virtual
{
	ResetFocus();
}

//екземпляр получил Hover
void CCell::ReceiveHover() //virtual
{
	SetHover();
}

//екземпляр потерял Hover
void CCell::LoseHover() //virtual
{
	ResetHover();
}

//екземпляр получил Press
void CCell::ReceivePress() //virtual
{
	SetPress();
}

//екземпляр потерял Press
void CCell::LosePress() //virtual
{
	ResetPress();
}

//**** End VIRTUAL ***************


void CCell::DrawGraphicsList()
{
	vector<CGraphics*>::iterator it;
	for(it = ListGraphics.begin(); it != ListGraphics.end(); it++)
		(*it)->Draw();
}

CGraphics* CCell::GetGraphicsUnderMouse()
{
	SDL_Point pointMouse;
	SDL_GetMouseState(&pointMouse.x, &pointMouse.y);//получить положение мышки

	vector<CGraphics*>::reverse_iterator it;
	for(it=ListGraphics.rbegin(); it!=ListGraphics.rend(); it++)
		if(PointInRect(&pointMouse, *it))
			return (*it);

	return nullptr;
}

void CCell::AddGraphics( CGraphics* gr )
{
	ListGraphics.push_back(gr);
}

//Поставить контрол в начало обработки (в начало вектора ListGraphics)
void CCell::SetTopInVector(CGraphics* gr)
{
	if(gr != GetFocus())//если экземпляр не в фокусе, а соответственно не в верху списка ставим его верхним
	{
		int t = GetIndex(gr);
		if(t != -1)
			ListGraphics.erase(ListGraphics.begin() + t);
		ListGraphics.push_back(gr);
	}
}

//Возвращает индекс контрола либо -1 в ListGraphics
int CCell::GetIndex(CGraphics* gr)
{
	for(vector<CGraphics*>::size_type i = 0, n = 0; i < ListGraphics.size(); i++, n++)
		if(ListGraphics[i] == gr) return n;
	return -1;
}

void CCell::SetImage( char* pImage )
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

			//установить размеры прямоугольника на картинке который будет отображаться
			Uint32 format;
			int access, w, h;
			if(0 == SDL_QueryTexture(imageFonTexture, &format, &access, &w, &h))
			{
				float W = static_cast<float>(w);
				float H = static_cast<float>(h);
				float ratioRect = static_cast<float>(GetWidth()) / static_cast<float>(GetHeight());
				float ratioImg = W / H;

				if(ratioRect > ratioImg)
					H = W / ratioRect;
				else if(ratioRect < ratioImg)
					W = H * ratioRect;

				rectImageFonSrc.w = static_cast<int>(floor(W + 0.5));
				rectImageFonSrc.h = static_cast<int>(floor(H + 0.5));
			}
#ifdef _DEBUG
			else
				printf("Ошибка в методе CCell::SetImage! Функция SDL_QueryTexture вернула ошибку \n" );
#endif
		}
#ifdef _DEBUG
		else
			printf("Ошибка в методе CCell::SetImagePr! Отсутствует файл картинки %s\n", pImage);
#endif
	}
#ifdef _DEBUG
	else
		printf("Ошибка в методе CCell::SetImage! Передан пустой указатель на путь к картинке фона \n");
#endif
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CCell::RunMyEvent( string metod )
{

}
//********** End ****
