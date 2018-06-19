#pragma once
#include "stdafx.h"

void FinishPlayAudio( void );

class CAudio : public CBaseClass
{
	static CAudio* currentAudio;
	SDL_RWops* m_rw;
	vector<unsigned char> m_file;
	Mix_Music * m_music;

	bool fPause;	//Флаг указывает что воспроизведение на паузе
	bool fPlay;		//Флаг указывает что идет воспроизведение

	void ReadFileToBuffer(string filePath);
	friend void FinishPlayAudio( void );

public:

	CAudio(string filePath);
	~CAudio(void);

	static void ResumeCurrentAudio();
	void ResumeAudio();
	MyEvent evResumeAudio;					//Вызывается при вызове метода ResumeAudio

	void Play(int loops = 1);				//запускает воспроизведение с указанным количеством повторений
	MyEvent evPlay;							//Вызывается при вызове метода Play
	bool GetPlay()const { return fPlay; }	//возвращает состояние воспроизведения

	void Stop();							//останавливает воспроизведение
	MyEvent evStop;							//Вызывается при вызове метода Stop

	void Pause();							//делает паузу в воспроизведении
	MyEvent evPause;						//Вызывается при вызове метода Pause
	bool GetPause()const { return fPause; }	//фозвращает состояние паузы воспроизведения

	void Rewaind();							//Возобнавляет воспроизведение
	MyEvent evRewaind;						//Вызывается при вызове метода Rewaind

	void LoadMusic(string filePath);		//Загружает аудио из файла в память

	void WriteFileToBuffer(string filePath);

	//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
	virtual void RunMyEvent(string metod);
	//********** End ****
};