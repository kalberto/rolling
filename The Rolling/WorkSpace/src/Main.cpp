#include"Includes.h"

#include "Jogo.h"
#include "Iniciar_Finalizar.h"
#include "Verificacoes.h"
#include "Fase.h"
#include "MyMouse.h"
#include "SaveButton.h"
#include "Menu_inicial.h"

// testes
#include "Save.h"
#include "Item.h"
#include "VideoModeConfig.h"



using namespace std;





int main(int argc, char* argv[])
{
	int isWindowed;
	_videoModeSelector:	
		cout << endl << endl << "-------------------- SELECT YOUR VIDEO MODE --------------------";
		cout << endl << "Press <0> to run in Windowed Mode";
		cout << endl << "Press <1> to run in Fullscreen Mode";
		cout << endl << "Enter to Accept!";
		cout << endl;

		cin >> isWindowed;
		if (isWindowed != 0 && isWindowed != 1)
		{
			cout << endl << endl << endl << "-------------------- Warning!--------------------";
			cout << endl << "Incorrect Nunber!";
			cout << endl << "Press <0> or <1> !";
			goto _videoModeSelector;

		}

	if (!inicializar(isWindowed))
	{
		return 1;
	}


	C2D2_Botao* aux_keyboard = C2D2_PegaTeclas();
	Jogo* jogo = new Jogo;
	cout << endl;

	do
	{
		jogo->Run();
		if (aux_keyboard[C2D2_E].pressionado) // Apagar no final do Projeto!
		{
			exit(0);
		}

		C2D2_Sincroniza(C2D2_FPS_PADRAO);
		C2D2_LimpaTela();
	} while (!quit);
	finalizar();
	return 0;
}