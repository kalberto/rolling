#pragma once
#include"Includes.h"

#include "LevelEditor.h"

class MenuFasesEditor
{
private:

	LevelEditor* fase;
	bool m_InLevel;

	MyMouse* Mymouse;
	C2D2_Botao* teclas;

	int m_nivel;

	int m_sprite_mask;
	int m_sprite_bg;
	int m_sprite_f1;
	int m_sprite_f2;
	int m_sprite_f3;
	int m_sprite_f4;
	int m_sprite_f5;

	int m_y_niveis;

	int m_x_f1;
	int m_x_f2;
	int m_x_f3;
	int m_x_f4;
	int m_x_f5;

	// Botoes
	int m_sprite_back;
	int m_frame_back; // 0 desligado (sem zoom), 1 ligado(com zoom)

	//cursor/ponteiro
	int m_sprite_ponteiro;
	// timers
	int m_timer_delayClick;



public:
	//

	bool back; // para voltar ao menu inicial

	MenuFasesEditor();
	~MenuFasesEditor();

	void desenhar();
	void mover_niveis();
	void Run();
	void animacoes();
	void Update();

	int GetBack();


};

