#pragma once
#include"Includes.h"

#include"MyMouse.h"

class PlayStop
{
private:
	int m_sprite_hud;
	int m_sprite_play;
	int m_sprite_stop;

	int m_x_hud;
	int m_y_hud;

	int m_x_play;
	int m_y_play;

	int m_x_stop;
	int m_y_stop;

	bool isPlay;
	bool isStop;

public:
	PlayStop();
	~PlayStop();

	void Update(MyMouse* p_mouse);
	void Draw();
	void Run(MyMouse* p_mouse);	

	bool getIsPlay();
	bool getIsStop();

	void setIsPlay(bool p_bool);
	void setIsStop(bool p_bool);
};