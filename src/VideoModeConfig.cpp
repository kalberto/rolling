#include "VideoModeConfig.h"

VideoModeConfig::VideoModeConfig()
{
	m_bg = C2D2_CarregaSpriteSet("Mundo/Imagens/bg_videomode.png", 1366, 768);
	m_fullscreen = C2D2_CarregaSpriteSet("Mundo/Imagens/fullscreen.png", 357, 37);
	m_windowed = C2D2_CarregaSpriteSet("Mundo/Imagens/windowed.png", 312, 37);
	m_gear = C2D2_CarregaSpriteSet("Mundo/Imagens/gear.png", 56, 56);
	m_mouse = new MyMouse();

	m_xGear = 400;
	m_yGear = 280;
	m_isWindowed = false;
}

VideoModeConfig::~VideoModeConfig()
{
	delete m_mouse;
}

void VideoModeConfig::Run()
{
	Update();
	Draw();
	m_mouse->Run();
}
void VideoModeConfig::Draw()
{
	C2D2_DesenhaSprite(m_bg, 0, 0, 0);
	C2D2_DesenhaSprite(m_fullscreen, 0, 500, 300);
	C2D2_DesenhaSprite(m_windowed, 0, 520, 500);
	C2D2_DesenhaSprite(m_gear, 0, m_xGear, m_yGear);
}
void VideoModeConfig::Update()
{
	if (m_mouse->ObjectIsClicked(500,300,357,37))
	{
		m_xGear = 400;
		m_yGear = 280;

		m_isWindowed = false;
	}

	if (m_mouse->ObjectIsClicked(520, 500, 312, 37))
	{
		m_xGear = 400;
		m_yGear = 480;

		m_isWindowed = true;
	}
}