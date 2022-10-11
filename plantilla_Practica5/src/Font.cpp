#include "Font.h"


Font* FontManager::Load(const char* _FileNameToOpen, float _size)
{
	if (OpenFontFile(_FileNameToOpen, "rb")) //Apertura archivo (Evitar errores por no tenerlo abierto/No Existir)
	{
		fseek(m_FontFile, 0, SEEK_END);
		long lSize = ftell(m_FontFile);
		printf("Size of myfile.txt: %ld bytes.\n", lSize);
		rewind(m_FontFile);

		char* buffer = new char[lSize];
		if (buffer == NULL)
		{
			fputs("Memory error", stderr);
			exit(2);
		}

		// copy the file into the buffer:
		size_t resultado = fread(buffer, sizeof(char), lSize, m_FontFile);



		//Renderizar Alpha Buffer

		unsigned char* ptrAuxBuffer = reinterpret_cast<unsigned char*>(buffer);
		int auxSize = 512;
		unsigned char* auxPixels = new unsigned char[auxSize * auxSize];
		stbtt_bakedchar* auxCharData = new stbtt_bakedchar[auxSize * 0.5f];



		if (stbtt_BakeFontBitmap(ptrAuxBuffer, 0, _size, auxPixels, auxSize, auxSize, 0, 256, auxCharData))
		{
			//Crear Color Buffer
			//const long/*int no llega tanto*/ sizeColorBuffer = auxSize * auxSize * 4;
			unsigned char* ptrAuxColorBuffer = new unsigned char[auxSize * auxSize * 4];

			for (int i = 0; i < auxSize * auxSize * 4; i++)
			{
				ptrAuxColorBuffer[i] = 255;
				if ((i % 4 == 0) && (0 < i))
				{
					ptrAuxColorBuffer[i - 1] = auxPixels[i / 4];
				}
			}

			//Crear Textura LiteGFX 
			ltex_t* auxTex = ltex_alloc(auxSize, auxSize, 0);
			ltex_setpixels(auxTex, ptrAuxColorBuffer);

			//Font* auxLoadedFont = new Font(auxTex, auxCharData, _size);
			CloseFile();
			delete buffer;
			buffer = nullptr;
			delete ptrAuxColorBuffer;
			ptrAuxColorBuffer = nullptr;
			delete auxPixels;
			auxPixels = nullptr;
			return new Font(auxTex, auxCharData, _size);
		}

		else
		{

			//Cerrar archivo y Limpiar Buffers
			CloseFile();
			return nullptr;
		}
	}

	return nullptr;
}

void FontManager::UnloadFonts()
{
	for (int i = 0; i < m_LoadedFontArray.size(); i++)
	{
		if (m_LoadedFontArray[i])
		{
			delete m_LoadedFontArray[i];
			m_LoadedFontArray.erase(m_LoadedFontArray.begin() + i);
		}
	}
	std::cout << "Liberado el array de Fuentes Cargadas  \n";
}

int FontManager::OpenFontFile(const char* _ccFileName, const char* _ccOpenMode)
{
	if (m_FontFile == nullptr) //Compruebo puntero esta disponible para almacenar el archivo
	{
		//std::cout << "El puntero esta disponible para almacenar el archivo\n";

		int _err = fopen_s(&m_FontFile, _ccFileName, _ccOpenMode);

		if (_err != 0)
		{
			std::cout << "Error! File cannot be open\n";
			return 0; //Devuelvo 0 para evitar que pueda escribir/leer el archivo
		}
		else
		{
			std::cout << "File is Open!\n";
			return 1; //Devuelvo 1 para poder escribir/leer el archivo
		}
	}
	else
	{
		return 0; //Devuelvo 0 para evitar que pueda escribir/leer el archivo
		std::cout << "YA TIENES UN ARCHIVO ABIERTO!\n";
	}
}

void FontManager::CloseFile()
{
	//Compruebo que el puntero tiene archivos ya asociados (Diferente de nullptr)
	if (m_FontFile)
	{
		//Diferencia con OpenFile, 
		//creo una variable auxiliar para comprobar dentro de la funcion que el archivo se cierra correctamente
		//Posible ser menos eficiente puesto que crea un int (8bits) 
		int _err = fclose(m_FontFile);
		if (_err == 0)
		{
			printf("File is Close!\n");
		}
		else
		{
			printf("ERROR! File Cant be Closed\n");
		}

		//Restablezco el puntero a null para poder asociarlo a otro archivo
		m_FontFile = nullptr;

	}
	else
	{
		std::cout << "EL PUNTERO ESTA NULL!\n";
	}

}

FontDrawable::FontDrawable(MyVec2D _position)
{
	SetPos(_position);
}

FontDrawable::FontDrawable(float _positionX, float _positionY)
{
	SetPos(_positionX, _positionY);
}

void FontDrawable::Draw() const
{
	stbtt_aligned_quad* q = new stbtt_aligned_quad();

	float auxX = m_Pos.x;
	float auxY = m_Pos.y;
	//int sizeText = sizeof(textToRender)/sizeof(textToRender[0]);
	for (int i = 0; i < 15; i++)
	{
		stbtt_GetBakedQuad(ptrFont->GetCharData(), ptrFont->GetTex()->width, ptrFont->GetTex()->height, int(textToRender[i]), &auxX, &auxY, q, true);
		ltex_drawrotsized(ptrFont->GetTex(), auxX, auxY, 0, 1.f, 0.5f, (q->x1 - q->x0), (q->y1 - q->y0), q->s0, q->t0,
			q->s1, q->t1);

	}
	delete q;
	q = nullptr;
}