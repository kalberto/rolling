#pragma once
#include "Fase.h"

Fase::Fase(int p_level)
{
	m_level = p_level;
	m_back = false;
	//m_UpMask = m_DownMask = C2D2_CarregaSpriteSet("Mundo/Imagens/mask_f.png", 1366, 84);
	MyKeyborad = C2D2_PegaTeclas();
	SaveGame = new Save();
	Mymouse = new MyMouse();
	partesFase = new DLinkedList < Item* >();
	itensFase = new DLinkedList < Item* >();
	iterator_ItensFase = itensFase->GetIterator();
	iterator_partesFase = partesFase->GetIterator();
	itensHud = new Array < Item* >(10);
	m_bola = new Bola();
	resetButton = new ResetLevelButton(50, 680);

	m_bg = new Background("fase1");
	myCamera = new Camera;
	myPlayStop = new PlayStop;

	Inicializa();
		itensHud->m_array[0] = new Item("plataforma", 20, -10);
		itensHud->m_array[1] = new Item("mola", 250, 50);
		itensHud->m_array[2] = new Item("plataforma", 5000, 50);
		itensHud->m_array[3] = new Item("plataforma", 5000, 50);
		itensHud->m_array[4] = new Item("plataforma", 5000, 50);
		itensHud->m_array[5] = new Item("plataforma", 5000, 50);
		itensHud->m_array[6] = new Item("plataforma", 5000, 50);
		itensHud->m_array[7] = new Item("plataforma", 5000, 50);
		itensHud->m_array[8] = new Item("plataforma", 5000, 50);
		itensHud->m_array[9] = new Item("plataforma", 5000, 50);

	hudFase = new Hud(itensHud);

	endLevel = new EndLevel(m_level,SaveGame);
	
}

Fase::~Fase()
{
	delete Mymouse;
	delete MyKeyborad;
	delete partesFase;
	delete itensHud;
	delete itensFase;
	delete hudFase;	
	delete SaveGame;
}

void Fase::Inicializa()
{
	SaveGame->ReadObject2(partesFase,m_level);
	cout << endl << "------------------ Fase Inicializada! ------------------" << endl << endl;
}

void Fase::Run()
{
	Update();
	m_bg->Run();
	Draw();
	resetButton->Run();
	
	m_bola->Run(myCamera->m_x, myCamera->m_y);
	myCamera->Move(MyKeyborad, m_bg);
	myPlayStop->Run(Mymouse);	
	
	
	
	
	endLevel->Run(myCamera, m_bola, &m_back);

	if (endLevel->getInLevel() == true)
	{
		hudFase->Draw(); // desenha os itens do Hud
	}
	
	Mymouse->Run(myCamera->m_x, myCamera->m_y);
}

