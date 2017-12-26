#pragma once
#include "Includes.h"
#include "Item.h"

class MyMouse
{
private:
	
	unsigned int sprite;
	int indice;
	int frame;
	int timer; // � o contador, que � aumentado + 1 a cada frame do jogo, a cada 1 seg (60 frames) o timer == 60;
	bool IsAnimation;
	

public:
	C2D2_Mouse* Mouse;
	MyMouse();
	~MyMouse();

	Item* itemDraging;
	 int GetX();
	 int GetY();

	bool OnAnyClick();
	bool ObjectIsClicked(int p_x, int p_y, int p_w, int p_h); // X do bot�o, Y do bot�o, largura do bot�o, altura do bot�o
	bool MouseIsOverlapping(Item* item);
	bool MouseIsOverlapping(int p_x, int p_y, int p_w, int p_h);
	

	bool ItemIsClicked(Item* item);
	bool ButtonUp();

	void Animation();
	void Update();
	void Draw();
	void Run();
};

