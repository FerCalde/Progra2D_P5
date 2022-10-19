#pragma once

#include "MyVector2D.h"
#include <iostream>
#include <vector>
#include <litegfx.h>

//class ltext_t;

class Sprite
{
public:
	Sprite(const ltex_t* _tex, int _iHframes = 1, int _iVframes = 1);
	//~Sprite();

	void Update(float _fDeltaTime);
	void Draw() const;


	//type of callback func
	typedef void (*CallbackFunc)(Sprite&, float);
	
	//Set ptr to callback func
	void SetCallback(CallbackFunc _func);
	
	CallbackFunc m_CallbackFunc;


	//Ptr generic of data
	void* GetUserData();
	void SetUserData(void* _data);
	void* m_data = nullptr;

	const ltex_t* m_texture;
	const ltex_t* GetTexture() const;
	void SetTexture(const ltex_t* _tex, int _iHframes = 1, int _iVframes = 1);

	void SetSizeUVAnimFrame();
	MyVec2D m_SizeUVAnimFrame;

	lblend_t m_blendMode;
	lblend_t GetBlend() const;
	void SetBlend(lblend_t _mode);

	float m_fRed = 0;
	float m_fGreen = 0;
	float m_fBlue = 0;
	float m_fAlpha = 0;

	float GetRed() const;
	float GetGreen() const;
	float GetBlue() const;
	float GetAlpha() const;
	void SetColor(float _r, float _g, float _b, float _a);

#pragma region Transform
	MyVec2D m_Position;
	float m_fRotation;
	MyVec2D m_Scale;
	
	MyVec2D m_Pivot;
	
	const MyVec2D& GetPosition() const;
	void SetPosition(const MyVec2D& _pos);
	void SetPosition(float _posX, float _posY);

	float GetRotation() const;
	void SetRotation(float _fAngle);

	const MyVec2D& GetScale() const;
	void SetScale(const MyVec2D& _scale);
	void SetScale(float _weight, float _height);
	
	//Size frame multiply by scale
	MyVec2D m_Size;
	MyVec2D GetSize() const;
	void SetSize(const MyVec2D& _scale);

	//Valor send to ltex_drawrotsized when draw for indicate rotation pivot
	const MyVec2D& GetPivot() const;
	void SetPivot(const MyVec2D& _pivot);
	void SetPivot(float _fPivotX, float _fPivotY);

	const float m_fSpeedMovement = 750.f;
	const float GetSpeedMovement() const;
	float m_fSpeedRotation = 15.f;
	const float GetSpeedRotation() const;
	const void SetSpeedRotation(const float _fSpeedRot);
	const float m_fAngleRotationMax = 15.f;
	const float GetAngleRotationMax() const;

#pragma endregion Transform

	int m_iHframes;
	int m_iVframes;

	int GetHframes() const;
	int GetVframes() const;

	//times per second that change animation frame
	int m_iFPS;
	int GetFPS() const;
	void SetFPS(int _iFPS);
	
	float m_tickPerFPS = 1.0f / m_iFPS;
	float elapsedTickFPS = 0;
	
	//Current animation Frame
	float m_fCurrentFrame;
	float GetCurrentFrame() const;
	void SetCurrentFrame(int _iFrame);

	bool m_bIsMoving = false;

	

};


class SpriteManager
{
	public:
	SpriteManager(){}
	/*~SpriteManager();

	void AddSpriteToList(Sprite* sprite);
	void RemoveSpriteFromList(Sprite* sprite);
	void AddTextureToArray();
	void Update(float deltaTime);
	void Draw();
	*/
	ltex_t* GenerateTexture(const char* _fileName);
	
	void LoadTexture(const char* _fileName);
	void UnloadTextures();

	void CallbackUpdateSprite(Sprite& _sprite, float _fDeltaTime);
	

	std::vector<Sprite*> m_vSpriteArray;
	std::vector<ltex_t*> m_vTextureArray;
};