#pragma once

#include "Includes.h"
#include "Save.h"
#include "Camera.h"
#include "Bola.h"

class EndLevel
{
private:
	int m_sprite;
	float m_x, m_y;
	int m_level;

	int m_flag;
	int m_xFlag;
	int m_yFlag;

	int m_timer;

	bool inLevel;

	Save* m_save;
public:
	
	EndLevel();

	EndLevel(int p_level, Save* p_save);

	~EndLevel();

	void Update(Bola* p_bola, bool* p_back);
	void Draw(Camera* p_camera);
	void Run(Camera* p_camera,Bola* p_bola,bool* p_back);
	void SaveFinishedLevel();

	bool getInLevel();
	float getX();
	float getY();

	void setX(float p_x);
	void setY(float p_y);
};