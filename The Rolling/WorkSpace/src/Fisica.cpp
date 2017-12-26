#pragma once
#include "Fisica.h"


Fisica::Fisica()
{
	gravidade = 0.12;
	PI = 3.14159265;
	resistenciaAr = 0.002; // 0.002 default
}


Fisica::~Fisica()
{
}

void Fisica::AplicaGravidadePF(Bola* p_bola, Item* p_plat = nullptr )
{
	float angulo;
	float velocidadeY;
	float velocidadeX;
	float velocidade;
	if (p_plat == nullptr)
		angulo = 90;
	else
	{
		angulo = CalculaAnguloPB(p_bola, p_plat);
	}
	if (p_bola->GetVeloy() > 1 || p_bola->GetVeloy() < 1)
	{
		if (p_plat == nullptr)
		{
			velocidadeY = gravidade*sin(angulo*PI / 180);
			velocidadeX = gravidade*cos(angulo*PI / 180);

			if (angulo > 90)
			{
				p_bola->addX(p_bola->GetVelox());
				p_bola->addVeloX(velocidadeX);
				p_bola->addY(p_bola->GetVeloy());
				p_bola->addVeloY(velocidadeY);
			}
			if (angulo == 90)
			{
				p_bola->addX(p_bola->GetVelox());
				p_bola->addVeloX(velocidadeX);
				p_bola->addY(p_bola->GetVeloy());
				p_bola->addVeloY(velocidadeY);

			}
			if (angulo < 90)
			{
				p_bola->addX(p_bola->GetVelox());
				p_bola->addVeloX(velocidadeX);
				p_bola->addY(p_bola->GetVeloy());
				p_bola->addVeloY(velocidadeY);
			}
		}
		else
		{
			if (p_bola->getY() > p_plat->getY() - 50)
			{
				p_bola->setY(p_plat->getY() - 38);
			}
			if (angulo > 90)
			{
				velocidade = p_bola->GetVeloy()*cos(angulo*PI / 180) + (-p_bola->GetVelox()*sin(angulo*PI / 180)); // ARRUMAR ESSA BAGAÇA
				p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
				p_bola->addX(p_bola->GetVelox());
				p_bola->setVeloY(-0.8*velocidade*sin(angulo*PI / 180));
				p_bola->setAngulo(atan(p_bola->GetVelox() / p_bola->GetVeloy() * 180 / PI));
			}
			if (angulo == 90)
			{
				velocidade = p_bola->GetVeloy();
				p_bola->addX(p_bola->GetVelox());
				p_bola->addVeloX(gravidade*cos(angulo*PI / 180));
				p_bola->setVeloY(-0.8*velocidade*sin(angulo*PI / 180));
				p_bola->addY(p_bola->GetVeloy());
				p_bola->addVeloY(-gravidade*sin(angulo*PI / 180));

			}
			if (angulo < 90)
			{
				velocidade = p_bola->GetVeloy()*sin(angulo*PI / 180) + p_bola->GetVelox()*cos(angulo*PI / 180); // ARRUMAR ESSA BAGAÇA
				p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
				p_bola->addX(p_bola->GetVelox());
				p_bola->setVeloY(-0.8*velocidade*sin(angulo*PI / 180));
				p_bola->addY(p_bola->GetVeloy());
				p_bola->setAngulo(atan((p_bola->GetVelox() / p_bola->GetVeloy()) * 180 / PI));
			}
		}
	}
	else
	{
		velocidadeY = gravidade*sin(angulo*PI / 180);
		velocidadeX = gravidade*cos(angulo*PI / 180);

		if (angulo > 90)
		{
			p_bola->addX(p_bola->GetVelox());
			p_bola->addVeloX(-velocidadeX);
			p_bola->addY(p_bola->GetVeloy());
			p_bola->addVeloY(velocidadeY);
		}
		if (angulo == 90)
		{
			p_bola->addX(p_bola->GetVelox());
			p_bola->addVeloX(velocidadeX);
			p_bola->addY(p_bola->GetVeloy());
			p_bola->addVeloY(velocidadeY);

		}

		if (angulo < 90)
		{
			p_bola->addX(p_bola->GetVelox());
			p_bola->addVeloX(velocidadeX);
			p_bola->addY(p_bola->GetVeloy());
			p_bola->addVeloY(velocidadeY);
		}
	}
}
float Fisica::CalculaAnguloPB(Bola* p_bola, Item* p_plat = nullptr)
{
	float angulo;
	
	if (p_plat != nullptr)
	{
		angulo = p_plat->m_angulo - p_bola->getAngulo();
	}	
	else
		angulo = p_bola->getAngulo();
	
	if (angulo < 0)
	{
		angulo = angulo*(-1);
	}
	
	return angulo;	
}
float Fisica::CalculaAnguloMB(Bola* p_bola, Item* p_mola)
{
	float angulo;
	angulo = p_mola->getAngulo() - p_bola->getAngulo();

	if (angulo < 0)
	{
		angulo = angulo*(-1);
	}

	return angulo;
}

void Fisica::AplicaAtrito(Bola* p_bola, Item* p_plat= nullptr)
{
	if (p_plat == nullptr)
	{
		p_bola->setVeloY(p_bola->GetVeloy()-resistenciaAr*p_bola->getMassa());
	}
	else
	{
		if (p_bola->GetVelox() > 0)
		{
			p_bola->setVeloX(p_bola->GetVelox() - p_bola->getMassa()*gravidade*p_plat->m_atrito);
			if (p_bola->GetVelox() < 0)
				p_bola->setVeloX(0);
		}
			
		if (p_bola->GetVelox() < 0)
		{
			p_bola->setVeloX(p_bola->GetVelox() + p_bola->getMassa()*gravidade*p_plat->m_atrito);
			if (p_bola->GetVelox() > 0)
				p_bola->setVeloX(0);
		}
			
	}
}
void Fisica::AplicaForçaMola(Bola* p_bola, Item* p_mola)
{
	float angulo;
	angulo = CalculaAnguloMB(p_bola,p_mola);
	float forçaB;
	forçaB = sqrt(pow(p_bola->GetVelox(),2.0) + pow(p_bola->GetVeloy(),2.0));
	p_bola->setVeloX(forçaB*cos(angulo*PI / 180));
	p_bola->setVeloY(forçaB*sin(angulo*PI / 180));
}
