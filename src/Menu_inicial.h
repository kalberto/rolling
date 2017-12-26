#pragma once
#include"Includes.h"

#include "Menu_niveis.h"
#include "MenuFasesEditor.h"
#include "MyMouse.h"
#include "ConfigsButton.h"



using namespace std;

class Menu_inicial
{
private:
	//Menu Imagens
	int m_x;
	int m_y;
	int m_sprite_bg;
	int m_sprite_mask;

	int m_sprite_gears;
	int m_frame_gears;

	// Intro Imagem e Timers
	int m_sprite_intro;
	int m_sprite_blackmask;
	float m_blackmask_alpha;
	int m_timer_intro;

	// Musicas
	int m_musica;

	// Menu Ponteiro (Circulo)
	int m_sprite_ponteiro;
	int m_frame_ponteiro;
	int m_x_ponteiro;
	int m_y_ponteiro;
	// Botão Start
	int m_sprite_start;
	int m_x_start;
	int m_y_start;
	int m_frame_start;
	//Botão Exit
	int m_sprite_exit;
	int m_x_exit;
	int m_y_exit;
	int	m_frame_exit;
	// Botão Configs
	ConfigsButton* ConfigButton;
	//auxiliares
	int m_frameCount;
	int m_frame_atual;

public:
	
	int game_estate; // 0 - menu inicial | 1 - Menu de niveis | 2 - Nivel um 

	MyMouse* Mymouse;
	C2D2_Botao* MyKeyborad;
	Menu_niveis* obj_menu_niveis;
	MenuFasesEditor* levelEditor;
	void Run();

	void Draw();
	void Animacoes();
	void Update();

	Menu_inicial();
	~Menu_inicial();



};

