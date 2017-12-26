#pragma once

#include "Menu_inicial.h"
#include"Includes.h"

using namespace std;

class Jogo
{
public:

	Menu_inicial* obj_menu;
	Jogo();
	~Jogo();

	void Run();

private:
	bool criei_jogo = true;
};

