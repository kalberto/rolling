#pragma once

#include "Includes.h"

#include "DlinkedList.h"
#include "Item.h"
#include "Bola.h"
#include "Background.h"
#include "Includes.h"

class Camera
{
public:
	int m_xAdded;
	int m_yAdded;
	float m_speed;
	int m_x, m_y;


	void Move(C2D2_Botao* p_teclado, Background* p_bg);
	void Update();
	void Run();

	Camera();
	~Camera();
};