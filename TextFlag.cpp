#include "StdAfx.h"


CTextFlag::CTextFlag(void):
	KF_CAPS(false),
	f_CapsRelease(true),
	KF_SHIFT(false),
	lang(RUS)
{
#ifdef _DEBUG
	printf("Вызван конструктор по умолчанию класса CTextFlag\n");
#endif

	//******* БУКВЫ ***********
	keyChar.insert(Entry(SDLK_a, CKeyState(SDLK_a,L"a",L"A",L"ф",L"Ф")));
	keyChar.insert(Entry(SDLK_b, CKeyState(SDLK_b,L"b",L"B",L"и",L"И")));
	keyChar.insert(Entry(SDLK_c, CKeyState(SDLK_c,L"c",L"C",L"с",L"С")));
	keyChar.insert(Entry(SDLK_d, CKeyState(SDLK_d,L"d",L"D",L"в",L"В")));
	keyChar.insert(Entry(SDLK_e, CKeyState(SDLK_e,L"e",L"E",L"у",L"У")));
	keyChar.insert(Entry(SDLK_f, CKeyState(SDLK_f,L"f",L"F",L"а",L"А")));
	keyChar.insert(Entry(SDLK_g, CKeyState(SDLK_g,L"g",L"G",L"п",L"П")));
	keyChar.insert(Entry(SDLK_h, CKeyState(SDLK_h,L"h",L"H",L"р",L"Р")));
	keyChar.insert(Entry(SDLK_i, CKeyState(SDLK_i,L"i",L"I",L"ш",L"Ш")));
	keyChar.insert(Entry(SDLK_j, CKeyState(SDLK_j,L"j",L"J",L"о",L"О")));
	keyChar.insert(Entry(SDLK_k, CKeyState(SDLK_k,L"k",L"K",L"л",L"Л")));
	keyChar.insert(Entry(SDLK_l, CKeyState(SDLK_l,L"l",L"L",L"д",L"Д")));
	keyChar.insert(Entry(SDLK_m, CKeyState(SDLK_m,L"m",L"M",L"ь",L"Ь")));
	keyChar.insert(Entry(SDLK_n, CKeyState(SDLK_n,L"n",L"N",L"т",L"Т")));
	keyChar.insert(Entry(SDLK_o, CKeyState(SDLK_o,L"o",L"O",L"щ",L"Щ")));
	keyChar.insert(Entry(SDLK_p, CKeyState(SDLK_p,L"p",L"P",L"з",L"З")));
	keyChar.insert(Entry(SDLK_q, CKeyState(SDLK_q,L"q",L"Q",L"й",L"Й")));
	keyChar.insert(Entry(SDLK_r, CKeyState(SDLK_r,L"r",L"R",L"к",L"К")));
	keyChar.insert(Entry(SDLK_s, CKeyState(SDLK_s,L"s",L"S",L"ы",L"Ы")));
	keyChar.insert(Entry(SDLK_t, CKeyState(SDLK_t,L"t",L"T",L"е",L"Е")));
	keyChar.insert(Entry(SDLK_u, CKeyState(SDLK_u,L"u",L"U",L"г",L"Г")));
	keyChar.insert(Entry(SDLK_v, CKeyState(SDLK_v,L"v",L"V",L"м",L"М")));
	keyChar.insert(Entry(SDLK_w, CKeyState(SDLK_w,L"w",L"W",L"ц",L"Ц")));
	keyChar.insert(Entry(SDLK_x, CKeyState(SDLK_x,L"x",L"X",L"ч",L"Ч")));
	keyChar.insert(Entry(SDLK_y, CKeyState(SDLK_y,L"y",L"Y",L"н",L"Н")));
	keyChar.insert(Entry(SDLK_z, CKeyState(SDLK_z,L"z",L"Z",L"я",L"Я")));

    keyChar.insert(Entry(SDLK_LEFTBRACKET, CKeyState(SDLK_LEFTBRACKET,L"[",L"[",L"х",L"Х")));	//	'['
	keyChar.insert(Entry(SDLK_RIGHTBRACKET, CKeyState(SDLK_RIGHTBRACKET,L"]",L"]",L"ъ",L"Ъ")));	//	']'
    keyChar.insert(Entry(SDLK_COLON, CKeyState(SDLK_COLON,L":",L":",L"ж",L"Ж")));				//	':'
    keyChar.insert(Entry(SDLK_SEMICOLON, CKeyState(SDLK_SEMICOLON,L";",L";",L"ж",L"Ж")));		//	';'
    keyChar.insert(Entry(SDLK_QUOTEDBL, CKeyState(SDLK_QUOTEDBL,L"\"",L"\"",L"э",L"Э")));		//	'"'
    keyChar.insert(Entry(SDLK_QUOTE, CKeyState(SDLK_QUOTE,L"'",L"'",L"э",L"Э")));				//	'\''
    keyChar.insert(Entry(SDLK_BACKQUOTE, CKeyState(SDLK_BACKQUOTE,L"`",L"`",L"ё",L"Ё")));		//	'`'
    keyChar.insert(Entry(SDLK_LESS, CKeyState(SDLK_LESS,L"<",L"<",L"б",L"Б")));					//	'<'
    keyChar.insert(Entry(SDLK_GREATER, CKeyState(SDLK_GREATER,L">",L">",L"ю",L"Ю")));			//	'>'
    keyChar.insert(Entry(SDLK_PERIOD, CKeyState(SDLK_PERIOD,L".",L".",L"ю",L"Ю")));				//	'.'
    keyChar.insert(Entry(SDLK_COMMA, CKeyState(SDLK_COMMA,L",",L",",L"б",L"Б")));				//	','

	keyChar.insert(Entry(SDLK_SPACE, CKeyState(SDLK_SPACE,L" ",L" ",L" ",L" ")));

	//******* ЦИФРЫ ***********
	keyChar.insert(Entry(SDLK_0, CKeyState(SDLK_0,L"0",L"0",L"0",L"0")));
	keyChar.insert(Entry(SDLK_1, CKeyState(SDLK_1,L"1",L"1",L"1",L"1")));
	keyChar.insert(Entry(SDLK_2, CKeyState(SDLK_2,L"2",L"2",L"2",L"2")));
	keyChar.insert(Entry(SDLK_3, CKeyState(SDLK_3,L"3",L"3",L"3",L"3")));
	keyChar.insert(Entry(SDLK_4, CKeyState(SDLK_4,L"4",L"4",L"4",L"4")));
	keyChar.insert(Entry(SDLK_5, CKeyState(SDLK_5,L"5",L"5",L"5",L"5")));
	keyChar.insert(Entry(SDLK_6, CKeyState(SDLK_6,L"6",L"6",L"6",L"6")));
	keyChar.insert(Entry(SDLK_7, CKeyState(SDLK_7,L"7",L"7",L"7",L"7")));
	keyChar.insert(Entry(SDLK_8, CKeyState(SDLK_8,L"8",L"8",L"8",L"8")));
	keyChar.insert(Entry(SDLK_9, CKeyState(SDLK_9,L"9",L"9",L"9",L"9")));

	//******* СПЕЦСИМВОЛЫ ***********
    keyChar.insert(Entry(SDLK_EXCLAIM, CKeyState(SDLK_EXCLAIM,L"!",L"!",L"!",L"!")));			//	'!'
    keyChar.insert(Entry(SDLK_HASH, CKeyState(SDLK_HASH,L"#",L"#",L"#",L"#")));					//	'#'
    keyChar.insert(Entry(SDLK_PERCENT, CKeyState(SDLK_PERCENT,L"%",L"%",L"%",L"%")));			//	'%'
    keyChar.insert(Entry(SDLK_DOLLAR, CKeyState(SDLK_DOLLAR,L"$",L"$",L"$",L"$")));				//	'$'
    keyChar.insert(Entry(SDLK_AMPERSAND, CKeyState(SDLK_AMPERSAND,L"&",L"&",L"&",L"&")));		//	'&'
    keyChar.insert(Entry(SDLK_LEFTPAREN, CKeyState(SDLK_LEFTPAREN,L"(",L"(",L"(",L"(")));		//	'('
    keyChar.insert(Entry(SDLK_RIGHTPAREN, CKeyState(SDLK_RIGHTPAREN,L")",L")",L")",L")")));		//	')'
    keyChar.insert(Entry(SDLK_ASTERISK, CKeyState(SDLK_ASTERISK,L"*",L"*",L"*",L"*")));			//	'*'
    keyChar.insert(Entry(SDLK_PLUS, CKeyState(SDLK_PLUS,L"+",L"+",L"+",L"+")));					//	'+'
    keyChar.insert(Entry(SDLK_MINUS, CKeyState(SDLK_MINUS,L"-",L"-",L"-",L"-")));				//	'-'
    keyChar.insert(Entry(SDLK_SLASH, CKeyState(SDLK_SLASH,L"/",L"/",L"/",L"/")));				//	'/'
    keyChar.insert(Entry(SDLK_EQUALS, CKeyState(SDLK_EQUALS,L"=",L"=",L"=",L"=")));				//	'='
    keyChar.insert(Entry(SDLK_QUESTION, CKeyState(SDLK_QUESTION,L"?",L"?",L"?",L"?")));			//	'?'
    keyChar.insert(Entry(SDLK_AT, CKeyState(SDLK_AT,L"@",L"@",L"@",L"@")));						//	'@'
    keyChar.insert(Entry(SDLK_BACKSLASH, CKeyState(SDLK_BACKSLASH,L"\\",L"\\",L"\\",L"\\")));	//	'\\'
    keyChar.insert(Entry(SDLK_CARET, CKeyState(SDLK_CARET,L"^",L"^",L"^",L"^")));				//	'^'
    keyChar.insert(Entry(SDLK_UNDERSCORE, CKeyState(SDLK_UNDERSCORE,L"_",L"_",L"_",L"_")));		//	'_'

	//******* ПЕРЕДВИЖЕНИЕ УДАЛЕНИЕ ***********
	keyChar.insert(Entry(SDLK_LEFT, CKeyState(SDLK_LEFT)));
	keyChar.insert(Entry(SDLK_RIGHT, CKeyState(SDLK_RIGHT)));	
	keyChar.insert(Entry(SDLK_DELETE, CKeyState(SDLK_DELETE)));
	keyChar.insert(Entry(SDLK_BACKSPACE, CKeyState(SDLK_BACKSPACE)));

}


