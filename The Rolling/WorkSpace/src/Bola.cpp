#include "Bola.h"
#define PI 3.14159265

Bola::Bola()
{
	sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/bola.png", 40, 40);
	x = 140;
	y = 160;
	w = 40;
	h = 40;
	velocidade = 0;
	velocidadeX = 0;
	velocidadeY = 0;
	ver = true;
	m_angulo = 90;
	m_raio = 20;
	m_massa = 1;
}

Bola::~Bola()
{
}

float Bola::getRaio()
{
	return m_raio;
}
void Bola::setRaio(float p_raio)
{
	m_raio = p_raio;
}
void Bola::Update()
{
	x += velocidade;
}

void Bola::Draw()
{
	C2D2_DesenhaSprite(sprite,0,x,y);
}

void Bola::addVeloX(float x)
{
	velocidadeX += x;
}

int Bola::getSprite()
{
	return sprite;
}

void Bola::setVeloX(float x)
{
	velocidadeX = x;
}

void Bola::setVeloY(float y)
{
	velocidadeY = y;
}

void Bola::addVeloY(float y)
{
	velocidadeY += y;
}

float Bola::GetVelox()
{
	return velocidadeX;
}

float Bola::GetVeloy()
{
	return velocidadeY;
}
void Bola::Run()
{
	Update();
	Draw();
}

int Bola::getW()
{
	return w;
}
int Bola::getH()
{
	return h;
}
float Bola::getX()
{
	return x;
}

float Bola::getAngulo()
{
	float p_angulo;
	if(velocidadeX == 0 && velocidadeY == 0)
	{
		p_angulo = 90;
	}
	else 
	{
	 p_angulo = (90-(180/PI*acos(velocidadeY / sqrt(pow(velocidadeX, 2) + pow(velocidadeY, 2)))));
	 if (p_angulo < 0)
		 p_angulo = p_angulo*-1;
	}
	
	m_angulo = p_angulo;
	return m_angulo;
}

float Bola::getY()
{
	return y;
}
float Bola::getSpeed()
{
	return velocidade;
}
void Bola::setX(int p_x)
{
	x = p_x;
}
void Bola::setY(int p_y)
{
	y = p_y;
}
void Bola::setSpeed(float p_speed)
{
	velocidade = p_speed;
}
void Bola::addX(float p_x)
{
	x += p_x;
}
void Bola::addY(float p_y)
{
	y += p_y;
}
void Bola::addSpeed(int p_speed)
{
	velocidade += p_speed;
}

void Bola::setAngulo(float angulo)
{
	m_angulo = angulo;
}

float Bola::getMassa()
{
	return m_massa;
}
void Bola::setMassa(float p_m)
{
	m_massa = p_m;
}