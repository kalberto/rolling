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
	float angulo;
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
	bool ReadIsCompleted(int p_level);
	bool SaveIsCompleted(int p_level);
	bool ReadObject(DLinkedList<Item*>* p_list);
	bool ReadObject2(DLinkedList<Item*>* p_list, int p_level);
	bool isFile(string p_FileName);
	bool PutEOF(int p_level); // '.' == EOF
	bool SaveObject(string p_ItemName,float p_X,float p_Y);
	bool SaveObject2(string p_ItemName, float p_X, float p_Y, float p_angulo, int p_level);
	void CleanFile(int p_level);
	void OverwriteFile();
};

