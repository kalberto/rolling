#include"Hud.h"

Hud::Hud()
{

}

Hud::Hud(Array<Item*>* p_itens_hud)
{
	spriteHud = C2D2_CarregaSpriteSet("Mundo/Imagens/hud2.png", 1365, 134);
	//spriteSetaDireita = C2D2_CarregaSpriteSet("setaDireita.png", 40, 40);
	//spriteSetaEsquerda = C2D2_CarregaSpriteSet("setaEsquerda.png", 40, 40);
	xHud = 0;
	yHud = 0;
	xSetaDireita = 0;
	ySetaDireita = 100;
	xSetaEsquerda = 200;
	ySetaEsquerda = 100;
	indiceHud = 0;
	indiceSetaDireita = 0;
	indiceSetaEsquerda = 0;
	Hud_Itens = p_itens_hud;
}

Hud::~Hud()
{

}

void Hud::MoverDireita()
{

}

void Hud::MoverEsquerda()
{

}

void Hud::SetArrayItens(Array<Item*>* p_array)
{
	Hud_Itens = p_array;
}

void Hud::Draw()
{
	C2D2_DesenhaSprite(spriteHud, indiceHud, xHud, yHud);
	for (int i = 0; i < 10; i++)
	{
		Hud_Itens->m_array[i]->Draw(); //desenha cada item do array de itensHud
	}
}