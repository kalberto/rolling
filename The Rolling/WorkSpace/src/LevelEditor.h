#pragma once
#include"Array.h"
#include"DlinkedList.h"
#include"Item.h"
#include"Hud.h"
#include"Bola.h"
#include "MyMouse.h"
#include "Save.h"
#include "SaveButton.h"

using namespace std;

class LevelEditor
{
private:
	int m_backgroung;
	int m_UpMask;
	int m_DownMask;
	C2D2_Botao* MyKeyborad;
	MyMouse* Mymouse;
	Save* SaveGame;
	DlinkedList<Item*>* partesFase; // partes de contrução da fase
	DListInterator<Item*> interator_partesFase;
	DlinkedList<Item*>* itensFase; // itens colocados para passar pela fase
	DListInterator<Item*> interator_ItensFase;
	Array<Item*>* itensHud;	// itens que podem ser escolhidos para colocar na fase
	Hud* hudFase;	// Item que desenhará e controlará o scroll dos itensHud
	SaveButton* savebutton;


public:
	bool m_back; // voltar pro menu de niveis

	LevelEditor();
	~LevelEditor();

	void Inicializa();

	void Run();

	void Update();

	void Draw();

	void AddItensFase(Item item_solto);

	void AddPartesFase(Item item_solto);

	void SoltarItem(Item* itemdraging);
};

