#pragma once

#include "Menu_inicial.h"
#include"Includes.h"

using namespace std;

class VideoModeConfig
{
private:
	bool m_isWindowed; // false = FULLSCREEN | true - WINDOWED MODE
	MyMouse* m_mouse;
	int m_bg;
	int m_fullscreen;
	int m_windowed;
	int m_gear;
	int m_xGear;
	int m_yGear;

public:
	VideoModeConfig();
	~VideoModeConfig();

	bool getVideoMode();
	void setVideoMode(bool p_videoMode);
	void Run();
	void Update();
	void Draw();
};

