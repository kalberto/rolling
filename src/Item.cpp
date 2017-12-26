#include "Item.h"
Item::Item(string p_nome)
{
	m_nome = p_nome;
	
}

Item::Item(string p_nome, float p_x, float p_y)
{
	m_nome= p_nome;
	m_x = p_x;
	m_xInicio = p_x;
	m_y = p_y;
	m_yInicio = p_y;
	m_xDraw = p_x;
	m_yDraw = p_y;

	m_indice = 0;
	m_isDraging = false;
	
	

	if (m_nome == "mola")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/Mola.png", 60, 30);
		m_angulo = 0;
		m_atrito = 0.1;
	}
	else if (m_nome == "gangorra")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/gangorra2.png", 122, 122);
		m_angulo = 0;
		m_atrito = 0.1;
	}
	else if (m_nome == "plataforma")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_plataforma.png", 150, 150);
		m_angulo = 0;
		m_atrito = 0.1;
		m_indice = 0;
	}
	

}

Item::Item(string p_nome, float p_x, float p_y, float p_angulo, int p_indice)
{
	m_nome = p_nome;
	m_x = p_x;
	m_xInicio = p_x;
	m_y = p_y;
	m_yInicio = p_y;
	m_xDraw = p_x;
	m_yDraw = p_y;
	m_indice = p_indice;
	m_angulo = p_angulo;
	m_isDraging = false;
	

	if (m_nome == "mola")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/Mola.png", 60, 30);
		m_atrito = 0.1;
	}
	else if (m_nome == "gangorra")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/gangorra2.png", 122, 122);
		m_atrito = 0.1;
	}
	else if (m_nome == "plataforma")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_plataforma.png", 150, 150);
		m_atrito = 0.1;

		if (m_angulo == 180)
			m_indice = 0;

		if (m_angulo == 45)
			m_indice = 1;

		if (m_angulo == 90)
			m_indice = 2;

		if (m_angulo == 135)
			m_indice = 3;
	}
}

void Item::Update()
{

		m_x = (m_x / TAMANHOGRID) * TAMANHOGRID;

		m_y = (m_y / TAMANHOGRID) * TAMANHOGRID;


}

void Item::Draw()
{
	C2D2_DesenhaSprite(m_sprite, m_indice, m_x, m_y);
}

void Item::Draw(int p_x, int p_y)
{
	C2D2_DesenhaSprite(m_sprite, m_indice, m_x - p_x, m_y - p_y);
	m_xDraw = m_x - p_x;
	m_yDraw = m_y - p_y;
}

void Item::rotPlat()
{
	if (getAngulo() == 135 )
	{
		setAngulo(0);
		setIndice(0);
		return;
	}

	setAngulo((getAngulo() + 45));
	setIndice((getIndice() + 1));	
}

void Item::ReturnPosition()
{
	m_x = m_xInicio;
	m_y = m_yInicio;
}

void Item::Drop()
{
	m_xInicio = m_x;
	m_yInicio = m_y;


}


string Item::getName()
{
	return m_nome;
}

int Item::getX()
{
	return m_x;
}

int Item::getY()
{
	return m_y;
}

int Item::getXinicio()
{
	return m_xInicio;
}

int Item::getYinicio()
{
	return m_yInicio;
}

float Item::getAngulo()
{
	return m_angulo;
}

float Item::getAtrito()
{
	return m_atrito;
}

int Item::getIndice()
{
	return m_indice;
}

unsigned int Item::getSprite()
{
	return m_sprite;
}


void Item::setName(string p_name)
{
	m_nome = p_name;
}

void Item::setX(int p_x)
{
	m_x = p_x;
}

void Item::setY(int p_y)
{
	m_y = p_y;
}

void Item::setAngulo(float p_angulo)
{
	m_angulo = p_angulo;
}

void Item::setAtrito(float p_atrito)
{
	m_atrito = p_atrito;
}
void Item::setIndice(int p_indice)
{
	m_indice = p_indice;
}
