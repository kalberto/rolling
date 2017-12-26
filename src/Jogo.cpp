#include "Jogo.h"

Jogo::Jogo()
{
	obj_menu = new Menu_inicial;
		
		cout << endl << "Construtor Jogo!";
}

Jogo::~Jogo()
{
	delete obj_menu;
}

void Jogo::Run()
{
	obj_menu->Run();
}

