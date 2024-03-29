#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION

#include "main.h"


//#include "Font.h"
#include "AudioSource.h"
#include "AudioListener.h"

#include "MyVector2D.h"
#include "Sprite.h"

#include <glfw3.h>
#include <iostream>
#include <vector>

#include <sstream>
#include <cstring>////
#include <string>//
#include <fstream>     
#include <iterator>

#include "AL/alc.h"


using namespace std;


/* VARIABLES PRACTICA 1*/
int weightWindowScreen = 1920;
int heightWindowScreen = 1080;
GLFWwindow* myWindow;

double currentTime;
double previousTime;
double deltaTime;
double* delt = nullptr;
double fixedTick = 0.016; // 1/60 para que sean 60 fps
double dangerTicks = 1 / 15;

MyVec2D myCursorPos;
double mouseXpos(0);
double mouseYpos(0);

float fToleranceMovement = 10.f;


/* VARIABLES PRACTICA 4*/
const char* bee_fileName = "data/bee.png";
const char* beeAnim_fileName = "data/bee_anim.png";
const char* ball_fileName = "data/ball.png";
const char* box_fileName = "data/box.png";
const char* circle_fileName = "data/circle.png";
const char* rect_fileName = "data/rect.png";

void CallbackUpdateSprite(Sprite& _sprite, float _fDeltaTime);
void CallbackUpdateSpriteMouse(Sprite& _sprite, float _fDeltaTime);


/* -----VARS P2 AUDIO----- */
const char* audio_fileName = "data/CantinaBand60.wav";
float fDistSource = (heightWindowScreen * 0.25f); //a un cuarto del alto de la pantalla. Origin will be Center Screen
float fDistListener = 100;
MyVec2D middleScreen(weightWindowScreen * 0.5f, heightWindowScreen * 0.5f); //Static middle Screen

//Rotacion CircleSource
float rotationCurrentFrame = 0.f;
float sourceSpeed = 55.f;
float fDopplerFactor =1.f;
float fGain = 325.f;

