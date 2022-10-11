#pragma once

class FILE;

class FileManager
{
	FILE* m_FontFile = nullptr; //Gestion Apertura, Lectura y Cierre de Archivos .ttf
	

	int OpenFile(const char* _ccFileName, const char* _ccOpenMode);

	void CloseFile();

};