#include "EndLevel.h"

EndLevel::EndLevel()
{
	m_x = m_y = 0;
	m_level = 0;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/endlevel_sprite.png", 1366, 768);

	m_flag = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_flag.png", 128, 128);
	m_xFlag = 1000;
	m_yFlag = 500;

	inLevel = false;

}

EndLevel::EndLevel(int p_level,Save* p_save)
{
	m_x = m_y = 0;
	m_level = p_level;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/endlevel_sprite.png", 1366, 768);

	m_flag = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_flag.png", 128, 128);
	m_xFlag = 1000;
	m_yFlag = 430;

	inLevel = true;
	m_save = p_save;
	m_timer = 0;
}

EndLevel::~EndLevel()
{

}

void EndLevel::Run(Camera* p_camera, Bola* p_bola, bool* p_back)
{
	Update(p_bola,p_back);
	Draw(p_camera);
}

void EndLevel::Update(Bola* p_bola,bool* p_back)
{
	if (p_bola->getX() >= m_xFlag && p_bola->getX() <= m_xFlag + 128) // colisão em X
	{
		if (p_bola->getY() >= m_yFlag && p_bola->getY() <= m_yFlag + 128) //colisão em Y
		{
			inLevel = false;
			SaveFinishedLevel();
		}
	}

	if (inLevel == false && m_timer < 180) // m_timer < segs * 60    Duração de exibição da tela
		m_timer++;

	if (m_timer == 180)
	{
		inLevel = true;
		m_timer = 0;
		*p_back = true;
	}
	
}

void EndLevel::Draw(Camera* p_camera)
{
	if (inLevel == true) // se estiver no level printar a flag
	{
		C2D2_DesenhaSprite(m_flag, 0, m_xFlag - p_camera->m_x, m_yFlag - p_camera->m_y);
	}

	if (inLevel == false) // se estiver no level printar a flag
	{
		C2D2_DesenhaSprite(m_sprite, 0, m_x, m_y);
	}
	
}

bool EndLevel::getInLevel()
{
	return inLevel;
}

float EndLevel::getX()
{
	return m_x;
}

float EndLevel::getY()
{
	return m_y;
}

void EndLevel::setX(float p_x)
{
	m_x = p_x;
}

void EndLevel::setY(float p_y)
{
	m_y = p_y;
}

void EndLevel::SaveFinishedLevel()
{
	m_save->SaveIsCompleted(m_level);
}