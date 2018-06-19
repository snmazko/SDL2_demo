#include "StdAfx.h"


CSectionLessBlink::CSectionLessBlink( CInit& ini )
	: CSection(ini), limitRandIterator(200),audError("audio/error.mp3"), audOk("audio/ok.ogg"), delayPlayCurStr(1000)
{
	lable = nullptr;
	fon = nullptr;
	lineBox = nullptr;

    delayShow = 20;     //Время на которое отображается надпись
    delayDraw = 1000;   //Задержка между отображениями надписи
	timeCheck = SDL_GetTicks();

    playStr = true;     //флаг указывает проигрывать или нет слово
    playStrEnd = true;  //флаг указывает что слово закончило проигрывание

	timeCheckPlayCurStr = SDL_GetTicks();//Время последнего звучания слова

	pause = false;

    InitSection();      //Создать все графические елементы данной секции
}


CSectionLessBlink::~CSectionLessBlink(void)
{
	
}


void CSectionLessBlink::RunEvent()
{
//Передать событие на обработку нужному елементу

	CCell* contr = nullptr;
	SDL_Event* ev = GetInit().GetMainEvent();
	switch(ev->type)
	{
	//передать события мышки на обработку тому сектору над которым оно произошло
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		contr = GetCellUnderMouse();
		if(contr != nullptr)
			contr->HendlerEvent();
		break;
	}

	//остальные события передать елементу CGraphics который находится в данный момент в фокусе
	if(CGraphics::GetFocus() != nullptr)
		CGraphics::GetFocus()->HendlerEvent();
}

SectionState CSectionLessBlink::RunDraw()
{
	SectionState state = Play();

	DrawListCell();//Вывести изображение графических елементов разделов секции на рендер

	return state;
}

