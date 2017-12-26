#pragma once

#include "Includes.h"

class Background
{
private:
	int m_sprite;
	int m_x;
	int m_y;
	int m_w;
	int m_h;

public:
	Background();
	Background(string p_sprite);
	~Background();

	void Run();
	void Draw();
	void Update();

	int getX();
	int getY();
	int getW();
	int getH();
	void setX(int p_x);
	void setY(int p_y);
};