#include "ConfigsButton.h"


ConfigsButton::ConfigsButton()
{
	m_frame = 0;
	m_w = 120;
	m_h = 55;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/leveleditor_button.png", m_w, m_h);
}

ConfigsButton::ConfigsButton(float p_x, float p_y)
{
	m_frame = 0;
	m_x = p_x;
	m_y = p_y;
	m_w = 120;
	m_h = 55;
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/leveleditor_button.png", m_w, m_h);
}


ConfigsButton::~ConfigsButton()
{
}

void ConfigsButton::Draw()
{
	C2D2_DesenhaSprite(m_sprite, m_frame, m_x, m_y);
}

void ConfigsButton::Run()
{
	Draw();
}

void ConfigsButton::SetFrame(int p_frame)
{
	m_frame = p_frame;
}

void ConfigsButton::SetX(float p_x)
{
	m_x = p_x;
}

void ConfigsButton::SetY(float p_y)
{
	m_y = p_y;
}

int ConfigsButton::getFrame()
{
	return m_frame;
}

float ConfigsButton::GetX()
{
	return m_x;
}

float ConfigsButton::GetY()
{
	return m_y;
}

int ConfigsButton::GetW()
{
	return m_w;
}

int ConfigsButton::GetH()
{
	return m_h;
}