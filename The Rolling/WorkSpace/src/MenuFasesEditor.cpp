#include "MenuFasesEditor.h"
#define VEL_MOV 450
#define Y_SPRITE 400


MenuFasesEditor::MenuFasesEditor()
{
	Mymouse = new MyMouse;
	teclas = C2D2_PegaTeclas();
	back = 0;
	m_timer_delayClick = 0;

	//Set nivel 1
	m_InLevel = false;
	m_nivel = 1;

	// Setagem dos x dos sprites dos niveis
	m_x_f1 = 508;
	m_x_f2 = 508 + (1 * VEL_MOV);
	m_x_f3 = 508 + (2 * VEL_MOV);
	m_x_f4 = 508 + (3 * VEL_MOV);
	m_x_f5 = 508 + (4 * VEL_MOV);

	//BG
	m_sprite_bg = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_bg.png", 1366, 768);
	m_sprite_mask = C2D2_CarregaSpriteSet("Mundo/Imagens/mask.png", 1366, 768);

	//Níveis
	m_sprite_f1 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f1.png", 300, 150);
	m_sprite_f2 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f2.png", 300, 150);
	m_sprite_f3 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f3.png", 300, 150);
	m_sprite_f4 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f4.png", 300, 150);
	m_sprite_f5 = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_f5.png", 300, 150);

	//Botões
	m_sprite_back = C2D2_CarregaSpriteSet("Mundo/Imagens/back.png", 135, 47);


	cout << endl << "Construtor Menu Niveis!";

}

void MenuFasesEditor::mover_niveis()
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

void MenuFasesEditor::desenhar()
{
	C2D2_DesenhaSprite(m_sprite_bg, 0, 0, 0);
	C2D2_DesenhaSprite(m_sprite_mask, 0, 0, 0);

	C2D2_DesenhaSprite(m_sprite_f1, 0, m_x_f1, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f2, 0, m_x_f2, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f3, 0, m_x_f3, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f4, 0, m_x_f4, Y_SPRITE);
	C2D2_DesenhaSprite(m_sprite_f5, 0, m_x_f5, Y_SPRITE);

	//botoes
	C2D2_DesenhaSprite(m_sprite_back, 0, 100, 650);
}

void MenuFasesEditor::Run()
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

int MenuFasesEditor::GetBack()
{
	return back;
}

void MenuFasesEditor::animacoes()
{
	if (Mymouse->MouseIsOverlapping(85, 625, 135, 47) == true)
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

void MenuFasesEditor::Update()
{
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

	if (Mymouse->ObjectIsClicked(m_x_f1, Y_SPRITE, 300, 150) == true && m_nivel == 1 && m_timer_delayClick >= 15 && m_InLevel == false)
	{
		//go to level 1
		m_InLevel = true;
		fase = new LevelEditor;
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
MenuFasesEditor::~MenuFasesEditor()
{
	delete fase;
	delete Mymouse;
	delete teclas;
}
