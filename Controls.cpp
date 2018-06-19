#include "StdAfx.h"

//********** ИНИЦИАЛИЗАЦИЯ СТАТИЧЕСКИХ ПОЛЕЙ *****
typedef vector<CControls*>::size_type iCon;
vector<CControls*> CControls::ListControl;
CControls* CControls::сontrolInFocus = nullptr;
int CControls::MouseX = 0;
int CControls::MouseY = 0;
CInit* CControls::init = nullptr;
// ********* End *********

//************ КОНСТРУКТОР ПО УМОЛЧАНИЮ (ПУСТОЙ) *****************
CControls::CControls( SDL_Rect* pRectControl /*= nullptr*/, SDL_Color* pPerimeter /*= nullptr*/, SDL_Color* pFill /*= nullptr*/ )
{
#ifdef DEBUG
	printf("Вызван конструктор по умолчанию класса CControls\n");
#endif

	colorPerimeter = nullptr;
	colorFill = nullptr;

	image = nullptr;
    imagePress = nullptr;
    imageHover = nullptr;
    imageHoverPress = nullptr;

    imagePach = nullptr;
    imagePressPach = nullptr;
    imageHoverPach = nullptr;
    imageHoverPressPach = nullptr;

	widthImage = 0;
	heightImage = 0;

	//Обработка прямоугольника контрола
	if(pRectControl == nullptr)
	{
		rectControl.x = 0;
		rectControl.y = 0;
		rectControl.w = 20;
		rectControl.h = 10;
	}
	else
	{
		rectControl.x = pRectControl->x;
		rectControl.y = pRectControl->y;
		rectControl.w = pRectControl->w;
		rectControl.h = pRectControl->h;
	}

	SetCenterRect();

	//Обработка ссылки на цвет периметра контрола
	if(pPerimeter != nullptr)
		colorPerimeter = new SDL_Color(*pPerimeter);

	//Обработка ссылки на цвет заливки контрола
	if(pFill != nullptr)
		colorFill = new SDL_Color(*pFill);

	deltaX = 0;
	deltaY = 0;

	ListControl.push_back(this);
}


CControls::CControls( 
	char* pImage,	
	char* pImagePress/* = nullptr*/,
	char* pImageHover/* = nullptr*/, 
	char* pImageHoverPress/* = nullptr*/	)
{
	colorPerimeter = nullptr;
	colorFill = nullptr;

	image = nullptr;
    imagePress = nullptr;
    imageHover = nullptr;
    imageHoverPress = nullptr;

    imagePach = nullptr;
    imagePressPach = nullptr;
    imageHoverPach = nullptr;
    imageHoverPressPach = nullptr;

	widthImage = 0;
	heightImage = 0;
	SetImage(pImage, pImagePress, pImageHover, pImageHoverPress);
}


//************ КОНСТРУКТОР КОПИРОВАНИЯ *****************
CControls::CControls( const CControls& Cc ) : CFlag(Cc)
{
#ifdef DEBUG
	printf("Вызван конструктор копирования класса CControls\n");
#endif

	rectControl = Cc.GetRectControl();	// Ограничивающий прямоугольник контрола
    xCenter = Cc.GetXCenter();			// Округленная позиция центра прямоугольника по Х
    yCenter = Cc.GetYCenter();			// Округленная позиция центра прямоугольника по Y

	//Периметр, заливка, картинка контрола
	if(Cc.GetColorPerimeter() == nullptr) colorPerimeter = nullptr;
	else colorPerimeter = new SDL_Color(*(Cc.GetColorPerimeter()));

	if(Cc.GetColorFill() == nullptr) colorFill = nullptr;
	else colorFill = new SDL_Color(*(Cc.GetColorFill()));

	image = nullptr;
    imagePress = nullptr;
    imageHover = nullptr;
    imageHoverPress = nullptr;

    imagePach = nullptr;
    imagePressPach = nullptr;
    imageHoverPach = nullptr;
    imageHoverPressPach = nullptr;

	//создать текстуру из картинки
	SetImage(Cc.GetImagePach(), Cc.GetImagePressPach(), Cc.GetImageHoverPach(), Cc.GetImageHoverPressPach());
}


