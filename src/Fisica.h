#pragma once
#include "Bola.h"

#include "Mola.h"
#include "Item.h"
#include"Includes.h"

class Fisica
{
public:
	Fisica();
	~Fisica();
	void AplicaGravidadePF(Bola* p_bola, Item* p_plat);
	float CalculaAnguloPB(Bola* p_bola, Item* p_plat);
	float CalculaAnguloMB(Bola* p_bola, Item* p_mola);
	void AplicaAtrito(Bola*p_bola, Item* p_plat);
	void AplicaForçaMola(Bola* p_bola, Item* p_mola);
	void FisicaBolaPlat(Bola* p_bola, Item* p_plat );
	void Aplicagravidade(Bola* p_bola);
	void Setarcair(bool p_cair);

private:
	float gravidade;
	float resistenciaAr;
	float PI;
	float perdaV;
	bool m_cair;
};

