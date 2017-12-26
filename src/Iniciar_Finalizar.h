#pragma once

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLMain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_mixer.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "c2d2.lib")
#pragma comment(lib, "ca2.lib")

#define LARG_JACK 182
#define ALT_JACK 260

#define LARG_TRUNK 65
#define ALT_TRUNK 65

#include"Includes.h"

#include "Verificacoes.h"
#include "VideoModeConfig.h"

using namespace std;

bool inicializar(int isWindowed)



{

	if (!C2D2_Inicia(LARGURATELA, ALTURATELA, isWindowed, C2D2_DESENHO_OPENGL, "The Rolling"))
		return false;
	
	bool test = false;

	if (!CA2_Inicia()) { printf("Falha ao iniciar o som."); }
	if (CA2_Inicia() == true) { printf("Som iniciado com sucesso!"); }

	in_menu = true;

	return true;
}

void finalizar()
{
	C2D2_Encerra();
}