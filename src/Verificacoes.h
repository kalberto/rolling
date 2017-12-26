#pragma once

#include"Includes.h"

bool quit = false;
bool in_menu = false;
bool in_game = false;

int x_mouse = 683;
int y_mouse = 384;

using namespace std;

void atualizar()
{

	C2D2_Botao* teclas = C2D2_PegaTeclas();
	C2D2_Mouse* mouse = C2D2_PegaMouse();

	if (in_menu == true)
	{
		x_mouse = mouse->x;
		y_mouse = mouse->y;

		if (teclas[C2D2_ESC].pressionado || teclas[C2D2_ENCERRA].pressionado)
		{
			quit = true;
		}

		if (mouse ->botoes[C2D2_MESQUERDO].pressionado && quit == false)
		{
			cout << endl << "Click!";
		}
	}
}