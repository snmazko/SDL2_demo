#include "StdAfx.h"


CSectionStartPage::CSectionStartPage( CInit& ini ):CSection(ini)
{

}


CSectionStartPage::~CSectionStartPage(void)
{

}

void CSectionStartPage::InitSection()
{

}

void CSectionStartPage::RunEvent()
{

}

SectionState CSectionStartPage::RunDraw()
{
	return SECT_NULL;
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CSectionStartPage::RunMyEvent( string metod )
{

}
//********** End ****

void CSectionStartPage::Pause( bool f /*= true */ )
{

}

SectionState CSectionStartPage::Play()
{
	return SECT_CURR_LESS;
}