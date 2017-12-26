#include "SaveButton.h"


SaveButton::SaveButton()
{
	m_w = 234;
	m_h = 46;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_botao_salvar_2.png", m_w, m_h);
}

SaveButton::SaveButton(float p_x, float p_y)
{
	m_x = p_x;
	m_y = p_y;
	m_w = 234;
	m_h = 46;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_botao_salvar_2.png", m_w, m_h);
}


SaveButton::~SaveButton()
{
}

void SaveButton::Draw()
{
	C2D2_DesenhaSprite(m_sprite, 0, m_x, m_y);
}

void SaveButton::Run()
{
	Draw();
}

void SaveButton::SetX(float p_x)
{
	m_x = p_x;
}

void SaveButton::SetY(float p_y)
{
	m_y = p_y;
}

float SaveButton::GetX()
{
	return m_x;
}

float SaveButton::GetY()
{
	return m_y;
}

int SaveButton::GetW()
{
	return m_w;
}

int SaveButton::GetH()
{
	return m_h;
}
