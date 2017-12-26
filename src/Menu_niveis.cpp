#define VEL_MOV 450
#define Y_SPRITE 400

#include "Menu_niveis.h"


Menu_niveis::Menu_niveis()
{
	Mymouse = new MyMouse;
	saveGame = new Save;
	teclas = C2D2_PegaTeclas();
	back = 0;
	m_timer_delayClick = 0;

	//Set nivel 1
	m_nivel = 1;

	//Seta os IsPassed para 0 INICIALMENTE para depois checar nos files | 0 = fase não concluida | 1 = fase concluida
	f1IsPassed = 0;
	f2IsPassed = 0;
	f3IsPassed = 0;
	f4IsPassed = 0;
	f5IsPassed = 0;
	//Seta inicialmente os sprites de fase não concluida
	m_passed_f1 = C2D2_CarregaSpriteSet("Mundo/Imagens/naoconcluida.png", 100, 75);
	m_passed_f2 = C2D2_CarregaSpriteSet("Mundo/Imagens/naoconcluida.png", 100, 75);
	m_passed_f3 = C2D2_CarregaSpriteSet("Mundo/Imagens/naoconcluida.png", 100, 75);
	m_passed_f4 = C2D2_CarregaSpriteSet("Mundo/Imagens/naoconcluida.png", 100, 75);
	m_passed_f5 = C2D2_CarregaSpriteSet("Mundo/Imagens/naoconcluida.png", 100, 75);

	// Setagem dos x dos sprites dos niveis
	m_x_f1 = 508;
	m_x_f2 = 508 + (1 * VEL_MOV);
	m_x_f3 = 508 + (2 * VEL_MOV);
	m_x_f4 = 508 + (3 * VEL_MOV);
	m_x_f5 = 508 + (4 * VEL_MOV);

	//BG
	m_sprite_bg = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_bg_2.png", 1366, 768);
	m_sprite_mask = C2D2_CarregaSpriteSet("Mundo/Imagens/mask.png", 1366, 768);

	//Níveis
	m_sprite_f1 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f1_2.png", 300, 150);
	m_sprite_f2 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f2_2.png", 300, 150);
	m_sprite_f3 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f3_2.png", 300, 150);
	m_sprite_f4 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f4_2.png", 300, 150);
	m_sprite_f5 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f5_2.png", 300, 150);

	//Botões
	m_sprite_back = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_back.png", 135, 47);


	cout << endl << "Construtor Menu Niveis!";

	CheckFinishedLevels();

}

void Menu_niveis::mover_niveis()
{
	

	if (teclas[C2D2_ESQUERDA].pressionado && m_x_f1 < 508)
	{
		m_x_f1 += VEL_MOV;
		m_x_f2 += VEL_MOV;
		m_x_f3 += VEL_MOV;
		m_x_f4 += VEL_MOV;
		m_x_f5 += VEL_MOV;

		m_nivel--;
	}

	if (teclas[C2D2_DIREITA].pressionado && m_x_f1 > -1292)
	{
		m_x_f1 -= VEL_MOV;
		m_x_f2 -= VEL_MOV;
		m_x_f3 -= VEL_MOV;
		m_x_f4 -= VEL_MOV;
		m_x_f5 -= VEL_MOV;
		m_nivel++;
	}

	if (teclas[C2D2_ESC].pressionado)
	{
		back = true;
	}

	if (teclas[C2D2_C].pressionado)
	{
		//cout << endl << m_x_f1;
		cout << endl << m_nivel;
	}
}

void Menu_niveis::desenhar()
{
	int XoffsetIsPassed = 180;
	int YoffsetIsPassed = 100;

	C2D2_DesenhaSprite(m_sprite_bg, 0, 0, 0);
	C2D2_DesenhaSprite(m_sprite_mask, 0, 0, 0);

	C2D2_DesenhaSprite(m_sprite_f1, 0, m_x_f1, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f2, 0, m_x_f2, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f3, 0, m_x_f3, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f4, 0, m_x_f4, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f5, 0, m_x_f5, Y_SPRITE);

	C2D2_DesenhaSprite(m_passed_f1, 0, m_x_f1 + XoffsetIsPassed, Y_SPRITE + YoffsetIsPassed);
	C2D2_DesenhaSprite(m_passed_f2, 0, m_x_f2 + XoffsetIsPassed, Y_SPRITE + YoffsetIsPassed);
	C2D2_DesenhaSprite(m_passed_f3, 0, m_x_f3 + XoffsetIsPassed, Y_SPRITE + YoffsetIsPassed);
	C2D2_DesenhaSprite(m_passed_f4, 0, m_x_f4 + XoffsetIsPassed, Y_SPRITE + YoffsetIsPassed);
	C2D2_DesenhaSprite(m_passed_f5, 0, m_x_f5 + XoffsetIsPassed, Y_SPRITE + YoffsetIsPassed);

	//botoes
	C2D2_DesenhaSprite(m_sprite_back, m_frame_back, 100, 650);
}

