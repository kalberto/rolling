#include "Camera.h"

Camera::Camera()
{
	m_xAdded = 0;
	m_yAdded = 0;
	m_speed = 10.0f;
	m_x = 0;
	m_y = 0;
}

Camera::~Camera()
{

}

void Camera::Run()
{
}

void Camera::Update()
{

}

void Camera::Move(C2D2_Botao* p_teclado, Background* p_bg)
{

	
	

	if (p_teclado[C2D2_D].ativo && m_x < (p_bg->getX() + p_bg->getW() * 2 - LARGURATELA))
	{
		
		p_bg->setX((p_bg->getX() - (m_speed / 2)));

		m_x += m_speed;
		m_xAdded += m_speed;

	}

	if (p_teclado[C2D2_A].ativo && m_x > p_bg->getX())
	{
		

		p_bg->setX((p_bg->getX() + (m_speed / 2)));
		m_x -= m_speed;
		m_xAdded -= m_speed;

	}

	if (p_teclado[C2D2_W].ativo && m_y > p_bg->getY())
	{
		
		p_bg->setY((p_bg->getY() + (m_speed / 2)));

		m_y -= m_speed;
		m_yAdded -= m_speed;
		}

	if (p_teclado[C2D2_S].ativo && m_y < (p_bg->getY() + p_bg->getH() * 2 - ALTURATELA))
	{

		p_bg->setY((p_bg->getY() - (m_speed / 2)));

		m_y += m_speed;
		m_yAdded += m_speed;

	}

	if (p_teclado[C2D2_R].ativo)
	{
		/*p_bg->setY((p_bg->getY() - (m_yAdded / 2)));

		m_y -= m_yAdded;
		m_yAdded -= m_yAdded;



		
		p_bg->setX((p_bg->getX() - (m_xAdded / 2)));

		m_x -= m_xAdded;
		m_xAdded -= m_xAdded;*/


		p_bg->setX(0);
		p_bg->setY(0);
		m_x = 0;
		m_y = 0;

	}
}