//************ ПЕРЕГРУЗКА ОПЕРАТОРА = *****************
CControls& CControls::operator=( const CControls& Cc )
{
	CFlag::operator=(Cc);
#ifdef DEBUG
	printf("Перегрузка оператора = класса CControls\n");
#endif

	if(this == &Cc)
		return *this;

	rectControl = Cc.GetRectControl();	// Ограничивающий прямоугольник контрола
    xCenter = Cc.GetXCenter();			// Округленная позиция центра прямоугольника по Х
    yCenter = Cc.GetYCenter();			// Округленная позиция центра прямоугольника по Y

	//Периметр, заливка, картинка контрола
	if(Cc.GetColorPerimeter() == nullptr) colorPerimeter = nullptr;
	else colorPerimeter = new SDL_Color(*(Cc.GetColorPerimeter()));

	if(Cc.GetColorFill() == nullptr) colorFill = nullptr;
	else colorFill = new SDL_Color(*(Cc.GetColorFill()));

	image = nullptr;
    imagePress = nullptr;
    imageHover = nullptr;
    imageHoverPress = nullptr;

    imagePach = nullptr;
    imagePressPach = nullptr;
    imageHoverPach = nullptr;
    imageHoverPressPach = nullptr;

	//создать текстуру из картинки
	SetImage(Cc.GetImagePach(), Cc.GetImagePressPach(), Cc.GetImageHoverPach(), Cc.GetImageHoverPressPach());

	return *this;
}


//************ ДЕСТРУКТОР *****************
CControls::~CControls()
{
#ifdef DEBUG
	printf("Деструктор класса CControls\n");
#endif

	if(colorPerimeter != nullptr)	delete colorPerimeter;
	colorPerimeter = nullptr;

	if(colorFill != nullptr) delete colorFill;
	colorFill = nullptr;

	if(image != nullptr)	SDL_DestroyTexture(image); image = nullptr;
	if(imagePress != nullptr)	SDL_DestroyTexture(imagePress); imagePress = nullptr;
	if(imageHover != nullptr)	SDL_DestroyTexture(imageHover); imageHover = nullptr;
	if(imageHoverPress != nullptr)	SDL_DestroyTexture(imageHoverPress); imageHoverPress = nullptr;

	if(imagePach != nullptr) delete [] imagePach; imagePach = nullptr;
	if(imagePressPach != nullptr) delete [] imagePressPach; imagePressPach = nullptr;
	if(imageHoverPach != nullptr) delete [] imageHoverPach; imageHoverPach = nullptr;
	if(imageHoverPressPach != nullptr) delete [] imageHoverPressPach; imageHoverPressPach = nullptr;

}


void CControls::SetColorPerimeter( SDL_Color* color )
{
	if(color == nullptr) colorPerimeter = nullptr;
	else
	{
		colorPerimeter->r = color->r < 0 ? 0 : color->r;
		colorPerimeter->r = color->r > 255 ? 255 : color->r;

		colorPerimeter->g = color->g < 0 ? 0 : color->g;
		colorPerimeter->g = color->g > 255 ? 255 : color->g;

		colorPerimeter->b = color->b < 0 ? 0 : color->b;
		colorPerimeter->b = color->b > 255 ? 255 : color->b;

		colorPerimeter->a = color->a < 0 ? 0 : color->a;
		colorPerimeter->a = color->a > 255 ? 255 : color->a;
	}

}

void CControls::SetColorFill( SDL_Color* color )
{
	if(color == nullptr) colorFill = nullptr;
	else
	{
		colorFill->r = color->r < 0 ? 0 : color->r;
		colorFill->r = color->r > 255 ? 255 : color->r;

		colorFill->g = color->g < 0 ? 0 : color->g;
		colorFill->g = color->g > 255 ? 255 : color->g;

		colorFill->b = color->b < 0 ? 0 : color->b;
		colorFill->b = color->b > 255 ? 255 : color->b;

		colorFill->a = color->a < 0 ? 0 : color->a;
		colorFill->a = color->a > 255 ? 255 : color->a;
	}

}

//принимает путь к картинке, ссылку на поле в которое записать путь картинки и ссылку на текстуру в которую создать новую текстуру из указанной картинки
bool CControls::SetImagePr( char* img, char* (& destPach), SDL_Texture* (& destTexture) )
{
	if(img != nullptr)
	{
		if(FileExists(img))
		{
			if(init->GetRenderer() != nullptr)
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

				destTexture = IMG_LoadTexture(init->GetRenderer(), img);
				return true;
			}
	#ifdef DEBUG
			else
				printf("Ошибка! Вызыван метод CControls::SetImagePr когда рендерер не инициализирован\n");
	#endif
		}
	#ifdef DEBUG
		else
			printf("Ошибка в методе CControls::SetImagePr! Отсутствует файл картинки %s\n", img);
	#endif
	}
	return false;
}

