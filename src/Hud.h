#pragma once
#include"Item.h"
#include"Array.h"

class Hud
{
public:
	unsigned int spriteHud, 
				 spriteSetaDireita, 
				 spriteSetaEsquerda;

	float xHud, yHud,
		xSetaDireita, ySetaDireita,
		xSetaEsquerda, ySetaEsquerda;

	int indiceHud,
		indiceSetaDireita,
		indiceSetaEsquerda;

	Array<Item*>* Hud_Itens;


	Hud();
	Hud(Array<Item*>* p_itens_hud);
	~Hud();
	void MoverDireita();
	void MoverEsquerda();
	void SetArrayItens(Array<Item*>* p_array);
	void Draw();
};