int main()
{
	//Iniciar libreria GFWX
	int inicializarGlfw = glfwInit();

	if (inicializarGlfw == GLFW_TRUE)
	{

		printf("CORRECTA INICIALIZACION GLFW lib\n");
		//Crear Ventana
		myWindow = (glfwCreateWindow(weightWindowScreen, heightWindowScreen, "HelloWorldWindowed", nullptr, nullptr));

		//Cambiar nombre a la ventana
		glfwSetWindowTitle(myWindow, "Practica5 FerCalderon");

		//Asociar contexto OpenGL a ventana
		glfwMakeContextCurrent(myWindow);


		////////// INICIAR LIBRERIA OPENAL //////////
		  //  //Crear Dispositivo
		ALCdevice* myDevice = alcOpenDevice(NULL); //Con NULL selecciono el dispositivo por defecto
		//  //Crear Context y asociarlo con myDevice
		if (myDevice)
		{
			ALCcontext* myContext = alcCreateContext(myDevice, NULL);
			alcMakeContextCurrent(myContext);
			cout << "CORRECTA INICIALIZACION OPENAL lib\n";
		}


		lgfx_setup2d(weightWindowScreen, heightWindowScreen);



		//Carga de ficheros


		//CREATE BUFFER
		AudioBuffer* myAudioBuffer = new AudioBuffer(audio_fileName);

		//CREATE SOURCE 
		// 
		AudioSource* myAudioSource = new AudioSource(myAudioBuffer, true);
		myAudioSource->SetPosition(weightWindowScreen * 0.5f, (heightWindowScreen * 0.5f) + fDistSource, 0.f);
		myAudioSource->SetGain(fGain);
		myAudioSource->SetVelocity(sourceSpeed, sourceSpeed, sourceSpeed);
		alDopplerFactor(fDopplerFactor);
		//CREATE LISTENER
		AudioListener* myAudioListener = new AudioListener(0, 0, 0);
		myAudioListener->SetPosition(weightWindowScreen * 0.5f, heightWindowScreen - 200.f, 0.f);
		


#pragma region LOAD_FONTS

		///* VARIABLES PRACTICA 3*/
		//std::vector<FontDrawable*> FontDrawableList;
		//const char* text_HelloWorld("Hello, World!");

		////Carga de ficheros de imagen
		//FontManager* ptrFontManager = new FontManager();

		//Font* auxFont = ptrFontManager->Load("data/SFSlapstickComic.ttf", 50);
		//ptrFontManager->m_LoadedFontArray.push_back(auxFont);

		//auxFont = ptrFontManager->Load("data/Orange.ttf", 50);
		//ptrFontManager->m_LoadedFontArray.push_back(auxFont);

		//auxFont = nullptr;

#pragma endregion LOAD_FONTS


#pragma region LOAD_TEXTURES

		SpriteManager* ptrSpriteManager = new SpriteManager();
		ptrSpriteManager->LoadTexture(bee_fileName);
		ptrSpriteManager->LoadTexture(ball_fileName);
		ptrSpriteManager->LoadTexture(box_fileName);
		ptrSpriteManager->LoadTexture(circle_fileName);
		ptrSpriteManager->LoadTexture(rect_fileName);

		std::cout << "Creacion ptrSpriteManager\n";

		//Sprite Bee created
		Sprite* ptrBeePlayer = new Sprite(ptrSpriteManager->m_vTextureArray[0]);
		ptrBeePlayer->SetFPS(0);
		ptrBeePlayer->SetBlend(BLEND_ALPHA);
		MyVec2D initialPosMiddleScreen(weightWindowScreen * 0.5f, heightWindowScreen * 0.5f);
		ptrBeePlayer->SetPosition(initialPosMiddleScreen);
		ptrBeePlayer->SetCallback(&CallbackUpdateSpriteMouse);
		ptrBeePlayer->SetCollisionType(COLLISION_PIXELS);
		std::cout << "Creacion ptrBee\n";


		Sprite* ptrBall = new Sprite(ptrSpriteManager->m_vTextureArray[1]);
		ptrBall->SetFPS(0);
		ptrBall->SetBlend(BLEND_ALPHA);
		ptrBall->SetPosition(initialPosMiddleScreen);
		ptrBall->SetCallback(&CallbackUpdateSprite);
		ptrBall->SetCollisionType(COLLISION_CIRCLE);
		ptrSpriteManager->LoadSprite(ptrBall);

		Sprite* ptrBox = new Sprite(ptrSpriteManager->m_vTextureArray[2]);
		ptrBox->SetFPS(0);
		ptrBox->SetBlend(BLEND_ALPHA);
		ptrBox->SetPosition(initialPosMiddleScreen.x*0.5f, initialPosMiddleScreen.y);
		ptrBox->SetCallback(&CallbackUpdateSprite);
		ptrBox->SetCollisionType(COLLISION_RECT);
		ptrSpriteManager->LoadSprite(ptrBox);


		Sprite* ptrBeeStatic = new Sprite(ptrSpriteManager->m_vTextureArray[0]);
		ptrBeeStatic->SetFPS(0);
		ptrBeeStatic->SetBlend(BLEND_ALPHA);
		ptrBeeStatic->SetPosition((initialPosMiddleScreen.x * 0.5f) + initialPosMiddleScreen.x, initialPosMiddleScreen.y);
		ptrBeeStatic->SetCallback(&CallbackUpdateSprite);
		ptrBeeStatic->SetCollisionType(COLLISION_PIXELS);
		ptrSpriteManager->LoadSprite(ptrBeeStatic);


#pragma endregion LOAD_TEXTURES

		previousTime = glfwGetTime();

		while (glfwWindowShouldClose(myWindow) != 1)
		{

			//Actualizar deltaTiempo
			currentTime = glfwGetTime();
			deltaTime += (currentTime - previousTime);
			previousTime = currentTime;

			while (deltaTime >= fixedTick)
			{

				std::cout << " LOGIC Loop\n";
				//std::cout << deltaTime << " Es el deltaTime Actual\n";

#pragma region INPUT

				//Leer Input de usuario


				if (glfwGetKey(myWindow, GLFW_KEY_ESCAPE))
				{
					glfwSetWindowTitle(myWindow, "Cierra");
					glfwSetWindowShouldClose(myWindow, 1);
				}

				if (glfwGetKey(myWindow, GLFW_KEY_I))
				{
					myAudioSource->Play();
				}
				if (glfwGetKey(myWindow, GLFW_KEY_P))
				{
					myAudioSource->Pause();
				}
				if (glfwGetKey(myWindow, GLFW_KEY_O))
				{
					myAudioSource->Stop();
				}
				if (glfwGetKey(myWindow, GLFW_KEY_L))
				{
					myAudioSource->SetLooping(!myAudioSource->GetLooping());
				}
				//MODIFY PITCH
				if (glfwGetKey(myWindow, GLFW_KEY_UP))
				{
					float fAuxPitch = myAudioSource->GetPitch() + (1.f * deltaTime);
					if (fAuxPitch < 3)
					{
						myAudioSource->SetPitch(fAuxPitch);
					}
				}
				if (glfwGetKey(myWindow, GLFW_KEY_DOWN))
				{
					float fAuxPitch = myAudioSource->GetPitch() + (-1.f * deltaTime);
					if (fAuxPitch > 0.5f)
					{
						myAudioSource->SetPitch(fAuxPitch);
					}
				}
				//MODIFY POS
				if (glfwGetKey(myWindow, GLFW_KEY_RIGHT))
				{
					MyVec2D auxPos = myAudioSource->GetPosition();
					auxPos.x += (0.1f * deltaTime);
					myAudioSource->SetPosition(auxPos);
				}
				if (glfwGetKey(myWindow, GLFW_KEY_LEFT))
				{
					MyVec2D auxPos = myAudioSource->GetPosition();
					auxPos.x += (-0.1f * deltaTime);
					myAudioSource->SetPosition(auxPos);
				}

				//Change Sprites 
				if (glfwGetMouseButton(myWindow, GLFW_MOUSE_BUTTON_LEFT))
				{
					ptrBeePlayer->SetTexture(ptrSpriteManager->m_vTextureArray[3]);
					ptrBeePlayer->SetFPS(0);
					ptrBeePlayer->SetCollisionType(COLLISION_CIRCLE);
				}
				if (glfwGetMouseButton(myWindow, GLFW_MOUSE_BUTTON_RIGHT))
				{
					ptrBeePlayer->SetTexture(ptrSpriteManager->m_vTextureArray[4]);
					ptrBeePlayer->SetFPS(0);
					ptrBeePlayer->SetCollisionType(COLLISION_RECT);

				}
				if (glfwGetMouseButton(myWindow, GLFW_MOUSE_BUTTON_MIDDLE))
				{
					ptrBeePlayer->SetTexture(ptrSpriteManager->m_vTextureArray[0], 1, 1);
					ptrBeePlayer->SetFPS(0);
					ptrBeePlayer->SetCollisionType(COLLISION_PIXELS);
				}



#pragma endregion INPUT

				//------------------   UPDATE LOGIC!------------------------------ //////////////////////////////////////////////////
				//Posicion del raton
				glfwGetCursorPos(myWindow, &mouseXpos, &mouseYpos);
				myCursorPos.x = mouseXpos;
				myCursorPos.y = mouseYpos;

				////LOGICA Bee! UPDATE POSITION Y Detectar Limite para eliminar
				ptrBeePlayer->Update(deltaTime);

				ptrBeePlayer->m_bIsMoving ? myAudioSource->SetVelocity(sourceSpeed, sourceSpeed, sourceSpeed) : myAudioSource->SetVelocity(0.f);

				myAudioSource->SetPosition(ptrBeePlayer->GetPosition());



				//Collisions
				//ptrBall->Collides(*ptrBeePlayer) ? ptrBeePlayer->SetColor(1, 0, 0, 1) : ptrBeePlayer->SetColor(1, 1, 1, 1);
				
				ptrBeePlayer->SetColor(1, 1, 1, 1); //Restablecer color por si ha dejado de estar colisionando
				for (Sprite* staticSpritesCollisions : ptrSpriteManager->m_vSpriteArray)
				{
					if (staticSpritesCollisions->Collides(*ptrBeePlayer))
					{
						ptrBeePlayer->SetColor(1, 0, 0, 1);
						staticSpritesCollisions->SetColor(1, 0, 0, 1);
					}
					else
					{
						staticSpritesCollisions->SetColor(1, 1, 1, 1);
					}
				}

				if (deltaTime >= dangerTicks)
				{
					deltaTime -= fixedTick;
					//std::cout << "DANGER TIME LOGIC Loop\n";
					//deltaTime = fixedTick;
				}

				deltaTime = 0;

			}

			//---------------------------------RENDER WINDOW-----------------------------------//////

			std::cout << "RENDER Loop\n";

#pragma region RENDER

			//Borrar el backbuffer
			//lgfx_clearcolorbuffer(1.f, 1.f, 1.f);
			lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

			//Render IMGs////
			//------Render BEE

			ptrBeePlayer->Draw();

			for (Sprite* staticSprites : ptrSpriteManager->m_vSpriteArray)
			{
				staticSprites->Draw();
			}



			lgfx_setcolor(1, 0, 0, 1);
			lgfx_drawrect(myAudioListener->m_Position.x, myAudioListener->m_Position.y, 50.f, 50.f); //Listener

			/*
			//RENDER TEXTOS*****************************************
			lgfx_setblend(BLEND_ALPHA);
			for (int i = 0; i < FontDrawableList.size(); i++)
			{
				if (FontDrawableList[i])
				{

					lgfx_setcolor(FontDrawableList[i]->GetR() / 255, FontDrawableList[i]->GetG() / 255, FontDrawableList[i]->GetB() / 255, 1);
					FontDrawableList[i]->Draw();
				}
			}*/

			lgfx_setcolor(1.f, 1.f, 1.f, 1); //Restablecer a color blanco para que no se ponga la pantalla del ultimo color seteado O.o

#pragma endregion RENDER

			//Cambio de buffers
			glfwSwapBuffers(myWindow);

			//Procesar eventos
			glfwPollEvents();

		}

		//Liberar recursos

#pragma region UNLOAD_TEXTURES
		ptrBeePlayer->m_texture = nullptr;
		delete ptrBeePlayer;
		ptrBeePlayer = nullptr;
		std::cout << "Liberar ptrBee \n";

		ptrBall->m_texture = nullptr;
		delete ptrBall;
		ptrBall = nullptr;

		ptrSpriteManager->UnloadTextures();
		delete ptrSpriteManager;
		ptrSpriteManager = nullptr;
		std::cout << "Liberar ptrSpriteManager  \n";
#pragma endregion UNLOAD_TEXTURES

#pragma region UNLOAD_FONTS
		/*
		//Elimino los obj de palabras (lo que realmente se pinta)
		//std::cout << "Liberar el array de Fuentes Cargadas  \n";
		for (int i = 0; i < FontDrawableList.size(); i++)
		{
			if (FontDrawableList[i])
			{

			delete FontDrawableList[i];
			FontDrawableList.erase(FontDrawableList.begin() + i);
			}
		}
		FontDrawableList = nullptr;
		for (int i = 0; i < ptrFontManager->m_LoadedFontArray.size(); i++)
		{
			delete ptrFontManager->m_LoadedFontArray[i];
			ptrFontManager->m_LoadedFontArray.erase(ptrFontManager->m_LoadedFontArray.begin() + i);
		}
		//std::cout << "Liberar ptr FontManager  \n";
		//delete ptrFontManager;
		//ptrFontManager = nullptr;
		//std::cout << "Liberado HelloWorld  \n";
		//delete text_HelloWorld;
		//text_HelloWorld = nullptr;*/
#pragma endregion UNLOAD_FONTS

		//Libero recursos de OpenAL

#pragma region UNLOAD_AUDIO

		delete myAudioSource;
		myAudioSource = nullptr;
		myAudioBuffer = nullptr; //El delete de AudioBuffer se hace en el destructor del AudioSource (No es del todo buena idea por si varios AudioSources utilizasen el mismo buffer)
		delete myAudioListener;
		myAudioListener = nullptr;

#pragma endregion UNLOAD_AUDIO

		ALCcontext* currentContext = alcGetCurrentContext();
		myDevice = alcGetContextsDevice(currentContext);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(currentContext);
		alcCloseDevice(myDevice);



		std::cout << "Terminar GLFW \n";
		glfwTerminate();

	}
	else
	{
		printf("FALLO AL INICIALIZAR GLFW lib");
		//glfwTerminate(); No libero recursos puesto que no se ha llegado a inicializar la libreria
		return 0;
	}

	std::cout << "Todo liberado, Procedo a cerrar la App \n";
	//Liberar recursos
	//glfwTerminate(); // Ya liberada antes de cerrar la app

	return 0;
}