bool CControls::SetImage( /*Принимает путь к картинке */ 
	char* pImage, 
	char* pImagePress /*= nullptr*/, 
	char* pImageHover /*= nullptr*/, 
	char* pImageHoverPress /*= nullptr */ 
	)
{
	if(SetImagePr(pImage, imagePach, image))
	{
		flipRect.x = 0, flipRect.y = 0, flipRect.w = 0, flipRect.h = 0;

		Uint32 format;
		int access, w, h;
		if(0 == SDL_QueryTexture(image, &format, &access, &w, &h))
		{
			widthImage = w;
			heightImage = h;
			flipRect.w = w, flipRect.h = h;
			rectControl.w = w, rectControl.h = h;
			SetCenterRect();

			SetImagePr(pImagePress, imagePressPach, imagePress);
			SetImagePr(pImageHover, imageHoverPach, imageHover);
			SetImagePr(pImageHoverPress, imageHoverPressPach, imageHoverPress);

			return true;
		}
#ifdef DEBUG
		else
			printf("Ошибка в методе CControls::SetImage! Функуия SDL_QueryTexture вернула ошибку \n" );
#endif
	}
#ifdef DEBUG
	else
			printf("Ошибка в методе CControls::SetImage! Не получилось установить главную картинку \n");
#endif
	return false;
}


int CControls::GetIndex()
{
	for(iCon i = 0, n = 0; i < ListControl.size(); i++, n++)
		if(ListControl[i] == this) return n;
	return -1;
}

//***********  статисческий метод вывода ИЗОБРАЖЕНИЯ
void CControls::DrawControls()
{
	vector<CControls*>::iterator it;
	for(it=ListControl.begin(); it!=ListControl.end(); it++)
	{
		(*it)->DrawChaild();
	}
}

//***********  статисческий метод обработки СОБИТИЙ
void CControls::EventControls()
{
	SDL_GetMouseState(&MouseX, &MouseY);//получить положение мышки

	//события для всех контролов
	CControls* contr = nullptr;
	switch(init->GetMainEvent()->type)
	{	
	case SDL_MOUSEMOTION:
		contr = GetControlUnderMouse();
		MouseHover(contr);
		break;
	case SDL_MOUSEBUTTONUP:
		MouseUp();
		break;
	case SDL_MOUSEBUTTONDOWN:
		contr = GetControlUnderMouse();
		if(contr != nullptr)//если событие над кнопкой, обрабатываем нажатие
			contr->SetFocus();
		else
			 ResetFocus();//если нажатие на пустом месте, сбрасываем фокус
		break;
	}

	if(сontrolInFocus != nullptr)
		сontrolInFocus->HendlerEventChaild(init->GetMainEvent());
}


//************* Получить верхний прямоугольник под мышкой который получит фокус
CControls* CControls::GetControlUnderMouse()
{
	SDL_Point pointMouse = {MouseX, MouseY};
	
	vector<CControls*>::reverse_iterator it;
	for(it=ListControl.rbegin(); it!=ListControl.rend(); it++)
		if(PointInRect(&pointMouse, *it))
			return (*it);

	return nullptr;
}


bool CControls::PointInRect( SDL_Point* p, CControls* Cc)
{
	SDL_Rect* r = &Cc->rectControl;
	if(p->x >= r->x && p->x <= (r->x + r->w) && p->y >= r->y && p->y <= (r->y + r->h))
		return true;
	else
		return false;
}

void CControls::SetDeltaXY()
{
	deltaX = MouseX - rectControl.x;
	deltaY = MouseY - rectControl.y;
}

void CControls::ChangePositionControl( int X /*= MouseX*/, int Y /*= MouseY*/, bool fDelta /*= true*/ )
{
	int dX = 0;
	int dY = 0;
	if(fDelta)
	{
		dX = deltaX;
		dY = deltaY;
	}
	rectControl.x = X - dX;
	rectControl.y = Y - dY;
	NormalizeRect(&rectControl);
	SetCenterRect();
}

//Поставить в начало обработки
void CControls::ChangeIndex()
{
	int t = GetIndex();
	if(t != -1)
		ListControl.erase(ListControl.begin() + t);
	ListControl.push_back(this);
}

