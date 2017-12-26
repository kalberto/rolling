#pragma once

#include"Includes.h"
#include "MyMouse.h"

class ResetLevelButton
{
private:
	
	int m_frame;
	int m_x, m_y;
	int m_w, m_h;
public:
	int m_sprite;
	ResetLevelButton();
	ResetLevelButton(float p_x, float p_y);
	~ResetLevelButton();

	void Draw();
	void Run();

	void SetX(float p_x);
	void SetY(float p_y);
	void SetFrame(int p_frame);
	int GetX();
	int GetY();
	int GetFrame();
	int GetW();
	int GetH();

};

