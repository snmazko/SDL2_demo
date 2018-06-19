#pragma once

//********** ЗАГОЛОВОЧНЫЕ C++ *****
#include <io.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <math.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <typeinfo>
#include <tuple>
#include <ctime>
#include <typeinfo>
// ********* End *********


// *********** ДИНАМИЧЕСКИ ПОДКЛЮЧАЕМЫЕ БИБЛИОТЕКИ *********
#include "librarys/SDL2/include/SDL.h"
#include "librarys/SDL2/include/SDL_image.h"
#include "librarys/SDL2/include/SDL_mixer.h"
//#include "librarys/SDL2-devel/include/SDL.h"
//#include "librarys/SDL2_net/include/SDL_net.h"
#include "librarys/SDL2/include/SDL_ttf.h"
// ********* End *********


// *********** ДИРЕКТИВЫ using *********
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::pair;
using std::tuple;
using std::get;
// ********* End *********


// *********** МОИ ТИПЫ ДАННЫХ *********

enum SectionState{//перечисления для обработки секций
	SECT_ERROR = -1,		//возвращается если при работе секции произошла ошибка
	SECT_NULL = 0,			//возвращается если текущая секция равняется nullptr
	SECT_CURR_LESS,			//возвращается если нужно продолжать выполнение текущего упражнения
	SECT_NEXT_LESS,			//возвращается если упражнение отработало и нужно брать на выполнение следующее упражнение
	SECT_LESS_BLINK,		//возвращается если нужно следующей выполнять секцию sectionLessBlink
	SECT_START_PAGE,		//возвращается если нужно следующей выполнять секцию sectionStartPage
    SECT_END_PAGE			//возвращается если нужно следующей выполнять секцию sectionEndPage
};

//перечисления для выравнивания текста
enum Align{ 
	CENTER = 1,		//при этом выравнивании отступы игнорируются
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

// ********* End *********


//********** ЗАГОЛОВОЧНЫЕ ФАЙЛЫ МОИХ КЛАССОВ *****
#include "BaseClass.h"
typedef CBaseClass::CMyEvent MyEvent;

#include "Audio.h"

#include "Init.h"
#include "Caret.h"
#include "KeyState.h"
#include "TextFlag.h"
#include "Text.h"
#include "Flag.h"

#include "Graphics.h"
#include "Image4Back.h"
#include "Check.h"

#include "Tile.h"
#include "LineBox.h"
#include "CheckBox.h"
#include "Lable.h"

#include "RadioBox.h"

#include "Cell.h"
#include "Section.h"

//еффекты
//#include "EffektExteriorShine.h"

//Секции, упражнения и пр.
#include "SectionLessBlink.h"

#include "SectionStartPage.h"
#include "SectionEndPage.h"

#include "Main.h"

// ********* End *********