CTextFlag::~CTextFlag(void)
{
}


// *****************  PUBLIC ******************
//проверяет наличие ключа в картах и обрабатывет нажатие клавиши
//return true если клавиша есть и нужно запускать обработку, иначе false
//Также проверяе подлежит ли клавиша отображению после обработки нажатия
//в ссылку на строку stroka записывается строка клавиши в зависимости от языка и нажатых капс и шифт
bool CTextFlag::K_DownKey( Uint32 key, wchar_t* stroka )
{
    auto iter = keyChar.find(key);  //Вернуть итератор указывающий на ключ клавиши
    if(iter != keyChar.end())       //если есть клавиша в нашей карте, запускаем обработчик нажатия
	{
		if(iter->second.SetKeyPress())
		{
			iter->second.GetLaunchHand();//если нужно обрабатывать нажатие
			//Проверить комбинацию нажтия клавиш капс лук и шифт чтобы понять какой регистр отображать
			int fl = lang;
			bool Low = KF_CAPS;
			if(KF_SHIFT) Low = !Low;
			if(Low) fl++;

			switch(fl)
			{
			case 1:
				if(nullptr != iter->second.GetChar(iter->second.ENG_UP))
				{
					int n = wcslen(iter->second.GetChar(iter->second.ENG_UP));
					wcscpy_s(stroka, n + 1, iter->second.GetChar(iter->second.ENG_UP));
				}
				else
					wcscpy_s(stroka, 1, L"");
				break;

			case 2:
				if(nullptr != iter->second.GetChar(iter->second.ENG_LOW))
				{
					int n = wcslen(iter->second.GetChar(iter->second.ENG_LOW));
					wcscpy_s(stroka, n + 1, iter->second.GetChar(iter->second.ENG_LOW));
				}
				else
					wcscpy_s(stroka, 1, L"");
				break;

			case 3:
				if(nullptr != iter->second.GetChar(iter->second.RUS_UP))
				{
					int n = wcslen(iter->second.GetChar(iter->second.RUS_UP));
					wcscpy_s(stroka, n + 1, iter->second.GetChar(iter->second.RUS_UP));
				}
				else
					wcscpy_s(stroka, 1, L"");
				break;

			case 4:
				if(nullptr != iter->second.GetChar(iter->second.RUS_LOW))
				{
					int n = wcslen(iter->second.GetChar(iter->second.RUS_LOW));
					wcscpy_s(stroka, n + 1, iter->second.GetChar(iter->second.RUS_LOW));
				}
				else
					wcscpy_s(stroka, 1, L"");
				break;
			}
			return true;
		}
	}
	return false;
}

//проверяет наличие ключа в картах и обрабатывет отжатие клавиши, return true если клавиша есть, иначе false
bool CTextFlag::K_UpKey( Uint32 key )
{
    auto iter = keyChar.find(key);  //Вернуть итератор указывающий на ключ клавиши
    if(iter !=  keyChar.end())      //если есть клавиша в нашей карте, запускаем обработчик отпускания
	{
		iter->second.SetKeyRelease();
		return true;
	}
	return false;
}


//Обработчик нажатия клавиши Caps Loock вернет состояние Caps Loock true - велючен, false - выключен 
bool CTextFlag::K_DownCaps()
{
    if(KF_CAPS && f_CapsRelease)        //если капс включен и уже отжимался - выключаем капс
		KF_CAPS = false;
    else if(!KF_CAPS && f_CapsRelease)  //если капс выключен и уже отжимался - включаем капс
		KF_CAPS = true;

	f_CapsRelease = false;
	return KF_CAPS;
}