void Fase::Update()
{
	if (MyKeyborad[C2D2_ESC].pressionado || MyKeyborad[C2D2_ENCERRA].pressionado)
	{
		m_back = true;

		cout << m_back;

	}
	
	if (Mymouse->MouseIsOverlapping(resetButton->GetX(), resetButton->GetY(), resetButton->GetW(), resetButton->GetH()))
		resetButton->SetFrame(1);
	else
		resetButton->SetFrame(0); 
	
	if (Mymouse->itemDraging != nullptr)
	{
		Mymouse->itemDraging->Update();

	}


	if (Mymouse->itemDraging == nullptr)
	{
		if (Mymouse->OnAnyClick()) // testa se o mouse esta clicado e sobr
		{
			for (int i = 0; i < 10; i++)
			{
				if (Mymouse->ItemIsClicked(itensHud->m_array[i]))
				{
					Mymouse->itemDraging = itensHud->m_array[i];
					Mymouse->itemDragingInHud = true;
					break;
				}
			}
			iterator_ItensFase = itensFase->GetIterator();
			while (iterator_ItensFase.Valid() == true)
			{
				if (Mymouse->ItemIsClicked(iterator_ItensFase.m_node->m_data))
				{
					Mymouse->itemDraging = iterator_ItensFase.m_node->m_data;
					Mymouse->itemDragingInFase = true;
					break;
				}
				iterator_ItensFase.Forth();
			}
		}
	}
	if (Mymouse->ButtonUp())
	{
		if (Mymouse->itemDraging != nullptr)
		{
			SoltarItem(Mymouse->itemDraging);
			Mymouse->itemDraging = nullptr;
			Mymouse->itemDragingInHud = false;
			Mymouse->itemDragingInFase = false;

		}
	}
	

	if (myPlayStop->getIsPlay() == true)
	{
		m_fisica.Aplicagravidade(m_bola); // se clicar play ai sim aplic a gravidade
		m_fisica.Setarcair(true);
	}
		

	if (myPlayStop->getIsStop() == true) // cliquei em stop, preciso resetar a posição da bola e deixa-la parada
	{
		m_bola = new Bola;
		myPlayStop->setIsStop(false);
	}
	

	iterator_partesFase = partesFase->GetIterator();
	
	while (iterator_partesFase.Valid() == true)
	{
		if (C2D2_ColidiuSprites(m_bola->getSprite(), 0, m_bola->getX(), m_bola->getY(), iterator_partesFase.m_node->m_data->m_sprite, iterator_partesFase.m_node->m_data->m_indice, iterator_partesFase.m_node->m_data->m_x, iterator_partesFase.m_node->m_data->m_y))
		{
			if (iterator_partesFase.m_node->m_data->m_nome == "plataforma")
				m_fisica.FisicaBolaPlat(m_bola, iterator_partesFase.m_node->m_data);
			if (iterator_partesFase.m_node->m_data->m_nome == "mola")
				m_fisica.AplicaForçaMola(m_bola, iterator_partesFase.m_node->m_data);

			break;
		}
		iterator_partesFase.Forth();
	}

	iterator_ItensFase = itensFase->GetIterator();
	while (iterator_ItensFase.Valid() == true)
	{
		if (C2D2_ColidiuSprites(m_bola->getSprite(), 0, m_bola->getX(), m_bola->getY(), iterator_ItensFase.m_node->m_data->m_sprite, iterator_ItensFase.m_node->m_data->m_indice, iterator_ItensFase.m_node->m_data->m_x, iterator_ItensFase.m_node->m_data->m_y))
		{
			if (iterator_ItensFase.m_node->m_data->m_nome == "plataforma")
				m_fisica.FisicaBolaPlat(m_bola, iterator_ItensFase.m_node->m_data);
			if (iterator_ItensFase.m_node->m_data->m_nome == "mola")
				m_fisica.AplicaForçaMola(m_bola, iterator_ItensFase.m_node->m_data);

			break;
		}
		iterator_ItensFase.Forth();
	}


	if (itensFase->m_count >= 1)
	{
		if (MyKeyborad[C2D2_X].pressionado && itensFase->m_tail->m_data->getName() == "plataforma")
		{
			itensFase->m_tail->m_data->rotPlat();

		}
	}

}

void Fase::Draw()
{
	C2D2_DesenhaSprite(m_UpMask, 0, 0, 0);
	C2D2_DesenhaSprite(m_DownMask, 0, 0, 684);

	

	//Desenha itenhs da fase
	iterator_ItensFase = itensFase->GetIterator();
	while (iterator_ItensFase.Valid() == true)
	{
		iterator_ItensFase.m_node->m_data->Draw(myCamera->m_x, myCamera->m_y);
		iterator_ItensFase.Forth();
	}

	iterator_partesFase = partesFase->GetIterator();
	while (iterator_partesFase.Valid() == true)
	{
		iterator_partesFase.m_node->m_data->Draw(myCamera->m_x, myCamera->m_y);
		iterator_partesFase.Forth();
	}

}

void Fase::AddItensFase(Item item_solto)
{
	itensFase->Append(new Item(item_solto));
}

