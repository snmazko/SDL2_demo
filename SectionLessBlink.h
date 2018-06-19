#pragma once
#include "stdafx.h"

class CSectionLessBlink : public CSection
{
	CAudio audError;
	CAudio audOk;

    bool playStr;               //флаг указывает проигрывать или нет слово
    bool playStrEnd;            //флаг указывает что слово закончило проигрывание

    Uint32 delayPlayCurStr;     //Задержка между повторениями слов
    Uint32 timeCheckPlayCurStr; //Время последнего звучания слова

    Uint32 timeCheck;           //Время последнего отображения надписи
    Uint32 delayShow;           //Время на которое отображается надпись
    Uint32 delayDraw;           //Задержка между отображениями надписи

	const int limitRandIterator;

	CCell* fon;
	CLable* lable;
	CLineBox* lineBox;

	bool pause;

	void CompareStr();//сравнивает строки и вызывает необходимые методы по результатам

public:

	static void StatFun(void);

	CSectionLessBlink(CInit& ini);
	virtual ~CSectionLessBlink(void);

    virtual void RunEvent();              //Обработать события выполняемой в данный момент секцией
    virtual SectionState RunDraw();       //Обобрзить графические элементы выполняемой в данный момент секциеи
    virtual void Pause( bool f = true );  //Останавливает рабту секции (упражнения)
    virtual SectionState Play();          //проигрывает секцию упражнение
    virtual void InitSection();           //Создать все графические елементы данной секции

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****

	void Blink();
	void SetRandomPosition();


    void PlayCurStr();          //Метод проигрывания текущего повторяемого слова
    void DelegateResumeAudio(); //Будет вызываться при окончании воспроизведения звукового файла
    void DelegateSetReturn();   //Будет вызываться при нажатии клавиши Ентер
	void DelegateSetVisibleMaska();
	void DelegateUnSetVisibleMaska();
	void DelegatePlayTrak1();
	void DelegatePlayTrak2();
};
