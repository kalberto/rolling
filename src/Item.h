#pragma once
#include "Includes.h"

using namespace std;

class Item
{
public:
	unsigned int m_sprite;
	int m_indice;
	float m_angulo, m_atrito;
	float m_coeficiente, m_distancia;
	int m_w,m_h;
	int m_x, m_y, m_xInicio, m_yInicio;
	string m_nome;
	bool m_isDraging;
	int m_xDraw;
	int m_yDraw;

	Item(string p_nome);
	Item(string p_nome, float p_x, float p_y);
	Item(string p_nome, float p_x, float p_y,float p_angulo,int p_indice);
	void Update();
	void Draw();
	void Draw(int px, int py);
	void ReturnPosition();
	void Drop();

	string getName();

	int getX();
	int getY();
	int getXinicio();
	int getYinicio();
	float getAngulo();
	float getAtrito();
	int getIndice();
	unsigned int getSprite();

	void setName(string p_name);
	void setX(int p_x);
	void setY(int p_y);
	void setAngulo(float p_angulo);
	void setAtrito(float p_atributo);
	void setIndice(int p_indice);
	void rotPlat();
	

};
