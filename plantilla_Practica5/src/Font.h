#pragma once
#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"
#include "MyVector2D.h"
#include <iostream>
#include <litegfx.h>
#include <vector>

class Font
{
private:
	Font() {}

public:

	Font(ltex_t* _tex, stbtt_bakedchar* _charData, float _size)
		: m_Tex(_tex), m_CharData(_charData),
		m_Weight(_size), m_Height(_size) {}
	~Font()
	{
		//Libero memoria
		//libero ptr y elimino Textura generada de la fuente
		if (m_Tex)
		{
			ltex_free(m_Tex);
			m_Tex = nullptr;
		}
		if (m_CharData)
		{
			//Char data
			delete m_CharData;
			m_CharData = nullptr;
		}

		std::cout << "Destructor de FONT! estaba cargada en memoria \n";
	}

	ltex_t* GetTex() { return m_Tex; }
	stbtt_bakedchar* GetCharData() { return m_CharData; }

	void SetTex(ltex_t* _Tex) { m_Tex = _Tex; }
	void SetCharData(stbtt_bakedchar* _CharData) { m_CharData = _CharData; }


	ltex_t* m_Tex = nullptr;
	stbtt_bakedchar* m_CharData = nullptr;
	float m_Height = 0.f;
	float m_Weight = 0.f;

};


class FontDrawable
{
private:
	/*FontDrawable(MyVec2D _position, MyVec2D(_sizeObject));
	FontDrawable(float posX, float posY, float weight, float height);
	FontDrawable(float posX, float posY, MyVec2D(_sizeObject));
	FontDrawable(MyVec2D _position, float weight, float height);*/

	Font* ptrFont = nullptr;
	const char* textToRender = nullptr;

	float m_R = 0.f;
	float m_G = 0.f;
	float m_B = 0.f;

	float m_Speed = 0;
	MyVec2D m_Pos = (0.f, 0.f);

public:
	float m_sizeTextPixelImg = 0;
	FontDrawable() {}
	FontDrawable(MyVec2D _position);
	FontDrawable(float _positionX, float _positionY);
	~FontDrawable()
	{
		std::cout << "Destructor de objeto FontDrawable! \n";
		/*delete textToRender;
		textToRender = nullptr;*/
	}

	void SetFont(Font* _font) { ptrFont = _font; }

	float GetR() { return m_R; }
	float GetG() { return m_G; }
	float GetB() { return m_B; }

	float GetSpeed() { return m_Speed; }
	MyVec2D GetPos() { return m_Pos; }

	void SetSpeed(float _Speed) { m_Speed = _Speed; }
	void SetPos(MyVec2D _pos) { m_Pos = _pos; }
	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }

	void SetRGB(float _r, float _g, float _b) { m_R = _r;  m_G = _g; m_B = _b; }
	void SetR(float _r) { m_R = _r; }
	void SetG(float _g) { m_G = _g; }
	void SetB(float _b) { m_B = _b; }

	void SetText(const char* _texto) { textToRender = _texto; }

	void Draw() const;
	void UpdatePos(float _deltaTime) { m_Pos.x += (-m_Speed * _deltaTime); }

};


class FontManager
{
private:

public:
	FontManager() {}

	~FontManager()
	{
		UnloadFonts();
		std::cout << "Destructor de objeto FontDrawable! \n";
	}

	std::vector<Font*> m_LoadedFontArray;

	FILE* m_FontFile = nullptr; //Gestion Apertura, Lectura y Cierre de Archivos .ttf


	//static Font* Load(const char* _FileNameToOpen);
	Font* Load(const char* _FileNameToOpen, float _size);

	void UnloadFonts();


	int OpenFontFile(const char* _ccFileName, const char* _ccOpenMode);

	void CloseFile();

};