void CallbackUpdateSpriteMouse(Sprite& _sprite, float _fDeltaTime)
{
	float updatedPosX = myCursorPos.x - _sprite.GetSize().x *0.25f;
	float updatedPosY = myCursorPos.y + _sprite.GetSize().y *0.25f;
	MyVec2D updatedPos = (myCursorPos.x - _sprite.GetSize().x*0.5f, myCursorPos.y - _sprite.GetSize().y*0.5f);
	_sprite.SetPosition(myCursorPos);
	//_sprite.SetPosition(updatedPosX, updatedPosY);
}

void CallbackUpdateSprite(Sprite& _sprite, float _fDeltaTime)
{
	//Way to Transform object follow this rule: Scale -> Rotate -> Traslate

		//Scale Update
	_sprite.SetScale(_sprite.GetScale());

	//Rotation Update
	MyVec2D dir = (myCursorPos - _sprite.GetPosition());

	dir.Magnitude() >= fToleranceMovement ? _sprite.m_bIsMoving = true : _sprite.m_bIsMoving = false;


	std::cout << dir.x << " X VALUEEEE\n";
	float newRotation = 0.f;
	bool bRightRotation = false;
	if (_sprite.m_bIsMoving)
	{
		if (dir.x > fToleranceMovement)
		{
			bRightRotation = true;
		}
		else if (dir.x < (-fToleranceMovement))
		{
			bRightRotation = false;
		}
	}
	else
	{
		if (_sprite.GetRotation() > 1.f)
		{
			bRightRotation = true;
		}
		else if (_sprite.GetRotation() < -1.f)
		{
			bRightRotation = false;
		}
	}

	!bRightRotation ? _sprite.SetSpeedRotation(std::abs(_sprite.GetSpeedRotation())) : _sprite.SetSpeedRotation(std::abs(_sprite.GetSpeedRotation()) * (-1));

	newRotation = _sprite.GetRotation() + (_sprite.GetSpeedRotation() * _fDeltaTime);

	std::cout << _sprite.GetRotation() << " bool VALUEEEE\n\n";

	//Block Limits and Return to Angle 0;
	if (_sprite.m_bIsMoving)
	{
		if (bRightRotation && _sprite.GetRotation() <= (-_sprite.GetAngleRotationMax()))//Right limit
		{
			newRotation = (-_sprite.GetAngleRotationMax());
		}
		else if (!bRightRotation && _sprite.GetRotation() >= (_sprite.GetAngleRotationMax()))//Left limit
		{
			newRotation = (_sprite.GetAngleRotationMax());
		}

	}
	else
	{
		if (_sprite.GetRotation() <= 1.f && _sprite.GetRotation() >= -1.f)
		{
			newRotation = 0;
		}
	}

	_sprite.SetRotation(newRotation);

	//Position Update
	MyVec2D currentPos(_sprite.GetPosition());
	dir.Normalize();
	MyVec2D newPos = currentPos + (dir * _sprite.GetSpeedMovement() * _fDeltaTime);

	if (_sprite.m_bIsMoving)
	{
		_sprite.SetPosition(newPos);

	}

	//std::cout << "CallbackUpdateSprite \n";
}
