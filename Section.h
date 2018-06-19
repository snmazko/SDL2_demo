/*
Данный клас будет содержать интерфейс для выполняемых в определенный момент текущих либо информационных блоков программы
*/
#pragma once
#include "stdafx.h"


class CSection : public CBaseClass
{
	CInit& init;
    static CSection* currentSection;  //указатель на текущий выполняемый блок
    vector<CCell*> ListCell;          //Вектор с указателями на все секторы которые будут в выполняемой секции

public:
	CSection(CInit& ini);
	virtual ~CSection(void);

    static SectionState RunCurrentSection( bool daraw );  //Запускает метод RunSection() текущей секции

    static void SetCurrentSection(CSection* se);          //устанавливает секцию текущей

	static CSection* GetCurrentSection(){ return currentSection; }//Возвращает указатель на текущую секцию

    //Метод отрабатывает секцию и отображает ее результаты
    //возращает true - если секция закончила свою работу и можно передать управление следующей секции
    virtual void RunEvent() = 0;              //Обработать события выполняемой в данный момент секцией
    virtual SectionState RunDraw() = 0;       //Обобрзить графические элементы выполняемой в данный момент секциеи
    virtual void Pause( bool f = true ) = 0;  //Останавливает рабту секции
    virtual SectionState Play() = 0;          //проигрывает секцию упражнение
    virtual void InitSection() = 0;           //Создать все графические елементы секции

	CInit& GetInit()const{ return init; }

    void AddCell(CCell* se);    //мотод добавляет ссылку на сформированный сектор в список ListSector

	CCell* GetCellUnderMouse();//Получить указатель на раздел секции в котором произошло событие мышки
	
	bool PointInRect( SDL_Point* p, CCell* gr );//проверяет попадает ли точка в рект елемента

    void DrawListCell();    //Вызывает для всех елементов ListSector метод Draw()
};
