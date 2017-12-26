#pragma once
#include"Includes.h"

//teste
#include "Item.h"
#include"DlinkedList.h"

using namespace std;

class Save
{
private:
	float x;
	float y;
	string ObjectName;
	bool FoiSobrescrito;

	FILE * fp;
	C2D2_Botao* aux_keyboard;
public:

	Save();
	~Save();

	float GetX();
	float GetY();
	string GetObjectName();

	void Update();
	void Run();
	bool SaveFile();
	bool ReadFile();
	bool ReadIsPassed(int p_level);
	bool SaveIsPassed(int p_level);
	bool ReadObject(DlinkedList<Item*>* p_list);
	bool isFile(string p_FileName);
	bool PutEOF(string p_FileName); // '.' == EOF
	bool SaveObject(string p_ItemName,float p_X,float p_Y);
	void OverwriteFile();
};