//проверяет чтобы координаты переданого первым параметром прямоугольника не выходили
//за пределы прямоугольника из второго параметра
//Вторым параметром по умолчанию будет nulptr что обозначает сравнение со всем окном приложения
void CControls::NormalizeRect( SDL_Rect* rC, SDL_Rect* rP /*= nullptr*/ )
{
	int X = 0;
	int Y = 0;
	int W = init->GetScreenWidth();
	int H = init->GetScrinHeight();

	if(rP != nullptr)//если передан ограничивающий прямоугольник
	{
		int X = 0;
		int Y = 0;
		int W = init->GetScreenWidth();
		int H = init->GetScrinHeight();
	}

    rC->x = rC->x < X ? X : rC->x;  //ограничить выход за пределы окна по X с лева
    if((rC->x + rC->w) > W)         //ограничить выход за пределы окна по X с права
		rC->x = W - rC->w - 1;

    rC->y = rC->y < 0 ? 0 : rC->y;  //ограничить выход за пределы окна по Y в верху
    if((rC->y + rC->h) > H)         //ограничить выход за пределы окна по Y в низу
		rC->y = H - rC->h - 1;
}

void CControls::SetCenterRect()
{
	xCenter = static_cast<int>(rectControl.x + floor(rectControl.w / 2.0 + 0.5));
	yCenter = static_cast<int>(rectControl.y + floor(rectControl.h / 2.0 + 0.5));
}

void CControls::InitControls( CInit* ini )
{
	if(init == nullptr)
		init = ini;
}

void CControls::SetRenderDrawColor( SDL_Color* color )
{
	SDL_Renderer* renderer = GetRenderer();
	if(renderer != nullptr)
		SDL_SetRenderDrawColor( renderer, color->r, color->g, color->b, color->a );
}

SDL_Renderer* CControls::GetRenderer()
{
	return init->GetRenderer();
}

SDL_Color CControls::GetRenderDrawColor()
{
	SDL_Renderer* renderer = GetRenderer();
	SDL_Color colorOld;
	colorOld.r = 100, colorOld.g = 100, colorOld.b = 100, colorOld.a = 100;
	if(renderer != nullptr)	
		SDL_GetRenderDrawColor(renderer, &colorOld.r, &colorOld.g, &colorOld.b, &colorOld.a);
	else
	{
#ifdef DEBUG
		printf("Ошибка получения текущего цвета ренда, рендер не инициализирован  CControls\n");
#endif
	}
	return colorOld;
}

CControls* CControls::GetControlInFocus()
{
	return сontrolInFocus;
}

//Устанавливается при обработке нажатия мыши SDL_MOUSEBUTTONDOWN
void CControls::SetFocus()
{
	//запускает обработку если произошло первое нажатие кнопи после ее отжатия
	//повторно запускает только после события отжатия кнопки
	if(GetTempPressUp())
	{
        SetTempPressUp(false);        //устанавливаем что произошло первое нажатие, ждем события отжатия
		//обрабатываем флаги
        SetTempPress(GetIsPress());   //запомнить предидущее положение кнопки
        SetIsPress(true);             //установить что кнопка нажата
	}

	if(сontrolInFocus != nullptr && сontrolInFocus != this)
		сontrolInFocus->LoseFocus();
	сontrolInFocus = this;
	сontrolInFocus->InFocus();
}

void CControls::LoseFocus()
{
	if(сontrolInFocus == this)
	{
		сontrolInFocus->OutFocus();
		сontrolInFocus = nullptr;
	}
}

void CControls::ResetFocus()
{
	if(сontrolInFocus != nullptr)
		сontrolInFocus->LoseFocus();
}

bool CControls::FileExists( const char *fname )
{
	return _access(fname, 0) != -1;
}

void CControls::SetFlipRect( SDL_Rect &r )
{
	if(image != nullptr)
	{
		SetFlipRectX( r.x );
		SetFlipRectY( r.y );
		SetFlipRectW( r.w );
		SetFlipRectH( r.h );
	}
}

void CControls::SetFlipRectX( int x )
{
	if(image != nullptr)
		flipRect.x = x >= 0 && x < widthImage ? x : 0;
}

void CControls::SetFlipRectY( int y )
{
	if(image != nullptr)
		flipRect.y = y >= 0 && y < heightImage ? y : 0;
}

void CControls::SetFlipRectW( int w )
{
	if(image != nullptr)
	{
		flipRect.w = w < 0 ? 0 : w;
		flipRect.w = flipRect.w + w <= widthImage ? w : widthImage - flipRect.w;
	}
}

void CControls::SetFlipRectH( int h )
{
	if(image != nullptr)
	{
		flipRect.h = h < 0 ? 0 : h;
		flipRect.h = flipRect.h + h <= heightImage ? h : heightImage - flipRect.h;
	}
}

SDL_Texture* CControls::GetImage() const
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
