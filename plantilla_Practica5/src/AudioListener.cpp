#include "AudioListener.h"
#include "AL/al.h"
#include "AL/alc.h"

AudioListener::AudioListener() 
{
	SetPosition(0);
	SetVelocity(0);
	SetOrientation(0);
}

AudioListener::AudioListener(MyVec2D _pos, MyVec2D _vel, MyVec2D _ori)
	: m_Position(_pos),
	m_Velocity(_vel),
	m_Orientation(_ori)
{
	alListener3f(AL_POSITION, m_Position.x, m_Position.y, 0);
	alListener3f(AL_VELOCITY, m_Velocity.x, m_Velocity.y, 0);
	alListener3f(AL_ORIENTATION, m_Orientation.x, m_Orientation.y, 0);
}

AudioListener::~AudioListener()
{
}

void AudioListener::SetPosition(MyVec2D _pos)
{
	m_Position = _pos;
	alListener3f(AL_POSITION, m_Position.x, m_Position.y, 0);
}

void AudioListener::SetPosition(float _x, float _y, float _z)
{
	m_Position.x = _x;
	m_Position.y = _y;
	//m_Position->z = _z;

	alListener3f(AL_POSITION, m_Position.x, m_Position.y, 0);
}

void AudioListener::SetVelocity(MyVec2D _vel)
{
	m_Velocity = _vel;
	alListener3f(AL_VELOCITY, m_Velocity.x, m_Velocity.y, 0);
}

void AudioListener::SetOrientation(MyVec2D _ori)
{
	m_Orientation = _ori;
	alListener3f(AL_ORIENTATION, m_Orientation.x, m_Orientation.y, 0);
}