void Fase::AddPartesFase(Item item_solto)
{
	partesFase->Append(new Item(item_solto));
}

void Fase::SoltarItem(Item* itemdraging)
{
	for (int i = 0; i < itensHud->Size(); i++)
	{
		if (Mymouse->itemDraging == itensHud->m_array[i])
		{
			if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, hudFase->spriteHud, hudFase->indiceHud, hudFase->xHud, hudFase->yHud))
			{
				itemdraging->ReturnPosition();
				return;
			}
			else
			{
				if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, resetButton->m_sprite, 0, resetButton->GetX(), resetButton->GetY()))
				{
					//colidiu lixeira
					itemdraging->ReturnPosition();
					return;					
				}

				// Testar se esta em cima de algum item da fase
				iterator_ItensFase = itensFase->GetIterator();
				while (iterator_ItensFase.Valid() == true)
				{
					if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, iterator_ItensFase.m_node->m_data->m_sprite, iterator_ItensFase.m_node->m_data->m_indice, iterator_ItensFase.m_node->m_data->m_x, iterator_ItensFase.m_node->m_data->m_y))
					{
						itemdraging->ReturnPosition();
						return;
					}
					iterator_ItensFase.Forth();
				}
				iterator_partesFase = partesFase->GetIterator();
				while (iterator_partesFase.Valid() == true)
				{
					if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, iterator_partesFase.m_node->m_data->m_sprite, iterator_partesFase.m_node->m_data->m_indice, iterator_partesFase.m_node->m_data->m_x, iterator_partesFase.m_node->m_data->m_y))
					{
						itemdraging->ReturnPosition();
						return;
					}
					iterator_partesFase.Forth();
				}
			}

			//SaveGame->SaveObject(itemdraging->Get_Name(), itemdraging->Get_X(), itemdraging->Get_Y()); // salva os objetos logo após ao solta-los
			itensFase->Append(new Item(itemdraging->m_nome, itemdraging->m_x + myCamera->m_x, itemdraging->m_y + myCamera->m_y)); // cria um item igual na fase na posição que foi solto

			itemdraging->ReturnPosition();
			// itemdraging->Drop();
			return;
		}
		else
		{
			if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, hudFase->spriteHud, hudFase->indiceHud, hudFase->xHud, hudFase->yHud))
			{
				itemdraging->ReturnPosition();
				return;
			}
			else
			{
				if (resetButton->GetFrame() == 1)
				{
					//colidiu lixeira

					iterator_ItensFase = itensFase->GetIterator();
					while (iterator_ItensFase.Valid() == true)
					{
						if (iterator_ItensFase.m_node->m_data == itemdraging)
						{
							itensFase->Remove(iterator_ItensFase);
							Mymouse->itemDraging = nullptr;
							return;
						}
						iterator_ItensFase.Forth();
					}
					resetButton->SetFrame(0);
				}
				iterator_ItensFase = itensFase->GetIterator();
				while (iterator_ItensFase.Valid() == true)
				{
					if (iterator_ItensFase.m_node->m_data != itemdraging)
					{
						if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, iterator_ItensFase.m_node->m_data->m_sprite, iterator_ItensFase.m_node->m_data->m_indice, iterator_ItensFase.m_node->m_data->m_x, iterator_ItensFase.m_node->m_data->m_y))
						{
							itemdraging->ReturnPosition();
							return;
						}
					}
					iterator_ItensFase.Forth();
				}
				iterator_partesFase = partesFase->GetIterator();
				while (iterator_partesFase.Valid() == true)
				{
					if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, iterator_partesFase.m_node->m_data->m_sprite, iterator_partesFase.m_node->m_data->m_indice, iterator_partesFase.m_node->m_data->m_x, iterator_partesFase.m_node->m_data->m_y))
					{
						itemdraging->ReturnPosition();
						return;
					}
					iterator_partesFase.Forth();
				}
			}
		}
	}
}