//Создать все графические елементы данной секции
void CSectionLessBlink::InitSection()
{
	int width = GetInit().GetScreenWidth();
	int heigth = GetInit().GetScrinHeight();
	int tret = width / 3;
	int margin = 10;
	int posNext;
	//фон
	fon = new CCell(GetInit(), width, heigth);
	fon->SetImage("images/fon.jpg");
	fon->SetVisible(true);

	//Чекбоксы
	int wImg, deltaX;
	CCheckBox* cBox1 = new CCheckBox(GetInit(), "images/check/checkOn.png", "images/check/checkOff.png", nullptr, L"Чекбокс 1",52);
	wImg = cBox1->GetWidth();
	deltaX = tret / 2 - wImg / 2;
	cBox1->SetPointDest(deltaX, margin);
	cBox1->Text.SetFontColor(255, 100, 100, 255);
	cBox1->SetVisible(true);
	fon->AddGraphics(cBox1);

	CCheckBox* cBox2 = new CCheckBox(GetInit(), "images/check/checkOn.png", "images/check/checkOff.png", nullptr, L"Чекбокс 2",52);
	deltaX = tret + (tret / 2) - wImg / 2;
	cBox2->SetPointDest(deltaX, margin);
	cBox2->Text.SetFontColor(100, 255, 100, 255);
	cBox2->SetVisible(true);
	fon->AddGraphics(cBox2);

	CCheckBox* cBox3 = new CCheckBox(GetInit(), "images/check/checkOn.png", "images/check/checkOff.png", nullptr, L"Чекбокс 3",52);
	deltaX = tret + tret + (tret / 2) - wImg / 2;
	cBox3->SetPointDest(deltaX, margin);
	cBox3->Text.SetFontColor(100, 100, 255, 255);
	cBox3->SetVisible(true);
	fon->AddGraphics(cBox3);

	posNext = margin * 2 + cBox1->GetHeight(); //добавить свои размеры


	//Радио Чекбоксы
	CRadioBox* rBox1 = new CRadioBox(*fon);
	deltaX = tret / 2 - wImg / 2;
	rBox1->Add("images/check/RadioOn.png", "images/check/RadioOff.png",deltaX, posNext, L"RadioBox 1");
	deltaX = tret + (tret / 2) - wImg / 2;
	rBox1->Add("images/check/RadioOn.png", "images/check/RadioOff.png",deltaX, posNext, L"RadioBox 2");
	deltaX = tret + tret + (tret / 2) - wImg / 2;
	rBox1->Add("images/check/RadioOn.png", "images/check/RadioOff.png",deltaX, posNext, L"RadioBox 3");
	rBox1->SetFontSize(56);

	posNext += margin + cBox1->GetHeight(); //добавить свои размеры


	//Поля ввода
	CLineBox* lineBox1 = new CLineBox(GetInit(), "images/tile/Botton.png");
	wImg = lineBox1->GetWidth();
	deltaX = tret / 2 - wImg / 2;

	lineBox1->SetPointDest(deltaX, posNext);
	lineBox1->Text.SetPtsize(56);
	lineBox1->Text.SetFontColor(255, 100, 100, 255);
	lineBox1->SetHorizontalIndent(10);
	lineBox1->SetText(L"LineBox 1");
	lineBox1->SetVisible(true);
	fon->AddGraphics(lineBox1);

	CLineBox* lineBox2 = new CLineBox(GetInit(), 288, 76);
	deltaX = tret + (tret / 2) - wImg / 2;
	lineBox2->SetPointDest(deltaX, posNext);
	lineBox2->Text.SetPtsize(56);
	lineBox2->Text.SetFontColor(100, 255, 100, 255);
	lineBox2->SetBorder(true, 2);//установить параметры рамки
	lineBox2->SetHorizontalIndent(10);
	lineBox2->SetHorizontalAlign(CENTER);
	lineBox2->SetText(L"LineBox 2");
	lineBox2->SetVisible(true);
	fon->AddGraphics(lineBox2);

	CLineBox* lineBox3 = new CLineBox(GetInit(), 288, 76);
	deltaX = tret + tret + (tret / 2) - wImg / 2;
	lineBox3->SetPointDest(deltaX, posNext);
	lineBox3->Text.SetPtsize(56);
	lineBox3->Text.SetFontColor(100, 100, 255, 255);
	lineBox3->SetBorder(false);//установить параметры рамки
	lineBox3->SetBorderBottom(true, 2);
	lineBox3->SetHorizontalIndent(10);
	lineBox3->SetHorizontalAlign(RIGHT);
	lineBox3->SetText(L"LineBox 3");
	lineBox3->SetVisible(true);
	fon->AddGraphics(lineBox3);

	posNext += margin + lineBox1->GetHeight();  //добавить свои размеры


	//Ввод и проверка слова
	lable = new CLable( GetInit(), L"Тест" );
	lable->SetFontSize(56);
	lable->SetFontColor(10, 10, 10, 255);
	fon->AddGraphics(lable);

	CLineBox* txt = new CLineBox(GetInit(), 588, 76);
	txt->SetPointDest(20, posNext);
	txt->Text.SetPtsize(42);
	txt->Text.SetFontColor(50, 50, 50, 255);
	txt->Text.SetFCaretka(false);
	txt->SetBorder(false);//установить параметры рамки
	txt->SetHorizontalIndent(10);
	txt->SetText(L"Введите слово 'Тест' либо другое и нажмите Enter");
	txt->SetVisible(true);
	fon->AddGraphics(txt);

	lineBox = new CLineBox(GetInit(), "images/tile/Botton.png");
	lineBox->SetPointDest(610, posNext);
	lineBox->Text.SetPtsize(56);
	lineBox->Text.SetFontColor(10, 10, 10, 255);
	lineBox->SetBorder(true, 2);//установить параметры рамки
	lineBox->SetHorizontalAlign(CENTER);
	lineBox->SetHorizontalIndent(10);
	lineBox->SetVisible(true);
	lineBox->ReceiveFocus();
	lineBox->evSetReturn.SetRunMetod(this, "SetReturn");//Задать событию делегат для выполнения
	fon->AddGraphics(lineBox);

	posNext += margin + txt->GetHeight();  //добавить свои размеры


	//Кнопки для нажатия
	CTile* butt1 = new CTile(
		GetInit(),
		"images/tile/button.png",
		"images/tile/buttonHover.png",
		"images/tile/buttonPress.png",
		"images/tile/buttonPressHover.png");
	wImg = butt1->GetWidth();
	deltaX = width / 4 - wImg / 2;
	butt1->Text.SetPtsize(42);
	butt1->SetPointDest(deltaX, posNext);
	butt1->Text.SetFontColor(255, 255, 255, 255);
	butt1->SetText(L"Трек 1");
	butt1->SetVisible(true);
	butt1->SetMoved(false);
	butt1->evSetPress.SetRunMetod(this, "PlayTrak1");
	fon->AddGraphics(butt1);

	CTile* butt2 = new CTile(
		GetInit(),
		"images/tile/button.png",
		"images/tile/buttonHover.png",
		"images/tile/buttonPress.png",
		"images/tile/buttonPressHover.png");
	deltaX = (width / 4) * 3 - wImg / 2;
	butt2->Text.SetPtsize(42);
	butt2->SetPointDest(deltaX, posNext);
	butt2->Text.SetFontColor(255, 255, 255, 255);
	butt2->SetText(L"Трек 2");
	butt2->SetVisible(true);
	butt2->SetMoved(false);
	butt2->evSetPress.SetRunMetod(this, "PlayTrak2");
	fon->AddGraphics(butt2);


	//Передвигающиеся буквы
	CTile* tile1 = new CTile(
		GetInit(),
		"images/tile/fontD.png",
		"images/tile/fontDhover.png",
		"images/tile/fontD.png",
		"images/tile/fontDhover.png");
	int pol = width / 8;
	wImg = tile1->GetWidth();
	posNext = heigth - tile1->GetHeight() - margin;
	deltaX = pol - wImg / 2;
	tile1->SetPointDest(deltaX, posNext);
	tile1->SetVisible(true);
	tile1->Text.SetPtsize(46);
	tile1->Text.SetFontColor(50, 50, 50, 255);
	tile1->Text.SetText(L"Move");
	fon->AddGraphics(tile1);

	deltaX = pol * 3 - wImg / 2;
	CTile* tile2 = new CTile(
		GetInit(),
		"images/tile/fontE.png",
		"images/tile/fontEhover.png",
		"images/tile/fontE.png",
		"images/tile/fontEhover.png");
	tile2->SetPointDest(deltaX, posNext);
	tile2->SetVisible(true);
	tile2->Text.SetPtsize(46);
	tile2->Text.SetFontColor(50, 50, 255, 255);
	tile2->Text.SetText(L"Move");
	fon->AddGraphics(tile2);

	deltaX = pol * 5 - wImg / 2;
	CTile* tile3 = new CTile(
		GetInit(),
		"images/tile/fontM.png",
		"images/tile/fontMhover.png",
		"images/tile/fontM.png",
		"images/tile/fontMhover.png");
	tile3->SetPointDest(deltaX, posNext);
	tile3->SetVisible(true);
	tile3->Text.SetPtsize(46);
	tile3->Text.SetFontColor(255, 255, 255, 255);
	tile3->Text.SetText(L"Move");
	fon->AddGraphics(tile3);

	deltaX = pol * 7 - wImg / 2;
	CTile* tile4 = new CTile(
		GetInit(),
		"images/tile/fontO.png",
		"images/tile/fontOhover.png",
		"images/tile/fontO.png",
		"images/tile/fontOhover.png");
	tile4->SetPointDest(deltaX, posNext);
	tile4->SetVisible(true);
	tile4->Text.SetPtsize(46);
	tile4->Text.SetFontColor(50, 255, 50, 255);
	tile4->Text.SetText(L"Move");
	fon->AddGraphics(tile4);

	AddCell(fon);
}

