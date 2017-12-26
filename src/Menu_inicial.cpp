#include "Menu_inicial.h"

#include "Animator.h"
Menu_inicial::Menu_inicial()
{
	MyKeyborad = C2D2_PegaTeclas();
	Mymouse = new MyMouse;
	ConfigButton = new ConfigsButton(1200,680);
	m_frame_atual = 0;
	m_frameCount = 1;
	game_estate = 0;  // 0 - menu inicial | 1 - Menu de niveis | 2 - Nivel um 

	m_x = 0;
	m_y = 0;

	m_x_ponteiro = 400;
	m_y_ponteiro = 400;
	m_frame_ponteiro = 0;

	m_x_start = 551;
	m_y_start = 350;
	m_frame_start = 0;

	m_x_exit = 551;
	m_y_exit = 550;
	m_frame_exit = 0;


	 m_sprite_mask = C2D2_CarregaSpriteSet("Mundo/Imagens/mask.png", 1366, 768);
	 m_sprite_bg = C2D2_CarregaSpriteSet("Mundo/Imagens/bg_rollin3.png", 1366, 768);
	 m_sprite_start = C2D2_CarregaSpriteSet("Mundo/Imagens/start_sprite2.png", 287, 100);
	 m_sprite_exit = C2D2_CarregaSpriteSet("Mundo/Imagens/exit_sprite2.png", 287, 100);

	 m_sprite_gears = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_gears.png", 167, 124);

	 m_sprite_intro = C2D2_CarregaSpriteSet("Mundo/Imagens/OmicronGames.png", 1366, 768);
	 m_sprite_blackmask = C2D2_CarregaSpriteSet("Mundo/Imagens/BlackMask.png", 1366, 768);
	 m_blackmask_alpha = 255;
	 

	 m_musica = CA2_CarregaMusica("Mundo/Musicas/musica1.mp3");
	// CA2_TocaMusica(m_musica, 1);
}

void Menu_inicial::Draw()
{
	
	C2D2_DesenhaSprite(m_sprite_bg, 0, m_x, m_y);
//	C2D2_DesenhaSprite(m_sprite_mask, 0, m_x, m_y);
	
	//botoes
	C2D2_DesenhaSprite(m_sprite_start, m_frame_start, m_x_start, m_y_start);
	C2D2_DesenhaSprite(m_sprite_exit, m_frame_exit, m_x_exit, m_y_exit);

	ConfigButton->Draw();

	//anins
	C2D2_DesenhaSprite(m_sprite_gears, m_frame_gears, 160, 260);


	if (m_timer_intro < 360)
	{
		C2D2_DesenhaSpriteCentroAlfa(m_sprite_intro, 0, 683, 384, 1366, 768, 255, 255, 255, 255);
		C2D2_DesenhaSpriteCentroAlfa(m_sprite_blackmask, 0, 683, 384, 1366, 768, 255, 255, 255, m_blackmask_alpha);
		m_timer_intro++;		
	}

	if (m_timer_intro < 120)
		m_blackmask_alpha -= 2.125;
	

	if (m_timer_intro > 240 && m_timer_intro < 360)
		m_blackmask_alpha += 2.125;

}

void Menu_inicial::Animacoes()
{
	m_frame_start = 0; // Reseta para o frame padrão(Botão sem zoom)
	m_frame_exit = 0; // Reseta para o frame padrão(Botão sem zoom)

	if (Mymouse->MouseIsOverlapping(m_x_start,m_y_start,287,100) == true)
		m_frame_start = 1;	

	if (Mymouse->MouseIsOverlapping(m_x_exit, m_y_exit, 287, 100) == true)
		m_frame_exit = 1;

	if (Mymouse->MouseIsOverlapping(ConfigButton->GetX(), ConfigButton->GetY(), 287, 100) == true)
		ConfigButton->SetFrame(0);
	else
		ConfigButton->SetFrame(1);

}

void Menu_inicial::Update()
{
	
	if (MyKeyborad[C2D2_ESC].pressionado || MyKeyborad[C2D2_ENCERRA].pressionado) // EXIT
	{
		exit(0);
	}

	if (m_frame_exit == 1)
	{
		if (Mymouse->OnAnyClick() == true)
		{
			exit(0);
		}
	}

	if (m_frame_start == 1)
	{
		if (Mymouse->OnAnyClick() == true)
		{
			// ir para menu de fases

			//Carregar Menu
			obj_menu_niveis = new Menu_niveis;
			game_estate = 1;
		}
	}

	if (ConfigButton->getFrame() == 0 && Mymouse->OnAnyClick())// mouse em cima do botão config
	{
		levelEditor = new MenuFasesEditor;
		cout << endl << "Click!";
		game_estate = 2;

	}
	Animador(&m_frameCount, &m_frame_gears, 0.04); // ANIMAÇÃO ENGRENAGENS
}

void Menu_inicial::Run()
{
	if (game_estate == 0)
	{
		

		Update();
		Animacoes();
		Draw();
		Mymouse->Run();
	}
	if (game_estate == 1)
	{
		Mymouse->Run();
		obj_menu_niveis->Run();

		if (obj_menu_niveis->back == true) // funfou
		{
			obj_menu_niveis->back = false;
			game_estate = 0;
		}

	}

	if (game_estate == 2) // level editor
	{
		levelEditor->Run();
		if (levelEditor->back == true) // funfou
		{
			levelEditor->back = false;
			game_estate = 0;
		}
	}
		
	
	
}

Menu_inicial::~Menu_inicial()
{
	delete Mymouse;
	delete MyKeyborad;
	delete obj_menu_niveis;
}
