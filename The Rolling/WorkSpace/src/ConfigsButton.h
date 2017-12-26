#pragma once
#include"Includes.h"
#include "MyMouse.h"
#include "Save.h"
class ConfigsButton
{
private:
	int m_sprite;
	float m_x, m_y;
	int m_w, m_h;
	int m_frame;
public:
	ConfigsButton();
	ConfigsButton(float p_x, float p_y);
	~ConfigsButton();

	void Draw();
	void Run();

	void SetX(float p_x);
	void SetY(float p_y);
	void SetFrame(int p_frame);
	int getFrame();
	float GetX();
	float GetY();
	int GetW();
	int GetH();

};