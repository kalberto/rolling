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

	Item(string p_nome);
	Item(string p_nome, float p_x, float p_y);
	void Update();
	void Draw();
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
	

};
/*
unsigned int sprite;
int indice;
float angulo, atrito;
int x, y, xInicio, yInicio;
string nome;
bool isDraging;

Item(string nome);
Item(string nome, float x, float y);
void Update();
void Draw();
void ReturnPosition();
void Drop();

string Get_Name();
int Get_X();
int Get_Y();
int Get_Xinicio();
int Get_Yinicio();
float Get_angulo();
float Get_atrito();
int Get_indice();
unsigned int Get_Sprite();

void Set_Name(string p_name);
void Set_X(int p_x);
void Set_Y(int p_y);
void Set_angulo(float p_angulo);
void Set_atrito(float p_atributo);
void Set_indice(int p_indice);*/