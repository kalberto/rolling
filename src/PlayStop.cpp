#include "PlayStop.h"

PlayStop::PlayStop()
{
	m_sprite_hud = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_hud.png", 147, 50);
	m_sprite_play = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_play.png", 21, 40);
	m_sprite_stop = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_stop.png", 39, 38);

	m_x_hud = 550;
	m_y_hud = 700;

	m_x_play = m_x_hud + 30;
	m_y_play = m_y_hud + 5;

	m_x_stop = m_x_play + 50;
	m_y_stop = m_y_play;

	isPlay = isStop = false;
}
PlayStop::~PlayStop()
{

}

void PlayStop::Update(MyMouse* p_mouse)
{
	if (p_mouse->ObjectIsClicked(m_x_play - 10,m_y_play,21,40))
	{
		isPlay = true;
	}

	if (p_mouse->ObjectIsClicked(m_x_stop - 10, m_y_stop, 39, 38))
	{
		isPlay = false;
		isStop = true;
	}
}

void PlayStop::Draw()
{
	C2D2_DesenhaSprite(m_sprite_hud, 0, m_x_hud, m_y_hud);
	C2D2_DesenhaSprite(m_sprite_play, 0, m_x_play, m_y_play);
	C2D2_DesenhaSprite(m_sprite_stop, 0, m_x_stop, m_y_stop);
}

void PlayStop::Run(MyMouse* p_mouse)
{
	Update(p_mouse);
	Draw();
}

bool PlayStop::getIsPlay()
{
	return isPlay;
}
bool PlayStop::getIsStop()
{
	return isStop;
}

void PlayStop::setIsPlay(bool p_bool)
{
	isPlay = p_bool;
}
void PlayStop::setIsStop(bool p_bool)
{
	isStop = p_bool;
}