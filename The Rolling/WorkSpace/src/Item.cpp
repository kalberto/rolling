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
	m_indice = 0;
	m_isDraging = false;
	
	//sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/mola.png", 323, 299);

	if (m_nome == "mola")
	{
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/mola2.png", 98, 99);
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
		m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/plataforma.png", 302, 16);
		m_angulo = 0;
		m_atrito = 0.1;
	}
	

}

void Item::Update()
{
	//if (x % TAMANHOGRID > TAMANHOGRID / 2)
	//	x = ((x / TAMANHOGRID) * TAMANHOGRID) + TAMANHOGRID;
	//else
	//{
		m_x = (m_x / TAMANHOGRID) * TAMANHOGRID;
	//}
	//if (y % TAMANHOGRID > TAMANHOGRID / 2)
	//	y = ((y / TAMANHOGRID) * TAMANHOGRID) + TAMANHOGRID;
	//else
	//{
		m_y = (m_y / TAMANHOGRID) * TAMANHOGRID;
	//}

}

void Item::Draw()
{
	C2D2_DesenhaSprite(m_sprite, m_indice, m_x, m_y);
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