void CSectionLessBlink::Blink()
{
	if(lable != nullptr)
	{
		Uint32 currentTime = SDL_GetTicks();

		if(lable->GetVisible())//обработать задержку отображения надписи
		{
			if(timeCheck + delayShow < currentTime)
			{
				lable->SetVisible(false);
				timeCheck = currentTime;
			}
		}
		else//Обработать задержку между отображениями надписи
		{
			if(timeCheck + delayDraw < currentTime)
			{
				SetRandomPosition();
				lable->SetVisible(true);
				timeCheck = currentTime;
			}
		}
	}
}

void CSectionLessBlink::SetRandomPosition()
{
	SDL_Rect rWork = fon->GetRectWork();

	SDL_Rect rDest = {0,0,lable->GetWidth(),lable->GetHeight()};

	int minX = rWork.x;
	int maxX = rWork.x + rWork.w - lable->GetWidth();

	int minY = rWork.y;
	int maxY = rWork.y + rWork.h - lable->GetHeight();

	bool stop = true;
	int i = 0;

	while(stop && i < limitRandIterator)
	{
		rDest.x = minX + rand() % maxX;
		rDest.y = minY + rand() % maxY;
		if(!lineBox->IntersectRect(&rDest))
			stop = false;
		i++;
	}

	if(stop == false)
	{
		lable->SetPointDest(rDest.x,rDest.y);
	}
	else
	{
		//srand( time( 0 ) ); // автоматическая рандомизация
#ifdef _DEBUG
		cout << "Внимание! Превышен лимит итераций в CSectionLessBlink::SetRandomPosition\n" << endl;
#endif
	}
}

