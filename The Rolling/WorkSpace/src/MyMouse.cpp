#include "MyMouse.h"


MyMouse::MyMouse()
{
	IsAnimation = false;
	Mouse = C2D2_PegaMouse();
	sprite = C2D2_CarregaSpriteSet("Mundo/Imagens/sprite_cursor.png", 32, 32);
	frame = 0;
	timer = 0;
	indice = 0;
	itemDraging = nullptr;
}


MyMouse::~MyMouse()
{

}

int MyMouse::GetX()
{
	return Mouse->x;
}

int MyMouse::GetY()
{
	return Mouse->y;
}

void MyMouse::Animation()
{
	if (IsAnimation == true)
	{
		if (timer % 2 == 0)
		{
			frame++;
			if (frame == 6)
			{
				frame = 0;
				IsAnimation = false;
			}
		}
	}
	timer++;

//	Animator(IsAnimation, &timer, &frame);
}

void MyMouse::Update()
{
	if (Mouse->botoes->pressionado)
	{
		IsAnimation = true;
	}

	if (itemDraging != nullptr)
	{
		itemDraging->setX(Mouse->x);
		itemDraging->setY(Mouse->y);
	}
}

void MyMouse::Draw()
{
	C2D2_DesenhaSprite(sprite, frame, Mouse->x, Mouse->y);
}

void MyMouse::Run()
{
	Update();
	Animation();
	Draw();
}



bool MyMouse::OnAnyClick()
{
	if (Mouse->botoes->pressionado)
	{
		return true;
	}
	return false;
}
bool MyMouse::MouseIsOverlapping(Item* item)
{
	if (C2D2_ColidiuSprites(sprite, indice, Mouse->x, Mouse->y, item->m_sprite, item->m_indice, item->m_x, item->m_y))
	{
		return true;
	}
	return false;
}

bool MyMouse::MouseIsOverlapping(int p_x, int p_y, int p_w, int p_h)
{
	if (Mouse->x >= p_x && Mouse->x <= p_x + p_w) // colisão em X
	{
		if (Mouse->y >= p_y && Mouse->y <= p_y + p_h) //colisão em Y
		{
			return true;

		}

	}
	return false;
}

bool MyMouse::ObjectIsClicked(int p_x, int p_y, int p_w, int p_h)
{
	if (Mouse->x >= p_x && Mouse->x <= p_x + p_w) // colisão em X
	{
		if (Mouse->y >= p_y && Mouse->y <= p_y + p_h) //colisão em Y
		{
			if (Mouse->botoes->pressionado)
			{
				return true;
			}

		}

	}
	return false;
}

bool MyMouse::ItemIsClicked(Item* item)
{
	if (Mouse->botoes->pressionado)
	{

		if (C2D2_ColidiuSprites(sprite, indice, Mouse->x, Mouse->y, item->m_sprite, item->m_indice, item->m_x, item->m_y))
		{

			itemDraging = item;
			return true;
		}
	}

	return false;
}

bool MyMouse::ButtonUp()
{
	if (Mouse->botoes->liberado)
	{
		return true;

	}
	return 0;
}