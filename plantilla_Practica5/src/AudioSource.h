#pragma once
#include "AudioBuffer.h"
#include "MyVector2D.h"

//#include "AL/al.h"

//class AudioBuffer;

class AudioSource
{
	AudioBuffer* m_audioBuffer;
	ALuint* m_sourceBufferID;

public:
	AudioSource(AudioBuffer* _audioBuffer, bool _PlayOnAwake = false);
	~AudioSource();

	float m_fPitch = 1.f;
	void SetPitch(float _fPitch = 1);
	float GetPitch();
	float m_fGain = 1.f;
	void SetGain(float _fGain = 1);
	float GetGain();
	bool m_bLoop = false;
	void SetLooping(bool _bLoop);
	bool GetLooping();

	MyVec2D m_Position{0,0};
	void SetPosition(float _x = 0, float _y = 0, float _z = 0);
	void SetPosition(MyVec2D _pos);
	MyVec2D GetPosition();

	MyVec2D m_Velocity{0,0};
	void SetVelocity(float _x = 0, float _y = 0, float _z = 0);
	void SetVelocity(MyVec2D _vel);



	void Play();
	void Stop();
	void Pause();
	bool IsPlaying() const;

	bool m_bIsPlaying = false;
	//bool m_bPlayOnAwake = false;
	//void SetPlayOnAwake(); //Directamente en el constructor

};