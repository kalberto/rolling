#pragma once

#include"Includes.h"

class Bola
{
private:
	int sprite;
	float x;
	float y;
	float velocidade;
	float velocidadeX;
	float velocidadeY;
	int w;
	int h;
	float m_angulo;
	float m_massa;
	float m_raio;

public:
	Bola();
	~Bola();
	bool ver ;
	void Draw();
	void Update();
	void Run();

	float getMassa();
	int getW();
	int getH();
	float getX();
	float getY();
	float getRaio();
	float getSpeed();
	float GetVelox();
	float GetVeloy();
	int getSprite();
	float getAngulo();

	void setX(int p_x);
	void setY(int p_y);
	void setSpeed(float p_speed);
	void setVeloX(float x);
	void setVeloY(float y);
	void setAngulo(float angulo);
	void setMassa(float p_massa);
	void setRaio(float p_raio);

	void addX(float p_x);
	void addY(float p_y);
	void addSpeed(int p_speed);
	void addVeloX(float x);
	void addVeloY(float y);
	
};

