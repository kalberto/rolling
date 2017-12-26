#pragma once
#include"Includes.h"

#include "Fase.h"

class Menu_niveis
{
private:

	Fase* fase;
	bool m_InLevel;

	MyMouse* Mymouse;
	C2D2_Botao* teclas;
	Save* saveGame;

	int m_nivel;

	int m_sprite_mask;
	int m_sprite_bg;
	int m_sprite_f1, m_passed_f1;
	int m_sprite_f2, m_passed_f2;
	int m_sprite_f3, m_passed_f3;
	int m_sprite_f4, m_passed_f4;
	int m_sprite_f5, m_passed_f5;

	int m_y_niveis;

	int m_x_f1, f1IsPassed;
	int m_x_f2, f2IsPassed;
	int m_x_f3, f3IsPassed;
	int m_x_f4, f4IsPassed;
	int m_x_f5, f5IsPassed;

	// Botoes
	int m_sprite_back;
	int m_frame_back; // 0 desligado (botao sem zoom), 1 ligado(botao com zoom)

	//cursor/ponteiro
	int m_sprite_ponteiro;
	// timers
	int m_timer_delayClick;

	
	 
public:
	//
	
	bool back; // para voltar ao menu inicial

	Menu_niveis();
	~Menu_niveis();

	void desenhar();
	void mover_niveis();
	void Run();
	void animacoes();
	void Update();
	void setIsPassed(int p_level,int p_IntBool);
	void ReloadSpriteIsPassed(int* sprite);
	void CheckFinishedLevels();

	int GetBack();


};

