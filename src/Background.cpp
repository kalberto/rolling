#include "Background.h"

Background::Background(string p_sprite)
{
	m_x = 0;
	m_y = 0;
	m_w = 5120;
	m_h = 1766;

	if (p_sprite == "fase1")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/background_f1_3.png", m_w, m_h);
	}
}

Background::Background()
{

}

Background::~Background()
{

}

void Background::Run()
{
	Update();
	Draw();
}

void Background::Draw()
{
	C2D2_DesenhaSprite(m_sprite, 0, m_x, m_y);
}

void Background::Update()
{

}

int Background::getW()
{
	return m_w;
}

int Background::getH()
{
	return m_h;
}

int Background::getX()
{
	return m_x;
}

int Background::getY()
{
	return m_y;
}

void Background::setX(int p_x)
{
	m_x = p_x;
}

void Background::setY(int p_y)
{
	m_y = p_y;
}