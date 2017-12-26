#pragma once
class Estado_Jogo
{
public:

	int m_Est_j; // 2 - Fase 1 | 3 - Fase 2 |...
	int m_ptr; // 0 - Start | 1 - Exit
	int m_ptr_menu_inicial; // 1 - Fase 1 | 2 - Fase 2 |...
	int m_timer;
	int m_pega_tempo;
	bool m_pause;
	Estado_Jogo();
	~Estado_Jogo();

	void up_menu_inicial();
	void up_menu_niveis();
	void up_fase1();

	void update(); // Update Geral
	
	

private:
};

