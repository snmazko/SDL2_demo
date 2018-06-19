#include "StdAfx.h"

Uint32 CKeyState::delayFirstPress = 700;
Uint32 CKeyState::delayMorePress = 120;

//************ КОНСТРУКТОР ПО УМОЛЧАНИЮ (ПУСТОЙ) *****************
CKeyState::CKeyState( Uint32 key /*= SDLK_UNKNOWN*/, wchar_t engUpper[] /*= nullptr*/, wchar_t engLower[] /*= nullptr*/, wchar_t rusUpper[] /*= nullptr*/, wchar_t rusLower[] /*= nullptr */ )
{
	mas[0] = nullptr;

	if(engUpper == nullptr) mas[ENG_UP] = nullptr;
	else
	{
		int n = wcslen(engUpper);
		mas[ENG_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_UP], n + 1, engUpper);
	}

	if(engLower == nullptr) mas[ENG_LOW] = nullptr;
	else
	{
		int n = wcslen(engLower);
		mas[ENG_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_LOW], n + 1, engLower);
	}

	if(rusUpper == nullptr) mas[RUS_UP] = nullptr;
	else
	{
		int n = wcslen(rusUpper);
		mas[RUS_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_UP], n + 1, rusUpper);
	}

	if(rusLower == nullptr) mas[RUS_LOW] = nullptr;
	else
	{
		int n = wcslen(rusLower);
		mas[RUS_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_LOW], n + 1, rusLower);
	}

	this->key = key;
	timeCheck = 0;
	isPress = false;
	launchHand = false;
	delayFirst = false;
}

//************ КОНСТРУКТОР КОПИРОВАНИЯ *****************
CKeyState::CKeyState( const CKeyState& Cc )
{
#ifdef _DEBUG
	//printf("Вызван конструктор КОПИРОВАНИЯ класса CKeyState\n");
#endif

	if(Cc.GetChar(ENG_UP) == nullptr) mas[ENG_UP] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(ENG_UP));
		mas[ENG_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_UP], n + 1, Cc.GetChar(ENG_UP));
	}

	if(Cc.GetChar(ENG_LOW) == nullptr) mas[ENG_LOW] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(ENG_LOW));
		mas[ENG_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_LOW], n + 1, Cc.GetChar(ENG_LOW));
	}

	if(Cc.GetChar(RUS_UP) == nullptr) mas[RUS_UP] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(RUS_UP));
		mas[RUS_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_UP], n + 1, Cc.GetChar(RUS_UP));
	}

	if(Cc.GetChar(RUS_LOW) == nullptr) mas[RUS_LOW] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(RUS_LOW));
		mas[RUS_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_LOW], n + 1, Cc.GetChar(RUS_LOW));
	}

	this->key = Cc.GetKey();
	timeCheck = Cc.GetTimeCheck();
	isPress = Cc.GetIsPress();
	launchHand = Cc.GetLaunch();
	delayFirst = Cc.GetDelayFirst();
}

//************ ПЕРЕГРУЗКА ОПЕРАТОРА = *****************
CKeyState& CKeyState::operator=( const CKeyState& Cc )
{
#ifdef _DEBUG
	//printf("Вызван OPERATOR= класса CKeyState\n");
#endif
	if(this == &Cc)
		return *this;

	if(Cc.GetChar(ENG_UP) == nullptr) mas[ENG_UP] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(ENG_UP));
		mas[ENG_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_UP], n + 1, Cc.GetChar(ENG_UP));
	}

	if(Cc.GetChar(ENG_LOW) == nullptr) mas[ENG_LOW] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(ENG_LOW));
		mas[ENG_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[ENG_LOW], n + 1, Cc.GetChar(ENG_LOW));
	}

	if(Cc.GetChar(RUS_UP) == nullptr) mas[RUS_UP] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(RUS_UP));
		mas[RUS_UP] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_UP], n + 1, Cc.GetChar(RUS_UP));
	}

	if(Cc.GetChar(RUS_LOW) == nullptr) mas[RUS_LOW] = nullptr;
	else
	{
		int n = wcslen(Cc.GetChar(RUS_LOW));
		mas[RUS_LOW] = new wchar_t[n + 1];
		wcscpy_s(mas[RUS_LOW], n + 1, Cc.GetChar(RUS_LOW));
	}

	this->key = Cc.GetKey();
	timeCheck = Cc.GetTimeCheck();
	isPress = Cc.GetIsPress();
	launchHand = Cc.GetLaunch();
	delayFirst = Cc.GetDelayFirst();

	return *this;
}

//************ ДЕСТРУКТОР *****************
CKeyState::~CKeyState(void)
{
#ifdef _DEBUG
	//printf("Вызван ДЕСТРУКТОР класса CKeyState\n");
#endif
	delete[] mas[ENG_UP];
	delete[] mas[ENG_LOW];
	delete[] mas[RUS_UP];
	delete[] mas[RUS_LOW];
}


//Возвращает true если включен флаг на обработку нажатия клавиши launchHand
bool CKeyState::SetKeyPress()
{
	//ситуация когда кнопка уже нажата (произошло зажатие клавиши)
	if(isPress)
	{
		Uint32 currentTime = SDL_GetTicks();
		if(!delayFirst)
		{
			if(timeCheck + delayFirstPress > currentTime)
				return false;

			delayFirst = true;
			launchHand = true;
			timeCheck = currentTime;
		}
		else
		{			
			if(timeCheck + delayMorePress > currentTime)
				return false;

			launchHand = true;
			timeCheck = currentTime;
		}
		return true;
	}//ситуация когда кнопка нажата впервые
	else
	{
		isPress = true;
		launchHand = true;
		timeCheck = SDL_GetTicks();
		delayFirst = false;
		return true;
	}
}

void CKeyState::SetKeyRelease()
{
	isPress = false;
	launchHand = false;
	timeCheck = 0;
	delayFirst = false;
}

bool CKeyState::GetLaunchHand()
{
	if(launchHand)
	{
		launchHand = false;
		return true;
	}
	return false;
}