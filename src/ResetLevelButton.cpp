#include "ResetLevelButton.h"

ResetLevelButton::ResetLevelButton()
{
	m_w = 75;
	m_h = 75;
	m_frame = 0;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_lixeira2.png", m_w, m_h);
}

ResetLevelButton::ResetLevelButton(float p_x, float p_y)
{
	m_x = p_x;
	m_y = p_y;
	m_w = 75;
	m_h = 75;
	m_frame = 0;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_lixeira2.png", m_w, m_h);
}


ResetLevelButton::~ResetLevelButton()
{
}

void ResetLevelButton::Draw()
{
	C2D2_DesenhaSprite(m_sprite, m_frame, m_x, m_y);
}

void ResetLevelButton::Run()
{
	Draw();
}

void ResetLevelButton::SetFrame(int p_frame)
{
	m_frame = p_frame;
}

void ResetLevelButton::SetX(float p_x)
{
	m_x = p_x;
}

void ResetLevelButton::SetY(float p_y)
{
	m_y = p_y;
}

int ResetLevelButton::GetFrame()
{
	return m_frame;
}

int ResetLevelButton::GetX()
{
	return m_x;
}

int ResetLevelButton::GetY()
{
	return m_y;
}

int ResetLevelButton::GetW()
{
	return m_w;
}

int ResetLevelButton::GetH()
{
	return m_h;
}