void CSectionLessBlink::CompareStr()
{
	wchar_t* str1 = lineBox->Text.GetTextW();
	wchar_t* str2 = lable->GetTextW();
	if(0 == wcscmp(str1, str2))
		audOk.Play();
	else
		audError.Play();
}

//********** End ****

//Метод проигрывания текущего повторяемого слова
void CSectionLessBlink::PlayCurStr()
{
	
}


void CSectionLessBlink::Pause( bool f /*= true */ )
{
	pause = f;
	//maskaGrey->SetVisible(pause);
}

SectionState CSectionLessBlink::Play()
{
	if(!pause)
	{
		//PlayCurStr();
		//Blink();
	}
	return SECT_CURR_LESS;
}

//Будет вызываться при окончании воспроизведения звукового файла
//Для этого его необходимо подписать на нужное событие нужного екземпляра класса CAudio
void CSectionLessBlink::DelegateResumeAudio()
{
	timeCheckPlayCurStr = SDL_GetTicks();
	playStrEnd = true;
}

//Будет вызываться при нажатии клавиши Ентер
void CSectionLessBlink::DelegateSetReturn()
{
	CompareStr();
}

void CSectionLessBlink::DelegateSetVisibleMaska()
{
	//maskaGrey->SetVisible(true);
}

void CSectionLessBlink::DelegateUnSetVisibleMaska()
{
	//maskaGrey->SetVisible(false);
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CSectionLessBlink::RunMyEvent( string metod )
{
	if(metod == "ResumeAudio")
		DelegateResumeAudio();
	else if(metod == "SetReturn")
		DelegateSetReturn();
	else if(metod == "SetVisibleMaska")
		DelegateSetVisibleMaska();
	else if(metod == "UnSetVisibleMaska")
		DelegateUnSetVisibleMaska();
	else if(metod == "PlayTrak1")
		DelegatePlayTrak1();
	else if(metod == "PlayTrak2")
		DelegatePlayTrak2();
}

void CSectionLessBlink::DelegatePlayTrak1()
{
	audOk.Play();
}

void CSectionLessBlink::DelegatePlayTrak2()
{
	audError.Play();
}
