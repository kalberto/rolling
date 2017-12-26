#pragma once
#include "Item.h"
#include"Includes.h"

using namespace std;

class Plataforma : public Item
{
private:
	string name;
	int sprite;
	float x;
	float y;
	int w;
	int h;
	float atrito;
	float angulo;
public:
	Plataforma(string p_nome, float p_x, float p_y);
	~Plataforma();

	void Draw();
	void Update();
	void Run();

	// Seters e Geters
	float getAtrito();
	float getX();
	float getY();
	int getW();
	int getH();
	int getSprite();
	void setX(float p_x);
	void setY(float p_y);
	void addX(float p_x);
	void addY(float p_y);
	float GetAngulo();

};

