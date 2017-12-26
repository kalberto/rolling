#pragma once
#include"Array.h"
#include"DlinkedList.h"
#include"Item.h"
#include"Hud.h"
#include"Bola.h"
#include "MyMouse.h"
#include "Fisica.h"
#include "Bola.h"
#include "Save.h"
#include"ResetLevelButton.h"
#include "Camera.h"

#include "EndLevel.h"
#include"PlayStop.h"

using namespace std;

class Fase
{
private:
	
	int m_UpMask;
	int m_DownMask;

	int m_level;
	

	C2D2_Botao* MyKeyborad;
	MyMouse* Mymouse;
	Save* SaveGame;
	DLinkedList<Item*>* partesFase; // partes de contrução da fase
	DListIterator<Item*> iterator_partesFase;
	DLinkedList<Item*>* itensFase; // itens colocados para passar pela fase
	DListIterator<Item*> iterator_ItensFase;
	Array<Item*>* itensHud;	// itens que podem ser escolhidos para colocar na fase
	Hud* hudFase;	// Item que desenhará e controlará o scroll dos itensHud
	Bola* m_bola;
	Fisica m_fisica;
	ResetLevelButton* resetButton;

	Background* m_bg;
	Camera* myCamera;
	PlayStop* myPlayStop;

	EndLevel* endLevel;
	

public:
	bool m_back; // voltar pro menu de niveis

	Fase(int p_level);
	~Fase();

	void Inicializa();

	void Run();

	void Update();

	void Draw();

	void AddItensFase(Item item_solto);

	void AddPartesFase(Item item_solto);

	void SoltarItem(Item* itemdraging);

};

