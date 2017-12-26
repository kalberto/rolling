#include "Estado_Jogo.h"
#include"Includes.h"

using namespace std;

Estado_Jogo::Estado_Jogo()
{
	m_Est_j = 0;
	m_ptr = 0;
	m_ptr_menu_inicial = 1;
	m_timer = 0;
	m_pega_tempo = 0;
	m_pause = false;
}

void Estado_Jogo::up_menu_inicial()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();


	if (m_Est_j == 0) // Estou no Menu inicial
	{
		if (teclas[C2D2_ENTER].pressionado && m_ptr == 0) // START
		{
			cout << "Start!";
			m_Est_j = 1;
			m_pega_tempo = m_timer;
			cout << endl << "TEMPO: " << m_pega_tempo;
		}

		if (teclas[C2D2_BAIXO].pressionado && m_ptr == 0) // START
		{
			m_ptr = 1;

		}

		if (teclas[C2D2_CIMA].pressionado && m_ptr == 1) // START
		{
			m_ptr = 0;

		}

	}
}

void Estado_Jogo::up_menu_niveis()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();

	if (m_Est_j == 1 && m_timer >= (m_pega_tempo + 10)) // Estou no menu de fases
	{
		if (teclas[C2D2_ESC].pressionado) // Retorna ao menu inicial
		{
			m_Est_j = 0;
		}

		if (teclas[C2D2_DIREITA].pressionado && m_ptr_menu_inicial <= 4 && m_ptr_menu_inicial >= 1) // Definir escolha de fase
		{
			m_ptr_menu_inicial++;
			cout << endl << m_ptr_menu_inicial;
		}

		if (teclas[C2D2_ESQUERDA].pressionado && m_ptr_menu_inicial >= 2 && m_ptr_menu_inicial <= 5) // Definir escolha de fase
		{
			m_ptr_menu_inicial--;
			cout << endl << m_ptr_menu_inicial;
		}

		if (teclas[C2D2_ENTER].pressionado && m_ptr_menu_inicial == 1) // Fase 1
		{
			cout << endl << "Fase 1!";
			m_Est_j = 2;
		}
		if (teclas[C2D2_ENTER].pressionado && m_ptr_menu_inicial == 2) // Fase 1
		{
			cout << endl << "Fase 2!";
			m_Est_j = 3;
		}
		if (teclas[C2D2_ENTER].pressionado && m_ptr_menu_inicial == 3) // Fase 1
		{
			cout << endl << "Fase 3!";
			m_Est_j = 4;
		}
		if (teclas[C2D2_ENTER].pressionado && m_ptr_menu_inicial == 4) // Fase 1
		{
			cout << endl << "Fase 4!";
			m_Est_j = 5;
		}
		if (teclas[C2D2_ENTER].pressionado && m_ptr_menu_inicial == 5) // Fase 1
		{
			cout << endl << "Fase 5!";
			m_Est_j = 6;
		}
	}
}

void Estado_Jogo::up_fase1()
{
	C2D2_Botao* teclas = C2D2_PegaTeclas();
	if (m_Est_j == 2)
	{
		if (teclas[C2D2_ESC].pressionado)
		{
			m_Est_j = 1; // TEMPORARIAMENTE - ARRUMAR PARA PAUSE!!!!!!
		}
	}
} // ARRUMAR PARA PAUSE !!!!!!!

void Estado_Jogo::update()
{
	up_menu_inicial();
	up_menu_niveis();	
	up_fase1();
	m_timer++;
}

Estado_Jogo::~Estado_Jogo()
{
}


