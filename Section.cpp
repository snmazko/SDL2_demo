#include "StdAfx.h"

CSection* CSection::currentSection = nullptr;

CSection::CSection(CInit& ini):init(ini)
{
	
}


CSection::~CSection(void)
{
	vector<CCell*>::iterator it;
	for(it = ListCell.begin(); it != ListCell.end(); it++)
	{
		if(*it != nullptr)
			delete (*it);
		(*it) = nullptr;
	}
}


void CSection::SetCurrentSection( CSection* se )
{
	currentSection = se;
}

SectionState CSection::RunCurrentSection( bool daraw )
{
	if(currentSection != nullptr)
	{
		currentSection->RunEvent();

		if(daraw)//отобразить графику
			return currentSection->RunDraw();

		return SECT_CURR_LESS;
	}
	else
		return SECT_NULL;
}

CCell* CSection::GetCellUnderMouse()
{
	SDL_Point pointMouse;
	SDL_GetMouseState(&pointMouse.x, &pointMouse.y);//получить положение мышки

	vector<CCell*>::reverse_iterator it;
	for(it=ListCell.rbegin(); it!=ListCell.rend(); it++)
		if(PointInRect(&pointMouse, *it) && (*it)->GetVisible())
			return (*it);

	return nullptr;
}

//проверяет попадает ли точка в рект елемента
bool CSection::PointInRect( SDL_Point* p, CCell* gr )
{
	SDL_Rect r = gr->GetRectSrc();
	if(p->x >= r.x && p->x <= (r.x + r.w) && p->y >= r.y && p->y <= (r.y + r.h))
		return true;
	else
		return false;
}

void CSection::DrawListCell()
{
	vector<CCell*>::iterator it;
	for(it = ListCell.begin(); it != ListCell.end(); it++)
		(*it)->Draw();
}

void CSection::AddCell( CCell* se )
{
	ListCell.push_back(se);
}