void Menu_niveis::Run()
{
	if (m_InLevel == false)
	{
		mover_niveis();
		animacoes();
		Update();
		desenhar();
		Mymouse->Run();
	}
	if (m_InLevel == true)
	{
		Update();
		fase->Run();
	}
		

}

int Menu_niveis::GetBack()
{
	return back;
}

void Menu_niveis::animacoes()
{
	m_frame_back = 0;
	if (Mymouse->MouseIsOverlapping(85,625,135,47) == true)
	{
		m_frame_back = 1;
	}

	if (Mymouse->ObjectIsClicked(938, 380, 300, 150) == true && m_nivel <= 4)
	{
			m_x_f1 -= VEL_MOV;
			m_x_f2 -= VEL_MOV;
			m_x_f3 -= VEL_MOV;
			m_x_f4 -= VEL_MOV;
			m_x_f5 -= VEL_MOV;
			m_nivel++;
	}

	if (Mymouse->ObjectIsClicked(42, 380, 300, 150) == true && m_nivel >= 2)
	{
		m_x_f1 += VEL_MOV;
		m_x_f2 += VEL_MOV;
		m_x_f3 += VEL_MOV;
		m_x_f4 += VEL_MOV;
		m_x_f5 += VEL_MOV;
		m_nivel--;
	}
}

void Menu_niveis::Update()
{
	CheckFinishedLevels();

	if (m_frame_back == 1)
	{
		if (Mymouse->OnAnyClick() == true)
		{
			back = true;
		}
	}

	//cout << endl << "X: " << MyMouse->x; // Mostrar pos mouse ### APAGAR DEPOIS ####
	//cout << endl << "Y: " << MyMouse->y;
	//cout << endl;

	if (Mymouse->ObjectIsClicked(508, Y_SPRITE, 300, 150) == true && m_timer_delayClick >= 15 && m_InLevel == false) // 508 || m_x_f1
	{
		//vai pro level passando qual nivel quer abrir
		m_InLevel = true;
		fase = new Fase(m_nivel);
	}

	if (m_InLevel == true)
	{	

		if (fase->m_back == true)
		{
			m_InLevel = false;
		}
	}
	if (m_timer_delayClick < 15)
	{
		m_timer_delayClick++;
	}
}

void Menu_niveis::setIsPassed(int p_level, int p_IntBool)
{
	if (p_level == 1)
	{
		f1IsPassed = p_IntBool;
		ReloadSpriteIsPassed(&m_passed_f1);
	}

	if (p_level == 2)
	{
		f2IsPassed = p_IntBool;
		ReloadSpriteIsPassed(&m_passed_f2);
	}
	if (p_level == 3)
	{
		f3IsPassed = p_IntBool;
		ReloadSpriteIsPassed(&m_passed_f3);
	}
	if (p_level == 4)
	{
		f4IsPassed = p_IntBool;
		ReloadSpriteIsPassed(&m_passed_f4);
	}
	if (p_level == 5)
	{
		f5IsPassed = p_IntBool;
		ReloadSpriteIsPassed(&m_passed_f5);
	}
}

void Menu_niveis::ReloadSpriteIsPassed(int* sprite)
{
	*sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/concluida.png", 100, 75);
}

void Menu_niveis::CheckFinishedLevels()
{
	int count_levels = 5;
	for (int i = 0; i < count_levels; i++)
	{
		if (saveGame->ReadIsCompleted(i + 1) == true)
		{
			setIsPassed(i + 1, 1);
		}
	}
}

Menu_niveis::~Menu_niveis()
{
	delete fase;
	delete Mymouse;
	delete teclas;
	delete saveGame;
}
