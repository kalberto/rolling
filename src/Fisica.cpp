#pragma once
#include "Includes.h"
#include "Fisica.h"
#include <math.h>

Fisica::Fisica()
{
	gravidade = 0.12;
	PI = acos(-1);
	resistenciaAr = 0.002; // 0.002 default
	perdaV = 0.8;
	m_cair = true;
}


Fisica::~Fisica()
{
}

void Fisica::Aplicagravidade(Bola* p_bola)
{
	
	if (m_cair == false)
	{
		p_bola->addY(p_bola->GetVeloy());
		p_bola->addX(p_bola->GetVelox());
		return;
	}
	else
	{
		p_bola->addVeloY(gravidade);
		p_bola->addY(p_bola->GetVeloy());
		p_bola->addX(p_bola->GetVelox());
	}
}

void Fisica::Setarcair(bool p_cair)
{
	m_cair = p_cair;
}

void Fisica::AplicaGravidadePF(Bola* p_bola, Item* p_plat = nullptr )
{
	//if (p_plat == nullptr)
	//	AplicaAtrito(p_bola, nullptr);
	//else
	//	AplicaAtrito(p_bola, p_plat);

	//float angulo;
	//float velocidadeY;
	//float velocidadeX;
	//float velocidade;
	//if (p_plat == nullptr)
	//	angulo = 90;
	//else
	//{
	//	angulo = CalculaAnguloPB(p_bola, p_plat);
	//}
	//if (true)//p_bola->GetVeloy() > 1 || p_bola->GetVeloy() < 1
	//{
	//	if (p_plat == nullptr)
	//	{
	//		velocidadeY = gravidade*sin(angulo*PI / 180);
	//		velocidadeX = gravidade*cos(angulo*PI / 180);

	//		if (angulo > 90)
	//		{
	//			p_bola->addX(p_bola->GetVelox());
	//			p_bola->addVeloX(velocidadeX);
	//			p_bola->addY(p_bola->GetVeloy());
	//			p_bola->addVeloY(velocidadeY);
	//		}
	//		if (angulo == 90)
	//		{
	//			
	//			p_bola->addVeloX(velocidadeX);
	//			p_bola->addX(p_bola->GetVelox());
	//			
	//			p_bola->addVeloY(velocidadeY);
	//			p_bola->addY(p_bola->GetVeloy());

	//		}
	//		if (angulo < 90)
	//		{
	//			p_bola->addX(p_bola->GetVelox());
	//			p_bola->addVeloX(velocidadeX);
	//			p_bola->addY(p_bola->GetVeloy());
	//			p_bola->addVeloY(velocidadeY);
	//		}
	//	}
	//	else
	//	{
	//		//if (p_bola->getY() > p_plat->getY() - 50)
	//		//{
	//		//	p_bola->setY(p_plat->getY() - 38);
	//		//}
	//		if (angulo > 90)
	//		{
	//			velocidade = p_bola->GetVeloy()*sin(angulo*PI / 180) + (-p_bola->GetVelox()*cos(angulo*PI / 180)); // ARRUMAR ESSA BAGAÇA
	//			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
	//			p_bola->addX(p_bola->GetVelox());
	//			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
	//			p_bola->setAngulo(atan(p_bola->GetVelox() / p_bola->GetVeloy() * 180 / PI));
	//		}
	//		if (angulo == 90)
	//		{
	//			velocidade = p_bola->GetVeloy();
	//			p_bola->addX(p_bola->GetVelox());
	//			p_bola->addVeloX(gravidade*cos(angulo*PI / 180));
	//			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
	//			p_bola->addY(p_bola->GetVeloy());
	//			p_bola->addVeloY(-gravidade*sin(angulo*PI / 180));

	//		}
	//		if (angulo < 90)
	//		{
	//			velocidade = p_bola->GetVeloy()*sin(angulo*PI / 180) + p_bola->GetVelox()*cos(angulo*PI / 180); // ARRUMAR ESSA BAGAÇA
	//			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
	//			p_bola->addX(p_bola->GetVelox());
	//			p_bola->setVeloY(perdaV*velocidade*sin(angulo*PI / 180)*-1);
	//			p_bola->addY(p_bola->GetVeloy());
	//			p_bola->setAngulo(atan((p_bola->GetVelox() / p_bola->GetVeloy()) * 180 / PI));			
	//		}
	//	}
	//}
	//else
	//{
	//	velocidadeY = gravidade*sin(angulo*PI / 180);
	//	velocidadeX = gravidade*cos(angulo*PI / 180);

	//	if (angulo > 90)
	//	{
	//		p_bola->addX(p_bola->GetVelox());
	//		p_bola->addVeloX(-velocidadeX);
	//		p_bola->addY(p_bola->GetVeloy());
	//		p_bola->addVeloY(velocidadeY);
	//	}
	//	if (angulo == 90)
	//	{
	//		velocidade = p_bola->GetVeloy();
	//		p_bola->addX(p_bola->GetVelox());
	//		p_bola->addVeloX(gravidade*cos(angulo*PI / 180));
	//		p_bola->setVeloY(-0.8*velocidade*sin(angulo*PI / 180));
	//		p_bola->addY(p_bola->GetVeloy());
	//		p_bola->addVeloY(-gravidade*sin(angulo*PI / 180));

	//	}

	//	if (angulo < 90)
	//	{
	//		p_bola->addX(p_bola->GetVelox());
	//		p_bola->addVeloX(velocidadeX);
	//		p_bola->addY(p_bola->GetVeloy());
	//		p_bola->addVeloY(velocidadeY);
	//	}
	//}

float velocidade;
float angulo;
if (p_plat == nullptr)
{
	AplicaAtrito(p_bola, nullptr);
	p_bola->addX(p_bola->GetVelox());
	p_bola->addVeloX(gravidade*cos(p_bola->getAngulo()*PI / 180));
	p_bola->addY(p_bola->GetVeloy());
	p_bola->addVeloY(gravidade*sin(p_bola->getAngulo()*PI / 180));
}
else
{
	angulo = CalculaAnguloPB(p_bola, p_plat);

	velocidade = sqrt(pow(p_bola->GetVelox(), 2) + pow(p_bola->GetVeloy(), 2));
	p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
	p_bola->addVeloX(p_bola->GetVelox());
	p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
	p_bola->addVeloY(p_bola->GetVeloy());
}

}
void Fisica::FisicaBolaPlat(Bola* p_bola, Item* p_plat = nullptr)
{
	
	float velocidade, velo;
	float angulo;
	int angulop = p_plat->getAngulo();
	if (p_plat == nullptr)
	{
		m_cair == true;
		AplicaAtrito(p_bola, nullptr);
		p_bola->addX(p_bola->GetVelox());
		p_bola->addVeloX(gravidade*cos(p_bola->getAngulo()*PI / 180));
		p_bola->addY(p_bola->GetVeloy());
		p_bola->addVeloY(gravidade*sin(p_bola->getAngulo()*PI / 180));
	}
	else
	{
		angulo = CalculaAnguloPB(p_bola, p_plat);
		/*switch (angulop)
		{
		case 90:
			if (p_bola->getX() < p_plat->getX() + 75)
			{
				velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
				p_bola->setVeloX(-velocidade*sin(angulo*PI / 180));
				p_bola->setVeloY(-perdaV*velocidade*cos(angulo*PI / 180));
				p_bola->addX(p_bola->GetVelox());
				p_bola->addY(p_bola->GetVeloy());
			}
			else
			{
				velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
				p_bola->setVeloX(velocidade*sin(angulo*PI / 180));
				p_bola->setVeloY(-perdaV*velocidade*cos(angulo*PI / 180));
				p_bola->addX(p_bola->GetVelox());
				p_bola->addY(p_bola->GetVeloy());
			}
			break;
		case 0 :
			velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
			p_bola->addX(p_bola->GetVelox());
			p_bola->addY(p_bola->GetVeloy());
			break;
		case 135:
			velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
			p_bola->addX(p_bola->GetVelox());
			p_bola->addY(p_bola->GetVeloy());

			break;
		case 45:
			velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
			p_bola->addX(p_bola->GetVelox());
			p_bola->addY(p_bola->GetVeloy());
			break;

		}*/
		
/*
			if (angulo < 0 && angulo > -90)
			{
				
			}
			if (angulo < -90 && angulo > -180)
			{
				velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
				p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
				p_bola->setVeloY(perdaV*velocidade*sin(angulo*PI / 180));
				p_bola->addY(p_bola->GetVeloy());
				return;
			}
			if (angulo < -180 && angulo > -270)
			{
				velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
				p_bola->setVeloX(-velocidade*cos(angulo*PI / 180));
				p_bola->setVeloY(perdaV*velocidade*sin(angulo*PI / 180));
				p_bola->addX(p_bola->GetVelox());
				p_bola->addY(p_bola->GetVeloy());
				return;
			}*/
			velocidade = sin(p_bola->getAngulo()*PI / 180)*p_bola->GetVeloy() + cos(p_bola->getAngulo()*PI / 180)*p_bola->GetVelox();
			p_bola->setVeloX(velocidade*cos(angulo*PI / 180));
			p_bola->setVeloY(-perdaV*velocidade*sin(angulo*PI / 180));
			p_bola->addX(p_bola->GetVelox());
			p_bola->addY(p_bola->GetVeloy());	
			if (p_plat->getAngulo() == 0)
			{
				m_cair = false;
			}
			else
			{
				m_cair = true;
			}
	}
}
float Fisica::CalculaAnguloPB(Bola* p_bola, Item* p_plat = nullptr)
{
	float angulo, angulob = p_bola->getAngulo();
	
	/*if (p_plat != nullptr)
	{
		if (p_bola->getX() < p_plat->getXinicio())
		{
			angulo = p_bola->getAngulo() - 90;
			return angulo;
		}
		if (p_plat->getAngulo() > p_bola->getAngulo())
		{
			if (p_bola->getAngulo() < 0)
				angulob*-1;
			angulo = p_plat->m_angulo - angulob;
		}
		if (p_bola->getAngulo() > p_plat->getAngulo())
		{
			angulo = p_bola->getAngulo() - p_plat->getAngulo();
		}
		
		return angulo;
	}
	else*/

	angulo = angulob - p_plat->getAngulo() * 2;
	return angulo;
	//angulo = p_bola->getAngulo();
	
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
		if (p_bola->GetVelox() != 0 && p_bola->GetVeloy() != 0)
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
	forçaB = sqrt(pow(p_bola->GetVelox(),2.0) + pow(p_bola->GetVeloy(),2.0)) *1.3;
	p_bola->setVeloX(forçaB*cos(angulo*PI / 180));
	p_bola->setVeloY(-forçaB*sin(angulo*PI / 180));
}

