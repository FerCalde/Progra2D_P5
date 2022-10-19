#pragma once
#include "AL/al.h"



class AudioBuffer
{
private:
	ALuint* m_bufferID;

	int m_iChannel = 0;
	int m_iSampleRate = 0;
	int m_iBps = 0;
	int m_iSize = 0;
	unsigned int m_uiFormat = 0;
	//char* m_pData;


	bool isBigEndian();
	int convertToInt(char* _cBuffer, int _iLenght);



public:
	AudioBuffer();
	AudioBuffer(const char* _cFileName);
	~AudioBuffer();

	static AudioBuffer* Load(const char* _filename);
	char* LoadWav(const char* _cFileName, int& chan, int& samplerate, int& bps, int& size);
	ALuint* GetAlBufferID() const;

};