#pragma once
#include"Includes.h"
#include "MyMouse.h"
#include "Save.h"
class SaveButton
{
private:
	int m_sprite;
	float m_x, m_y;
	int m_w, m_h;
public:
	SaveButton();
	SaveButton(float p_x,float p_y);
	~SaveButton();

	void Draw();
	void Run();

	void SetX(float p_x);
	void SetY(float p_y);
	float GetX();
	float GetY();
	int GetW();
	int GetH();

};

