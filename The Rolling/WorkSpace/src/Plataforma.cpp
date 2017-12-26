#include "Plataforma.h"


Plataforma::Plataforma(string p_nome, float p_x, float p_y) : Item(p_nome, p_x, p_y)
{
	w = 768;
	h = 100;

	sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/plataforma.png", w, h);
	x = p_x;
	y = p_y;
	atrito = 0;
	angulo = 0.1;
	m_nome = p_nome;
}


Plataforma::~Plataforma()
{
}

void Plataforma::Update()
{

}

void Plataforma::Draw()
{
	C2D2_DesenhaSprite(sprite, 0, x, y);
}

int Plataforma::getSprite()
{
	return sprite;
}

void Plataforma::Run()
{
	Update();
	Draw();
}

float Plataforma::getAtrito()
{
	return atrito;
}

float Plataforma::getX()
{
	return x;
}
float Plataforma::getY()
{
	return y;
}
int Plataforma::getW()
{
	return w;
}
int Plataforma::getH()
{
	return h;
}

void Plataforma::setX(float p_x)
{
	x = p_x;
}
void Plataforma::setY(float p_y)
{
	y = p_y;
}
void Plataforma::addX(float p_x)
{
	x += p_x;
}
void Plataforma::addY(float p_y)
{
	y += p_y;
}
float Plataforma::GetAngulo()
{
	return angulo;
}
