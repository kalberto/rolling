#pragma once
#include "Fase.h"

Fase::Fase()
{
	m_back = false;

	m_backgroung = C2D2_CarregaSpriteSet("Mundo/Imagens/background_f1.png", 1366, 768);
	//m_UpMask = m_DownMask = C2D2_CarregaSpriteSet("Mundo/Imagens/mask_f.png", 1366, 84);
	MyKeyborad = C2D2_PegaTeclas();
	SaveGame = new Save();
	Mymouse = new MyMouse();
	partesFase = new DlinkedList < Item* >();
	itensFase = new DlinkedList < Item* >();
	interator_ItensFase = itensFase->GetInterator();
	interator_partesFase = partesFase->GetInterator();
	itensHud = new Array < Item* >(10);
	m_bola = new Bola();
	Inicializa();
		itensHud->m_array[0] = new Item("plataforma", 50, 50);
		itensHud->m_array[1] = new Item("mola", 450, 15);
		itensHud->m_array[2] = new Item("plataforma", 5000, 50);
		itensHud->m_array[3] = new Item("plataforma", 5000, 50);
		itensHud->m_array[4] = new Item("plataforma", 5000, 50);
		itensHud->m_array[5] = new Item("plataforma", 5000, 50);
		itensHud->m_array[6] = new Item("plataforma", 5000, 50);
		itensHud->m_array[7] = new Item("plataforma", 5000, 50);
		itensHud->m_array[8] = new Item("plataforma", 5000, 50);
		itensHud->m_array[9] = new Item("plataforma", 5000, 50);

	hudFase = new Hud(itensHud);
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
	SaveGame->ReadObject(partesFase);
	cout << endl << "------------------ Fase Inicializada! ------------------" << endl << endl;
}

void Fase::Run()
{
	Update();
	Draw();
	Mymouse->Run();
	m_bola->Run();
}

void Fase::Update()
{
	if (MyKeyborad[C2D2_ESC].pressionado || MyKeyborad[C2D2_ENCERRA].pressionado)
	{
		m_back = true;

		cout << m_back;
	}if (Mymouse->itemDraging != nullptr)
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
				}
			}
		}
	}
	if (Mymouse->ButtonUp())
	{
		if (Mymouse->itemDraging != nullptr)
		{
			SoltarItem(Mymouse->itemDraging);
			Mymouse->itemDraging = nullptr;

		}
	}
	m_fisica.AplicaGravidadePF(m_bola, nullptr);

	

	interator_partesFase = partesFase->GetInterator();
	
	while (interator_partesFase.Valide() == true)
	{
		if (C2D2_ColidiuSprites(m_bola->getSprite(), 0, m_bola->getX(), m_bola->getY(), interator_partesFase.m_node->m_data->m_sprite, interator_partesFase.m_node->m_data->m_indice, interator_partesFase.m_node->m_data->m_x, interator_partesFase.m_node->m_data->m_y))
		{
			if (interator_partesFase.m_node->m_data->m_nome == "plataforma")
				m_fisica.AplicaGravidadePF(m_bola, interator_partesFase.m_node->m_data);
		}
		interator_partesFase.Forth();
	}

}

void Fase::Draw()
{
	C2D2_DesenhaSprite(m_backgroung, 0, 0, 0);

	C2D2_DesenhaSprite(m_UpMask, 0, 0, 0);
	C2D2_DesenhaSprite(m_DownMask, 0, 0, 684);

	hudFase->Draw(); // desenha os itens do Hud


	//Desenha itenhs da fase
	interator_ItensFase = itensFase->GetInterator();
	while (interator_ItensFase.Valide() == true)
	{
		interator_ItensFase.m_node->m_data->Draw();
		interator_ItensFase.Forth();
	}

	interator_partesFase = partesFase->GetInterator();
	while (interator_partesFase.Valide() == true)
	{
		interator_partesFase.m_node->m_data->Draw();
		interator_partesFase.Forth();
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
	/*  testa colisão com cada item do hud
	for (int i = 0; i < 10; i++)
	{
	if (itemdraging != itensHud->m_array[i])
	{
	if (C2D2_ColidiuSprites(itemdraging->sprite, itemdraging->indice, itemdraging->x, itemdraging->y, itensHud->m_array[i]->sprite, itensHud->m_array[i]->indice, itensHud->m_array[i]->x, itensHud->m_array[i]->y))
	{
	itemdraging->ReturnPosition();
	return;
	}
	}
	}
	*/
	if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, hudFase->spriteHud, hudFase->indiceHud, hudFase->xHud, hudFase->yHud))
	{
		itemdraging->ReturnPosition();
		return;
	}
	else
	{
		// Testar se esta em cima de algum item da fase
		interator_ItensFase = itensFase->GetInterator();
		while (interator_ItensFase.Valide() == true)
		{
			if (C2D2_ColidiuSprites(itemdraging->m_sprite, itemdraging->m_indice, itemdraging->m_x, itemdraging->m_y, interator_ItensFase.m_node->m_data->m_sprite, interator_ItensFase.m_node->m_data->m_indice, interator_ItensFase.m_node->m_data->m_x, interator_ItensFase.m_node->m_data->m_y))
			{
				itemdraging->ReturnPosition();
				return;
			}
			interator_ItensFase.Forth();
		}
	}

	//SaveGame->SaveObject(itemdraging->Get_Name(), itemdraging->Get_X(), itemdraging->Get_Y()); // salva os objetos logo após ao solta-los
	itensFase->Append(new Item(itemdraging->m_nome, itemdraging->m_x, itemdraging->m_y)); // cria um item igual na fase na posição que foi solto

	itemdraging->ReturnPosition();
	// itemdraging->Drop();
}