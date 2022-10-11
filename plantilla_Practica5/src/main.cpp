#define LITE_GFX_IMPLEMENTATION



#include "main.h"

//#include "Font.h"
#include "MyVector2D.h"
#include "Sprite.h"

#include <glfw3.h>
#include <iostream>
#include <vector>



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

float fToleranceMovement = 1.f;




/* VARIABLES PRACTICA 4*/
const char* bee_fileName = "data/bee_anim.png";

void CallbackUpdateSprite(Sprite& _sprite, float _fDeltaTime);

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
		glfwSetWindowTitle(myWindow, "Practica4 FerCalderon");

		//Asociar contexto OpenGL a ventana
		glfwMakeContextCurrent(myWindow);

		lgfx_setup2d(weightWindowScreen, heightWindowScreen);

		//MyVec2D myCursorPos;

		previousTime = glfwGetTime();

		//Carga de ficheros de Fuentes

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
		std::cout << "Creacion ptrSpriteManager\n";

		//Sprite Bee created
		Sprite* ptrBee = new Sprite(ptrSpriteManager->m_vTextureArray[0], 8, 1);
		ptrBee->SetFPS(8);
		ptrBee->SetBlend(BLEND_ALPHA);
		MyVec2D beeInitialPos(weightWindowScreen * 0.5f, heightWindowScreen * 0.5f);
		ptrBee->SetPosition(beeInitialPos);
		ptrBee->SetCallback(&CallbackUpdateSprite);
		std::cout << "Creacion ptrBee\n";

#pragma endregion LOAD_TEXTURES


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

				//Leer Input de usuario
				if (glfwGetKey(myWindow, GLFW_KEY_ESCAPE))
				{
					glfwSetWindowTitle(myWindow, "Cierra");
					glfwSetWindowShouldClose(myWindow, 1);
				}


				//------------------   UPDATE LOGIC!------------------------------ //////////////////////////////////////////////////
				//Posicion del raton
				glfwGetCursorPos(myWindow, &mouseXpos, &mouseYpos);
				myCursorPos.x = mouseXpos;
				myCursorPos.y = mouseYpos;

				////LOGICA Bee! UPDATE POSITION Y Detectar Limite para eliminar
				ptrBee->Update(deltaTime);

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

			//Borrar el backbuffer
			lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

			//Render IMGs////
			//------Render BEE

			ptrBee->Draw();

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


			//Cambio de buffers
			glfwSwapBuffers(myWindow);

			//Procesar eventos
			glfwPollEvents();

		}

		//Liberar recursos

#pragma region UNLOAD_TEXTURES
		ptrBee->m_texture = nullptr;
		delete ptrBee;
		ptrBee = nullptr;
		std::cout << "Liberar ptrBee \n";

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
void CallbackUpdateSprite(Sprite& _sprite, float _fDeltaTime)
{
	//Way to Transform object follow this rule: Scale -> Rotate -> Traslate

		//Scale Update
	_sprite.SetScale(_sprite.GetScale());

	//Rotation Update
	
	//@TODO: CORREGIR ROTATION
	MyVec2D dir = (myCursorPos - _sprite.GetPosition());

	bool bIsMoving = false;
	if (dir.Magnitude() >= fToleranceMovement)
	{
		bIsMoving = true;
	}
	std::cout << dir.x << " X VALUEEEE\n";
	float newRotation = 0.f;
	bool bRightRotation = false;
	if (bIsMoving)
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
		if (_sprite.GetRotation() < 1.f && _sprite.GetRotation() > -1.f)
		{

		}
		if (dir.x <= fToleranceMovement && dir.x >= (-fToleranceMovement))
		{
			bRightRotation = true;
		}
		else if (dir.x < (-fToleranceMovement))
		{
			bRightRotation = false;
		}
	}

	newRotation = _sprite.GetRotation() + (_sprite.GetSpeedRotation() * _fDeltaTime);
	
	if (bIsMoving)
	{
		if (!bRightRotation && newRotation <= (-_sprite.m_fAngleRotationMax)) /*if (newRotation < (-_sprite.GetAngleRotationMax()))*/ //Se entiende Peor
		{
			newRotation = (-_sprite.m_fAngleRotationMax);
		}
		else if (bRightRotation && newRotation >= _sprite.m_fAngleRotationMax)
		{
			newRotation = _sprite.m_fAngleRotationMax;
		}
	}

	_sprite.SetRotation(newRotation);

	//Position Update
	MyVec2D currentPos(_sprite.GetPosition());
	dir.Normalize();
	MyVec2D newPos = currentPos + (dir * _sprite.GetSpeedMovement() * _fDeltaTime);

	if (bIsMoving)
	{
		_sprite.SetPosition(newPos);

	}

	//std::cout << "CallbackUpdateSprite \n";

}
