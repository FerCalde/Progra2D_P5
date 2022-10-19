#include "AudioBuffer.h"

//#include "AL/alc.h"
//#include "AL/alext.h"
//#include "AL/alut.h"
//#include "AL/efx.h"
//#include "AL/efx-creative.h"
//#include "AL/efx-presets.h"

#include <fstream>     
#include <iostream>



AudioBuffer::AudioBuffer()
{
	m_bufferID = new ALuint;
}

bool AudioBuffer::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int AudioBuffer::convertToInt(char* _cBuffer, int _iLenght)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < _iLenght; i++)
			((char*)&a)[i] = _cBuffer[i];
	else
		for (int i = 0; i < _iLenght; i++)
			((char*)&a)[3 - i] = _cBuffer[i];
	return a;
}

AudioBuffer::AudioBuffer(const char* _cFileName)
{
	m_bufferID = new ALuint;

	//Load WAV
	//m_pData = LoadWav(_cFileName, m_iChannel, m_iSampleRate, m_iBps, m_iSize);
	char* auxData = LoadWav(_cFileName, m_iChannel, m_iSampleRate, m_iBps, m_iSize);
	//Generate Buffer
	alGenBuffers(1, m_bufferID);

	if (m_iChannel == 1)
	{
		if (m_iBps == 8)
		{
			m_uiFormat = AL_FORMAT_MONO8;
		}
		else
		{
			m_uiFormat = AL_FORMAT_MONO16;
		}
	}
	else
	{
		if (m_iBps == 8)
		{
			m_uiFormat = AL_FORMAT_STEREO8;
		}
		else
		{
			m_uiFormat = AL_FORMAT_STEREO16;
		}
	}
	
	//Load audioFile in Data
	//alBufferData(*m_bufferID, m_uiFormat, m_pData, m_iSize, m_iSampleRate);
	alBufferData(*m_bufferID, m_uiFormat, auxData, m_iSize, m_iSampleRate);
	
	//Now data is in the buffer, we can delete it
	/*delete[] m_pData;
	m_pData = nullptr;*/
	delete[] auxData;
	auxData = nullptr;
}

AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, m_bufferID);
	m_bufferID = nullptr;
}

AudioBuffer* AudioBuffer::Load(const char* filename)
{
	return nullptr;
}

char* AudioBuffer::LoadWav(const char* _cFileName, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	std::ifstream in(_cFileName, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "this is not a valid WAVE file" << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);      //data
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);
	char* data = new char[size];
	in.read(data, size);
	return data;
}

ALuint* AudioBuffer::GetAlBufferID() const
{
	return m_bufferID;
}
