#include "AudioSource.h"
//#include "AudioBuffer.h"
//#include "MyVector2D.h"


AudioSource::AudioSource(AudioBuffer* _audioBuffer, bool _PlayOnAwake)
	: m_audioBuffer(_audioBuffer),
	m_bLoop(false),
	m_fPitch(1),
	m_fGain(1),
	m_Position(0, 0),
	m_Velocity(0, 0),
	m_bIsPlaying(false)
	//m_bPlayOnAwake(_PlayOnAwake)

{

	//Generate Source and asign id into sourceBufferID
	m_sourceBufferID = new ALuint;
	alGenSources(1, m_sourceBufferID);

	//SetupEffects
	alSourcei(*m_sourceBufferID, AL_LOOPING, m_bLoop);
	alSourcef(*m_sourceBufferID, AL_PITCH, m_fPitch);
	alSourcef(*m_sourceBufferID, AL_GAIN, m_fGain);
	alSource3f(*m_sourceBufferID, AL_POSITION, m_Position.x, m_Position.y, 0);
	alSource3f(*m_sourceBufferID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, 0);

	//Assign buffer to source
	alSourcei(*m_sourceBufferID, AL_BUFFER, *m_audioBuffer->GetAlBufferID());

	if (_PlayOnAwake)	/*if(m_bPlayOnAwake)*/
	{
		Play();
	}
}



AudioSource::~AudioSource()
{
	alDeleteSources(1, m_sourceBufferID);
	m_sourceBufferID = nullptr;
	delete m_audioBuffer;
	m_audioBuffer = nullptr;
}

void AudioSource::SetPitch(float _fPitch)
{
	m_fPitch = _fPitch;
	alSourcef(*m_sourceBufferID, AL_PITCH, m_fPitch);
}

float AudioSource::GetPitch()
{
	return m_fPitch;
}

void AudioSource::SetGain(float _fGain)
{
	m_fGain = _fGain;
	alSourcef(*m_sourceBufferID, AL_GAIN, m_fGain);
}

float AudioSource::GetGain()
{
	return m_fGain;
}

void AudioSource::SetLooping(bool _bLoop)
{
	m_bLoop = _bLoop;
	alSourcei(*m_sourceBufferID, AL_LOOPING, m_bLoop);
}

bool AudioSource::GetLooping()
{
	return m_bLoop;
}

void AudioSource::SetPosition(float _x, float _y, float _z)
{
	m_Position.x = _x;
	m_Position.y = _y;
	//m_Position->z = _z;

	alSource3f(*m_sourceBufferID, AL_POSITION, m_Position.x, m_Position.y, 0);

}

void AudioSource::SetPosition(MyVec2D _pos)
{
	m_Position = _pos;

	alSource3f(*m_sourceBufferID, AL_POSITION, m_Position.x, m_Position.y, 0);
}

MyVec2D AudioSource::GetPosition()
{
	return m_Position;
}

void AudioSource::SetVelocity(float _x, float _y, float _z)
{
	m_Velocity.x = _x;
	m_Velocity.y = _y;

	alSource3f(*m_sourceBufferID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, 0);
}

void AudioSource::SetVelocity(MyVec2D _vel)
{
	m_Velocity = _vel;

	alSource3f(*m_sourceBufferID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, 0);
}

void AudioSource::Play()
{
	//if (m_sourceBufferID)
	{
		alSourcePlay(*m_sourceBufferID);
		m_bIsPlaying = true;
	}
}

void AudioSource::Stop()
{
	alSourceStop(*m_sourceBufferID);
	m_bIsPlaying = false;
}

void AudioSource::Pause()
{
	alSourcePause(*m_sourceBufferID);
	m_bIsPlaying = false;
}

bool AudioSource::IsPlaying() const
{
	return m_bIsPlaying;
}
