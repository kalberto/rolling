#pragma once
#include"Includes.h"

class Mola
{
private:
	float m_angulo;
	float m_PosX, m_PosY;
	float m_distancia;
	float m_coeficiente;//???????TALVEZ MAIS PRA FRENTE
	int m_sprite;
	int m_w, m_h;
public:

	float RetornaForça();
	float getAngulo();
	void MudarPosX(float p_x);
	void MudarPoxY(float p_y);
	void MudarPosXY(float p_x, float  p_y);
	void MudarDistancia(float p_distancia); // TALVEZ DEPOIS
	void AddDitancia(float p_distancia);
	void MudarCoeficiente(float p_coeficiente);

	Mola();
	~Mola();
};

