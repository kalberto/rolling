#pragma once
#include"Array.h"
#include"DlinkedList.h"
#include"Item.h"
#include"Hud.h"
#include"Bola.h"
#include "MyMouse.h"
#include "Save.h"
#include "SaveButton.h"
#include "ResetLevelButton.h"
#include"ResetLevelButton.h"
#include "Camera.h"
#include "Fisica.h"

using namespace std;

class LevelEditor
{
private:

	int m_level;

	C2D2_Botao* MyKeyborad;
	MyMouse* Mymouse;
	Save* SaveGame;
	DLinkedList<Item*>* partesFase; // partes de contrução da fase
	DListIterator<Item*> interator_partesFase;
	DLinkedList<Item*>* itensFase; // itens colocados para passar pela fase
	DListIterator<Item*> interator_ItensFase;
	Array<Item*>* itensHud;	// itens que podem ser escolhidos para colocar na fase
	Hud* hudFase;	// Item que desenhará e controlará o scroll dos itensHud

	Fisica m_fisica;
	Bola* m_bola;
	bool isBola; // False when i do new in the bola set to the true ok muderfucker
	bool isPrintBola;

	// ### BOTOES ###
	SaveButton* saveButton;
	ResetLevelButton* resetButton;

	unsigned int sprite_pressf1;
	int x_pressf1;
	int y_pressf1;

	Background* m_bg;
	Camera* myCamera;


public:
	bool m_back; // voltar pro menu de niveis


	bool mouseButtonDown;
	bool bolaFoiClicada;

	LevelEditor(int p_level);
	~LevelEditor();

	void Inicializa();

	void Run();

	void Update();

	void Draw();

	void AddItensFase(Item item_solto);

	void AddPartesFase(Item item_solto);

	void SoltarItem(Item* itemdraging);
};

