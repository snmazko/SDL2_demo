#include "stdafx.h"


CSectionEndPage::CSectionEndPage( CInit& ini ):CSection(ini)
{

}


CSectionEndPage::~CSectionEndPage(void)
{
}

void CSectionEndPage::InitSection()
{

}

void CSectionEndPage::RunEvent()
{

}

SectionState CSectionEndPage::RunDraw()
{
	return SECT_NULL;
}

//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CSectionEndPage::RunMyEvent( string metod )
{

}
//********** End ****

void CSectionEndPage::Pause( bool f /*= true */ )
{

}

SectionState CSectionEndPage::Play()
{
	return SECT_CURR_LESS;
}