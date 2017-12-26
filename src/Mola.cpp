#include "Mola.h"


Mola::Mola()
{
	m_sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/Mola.png", 60, 300);
}


Mola::~Mola()
{
}

float Mola::RetornaForça()
{
	float força = 0;
	força = m_distancia*m_coeficiente;
	return força;
}
float Mola::getAngulo()
{
	return m_angulo;
}
void Mola::AddDitancia(float p_distancia)
{
	m_distancia += p_distancia;
}
void Mola::MudarCoeficiente(float p_coeficiente)
{
	m_coeficiente = p_coeficiente;
}
void Mola::MudarPosX(float p_x)
{
	m_PosX = p_x;
}
void Mola::MudarPoxY(float p_y)
{
	m_PosY = p_y;
}
void Mola::MudarPosXY(float p_x, float p_y)
{
	m_PosX = p_x;
	m_PosY = p_y;
}