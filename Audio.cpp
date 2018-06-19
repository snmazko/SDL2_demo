#pragma once
#include "stdafx.h"

CAudio* CAudio::currentAudio = nullptr;

CAudio::CAudio( string filePath )
{
	m_rw = nullptr;
	m_music = nullptr;
	LoadMusic(filePath);

	fPause = false;
	fPlay = false;

    //Установить функцию которая вызывается при окончании воспроизведения
    Mix_HookMusicFinished(FinishPlayAudio);
}

CAudio::~CAudio(void)
{
	Stop();
	Mix_FreeMusic(m_music);
	SDL_FreeRW(m_rw);
#ifdef _DEBUG
	cout << "Вызван деструктор CAudio\n";
#endif

}

void CAudio::Play( int loops /*= 1*/ )
{
	if(currentAudio != this)
	{
		if(currentAudio != nullptr)
			currentAudio->ResumeAudio();
		currentAudio = this;
	}

	if(!fPlay)
	{
		if (Mix_PlayMusic(m_music, loops) == -1)
		{
#ifdef _DEBUG
			cout << "Error playing music " + string(Mix_GetError()) + " ...\n";
#endif
		}
		else
		{
			fPlay = true;
			evPlay.Run();
		}
	}
}

void CAudio::LoadMusic( string filePath )
{
    ReadFileToBuffer(filePath);
    m_rw = SDL_RWFromMem(&m_file[0], m_file.size());

    string pr = filePath.substr(filePath.length() - 3);
    Mix_MusicType mType = MUS_NONE;
    if(pr == "mp3" || pr == "MP3")
        mType = MUS_MP3;
    else if(pr == "wav" || pr == "WAV")
        mType = MUS_WAV;
    else if(pr == "ogg" || pr == "OGG")
        mType = MUS_OGG;
    if(mType != MUS_NONE)
    {
        if (m_rw == nullptr)
        {
#ifdef _DEBUG
            cout << "Error creating RW " + string(Mix_GetError()) + " ...\n";
#endif
        }


        m_music = Mix_LoadMUSType_RW(m_rw, mType, SDL_FALSE);

        if(m_music == nullptr)
        {
#ifdef _DEBUG
            cout << "Error creating music " + string(Mix_GetError()) + " ...\n";
#endif
        }
    }
    else
    {
#ifdef _DEBUG
        cout << "Передан не верный формат аудиофайла\n";
#endif
    }

}

void CAudio::ReadFileToBuffer( string filePath )
{
	ifstream file(filePath, ios::binary);

	file.seekg(0, ios::end);
	int fileSize = static_cast<int>(file.tellg());
	file.seekg(0, ios::beg);
	fileSize -= static_cast<int>(file.tellg());

	m_file.resize(fileSize);
	file.read((char *)&(m_file[0]), fileSize);

	file.close();
}

void CAudio::WriteFileToBuffer( string filePath )
{
	ofstream file(filePath, ios::out | ios::binary);
	for (size_t i = 0; i < m_file.size(); i++)
		file << m_file[i];
	file.close();
}

void CAudio::Pause()
{
	if(currentAudio == this && !fPause)
	{
		fPause = true;
		Mix_PausedMusic();
		evPause.Run();
	}
}

void CAudio::Rewaind()
{
	if(currentAudio == this && fPause)
	{
		fPause = false;
		Mix_RewindMusic();
		evRewaind.Run();
	}
}

void CAudio::Stop()
{
	if(currentAudio == this && fPlay)
	{
		Mix_ResumeMusic();
		ResumeAudio();
		evStop.Run();
	}
}

void CAudio::ResumeCurrentAudio()
{
	if(currentAudio != nullptr)
		currentAudio->ResumeAudio();
}

void CAudio::ResumeAudio()
{
	if(currentAudio == this)
	{
		fPause = false;
		fPlay = false;
		currentAudio = nullptr;
		evResumeAudio.Run();
	}
}


//**** ВИРТУАЛЬНЫЕ МЕТОДЫ ДЛЯ ВЗАИМОДЕЙСТВИЯ ОБЪЕКТОВ
void CAudio::RunMyEvent( string metod )
{

}
//**** END ****

void FinishPlayAudio( void )
{
	CAudio::ResumeCurrentAudio();
}
