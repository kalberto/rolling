#include "LevelEditor.h"

LevelEditor::LevelEditor(int p_level)
{
	m_level = p_level;
	m_back = false;

	MyKeyborad = C2D2_PegaTeclas();
	SaveGame = new Save();
	Mymouse = new MyMouse();
	partesFase = new DLinkedList < Item* >();
	itensFase = new DLinkedList < Item* >();
	interator_ItensFase = itensFase->GetIterator();
	interator_partesFase = partesFase->GetIterator();
	itensHud = new Array < Item* >(10);
	saveButton = new SaveButton(1100, 700);
	resetButton = new ResetLevelButton(50, 680);

	m_bg = new Background("fase1");
	myCamera = new Camera;

	Inicializa();
	itensHud->m_array[0] = new Item("plataforma", 20, -10);
	itensHud->m_array[1] = new Item("mola", 250, 50);
	itensHud->m_array[2] = new Item("plataforma", 5000, 0);
	itensHud->m_array[3] = new Item("plataforma", 5000, 0);
	itensHud->m_array[4] = new Item("plataforma", 5000, 0);
	itensHud->m_array[5] = new Item("plataforma", 5000, 0);
	itensHud->m_array[6] = new Item("plataforma", 5000, 0);
	itensHud->m_array[7] = new Item("plataforma", 5000, 0);
	itensHud->m_array[8] = new Item("plataforma", 5000, 0);
	itensHud->m_array[9] = new Item("plataforma", 5000, 0);
	hudFase = new Hud(itensHud);

	sprite_pressf1 = C2D2_CarregaSpriteSet("Mundo/Imagens/f1toplay.png", 357, 30);
	x_pressf1 = 300;
	y_pressf1 = 150;
	isBola = false;
	isPrintBola = false; // quando eu apertar uma vez f1, sempre estarei printando a bola!

	

	mouseButtonDown = false;
	bolaFoiClicada = false;
}

LevelEditor::~LevelEditor()
{
	delete Mymouse;
	delete MyKeyborad;
	delete partesFase;
	delete itensHud;
	delete itensFase;
	delete hudFase;
	delete SaveGame;
}

void LevelEditor::Inicializa()
{
	SaveGame->ReadObject2(partesFase,m_level);
	cout << endl << "------------------ Fase Inicializada! ------------------" << endl << endl;
}

void LevelEditor::Run()
{
	Update();
	m_bg->Run();
	Draw();
	resetButton->Run();
	saveButton->Run();
	myCamera->Move(MyKeyborad, m_bg);
	Mymouse->Run(myCamera->m_x, myCamera->m_y);	
}

void LevelEditor::Update()
{
	mouseButtonDown = false;
	if (Mymouse->OnButtonDown())
	{
		mouseButtonDown = true;
	}


	if (MyKeyborad[C2D2_ESC].pressionado || MyKeyborad[C2D2_ENCERRA].pressionado)
	{
		m_back = true;

		cout << m_back;
	}

	if (Mymouse->itemDraging != nullptr)
		Mymouse->itemDraging->Update();


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
			interator_partesFase = partesFase->GetIterator();
			while (interator_partesFase.Valid() == true)
			{
				if (Mymouse->ItemIsClicked(interator_partesFase.m_node->m_data))
				{
					Mymouse->itemDraging = interator_partesFase.m_node->m_data;
					Mymouse->itemDragingInFase = true;
					break;
				}
				interator_partesFase.Forth();
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

	if (Mymouse->ObjectIsClicked(saveButton->GetX(), saveButton->GetY(), saveButton->GetW(), saveButton->GetH()) == true) // clicar no botão save
	{
		interator_partesFase = partesFase->GetIterator();
		SaveGame->CleanFile(m_level);
		while (interator_partesFase.Valid() != 0)
		{
			SaveGame->SaveObject2(interator_partesFase.m_node->m_data->getName(), interator_partesFase.m_node->m_data->getX(), interator_partesFase.m_node->m_data->getY(), interator_partesFase.m_node->m_data->getAngulo(), m_level);
			cout << endl << "X: " << interator_partesFase.m_node->m_data->getX();
			cout << endl << "Y: " << interator_partesFase.m_node->m_data->getY();
			cout << endl << "Angulo: " << interator_partesFase.m_node->m_data->getAngulo();
			interator_partesFase.Forth();
		}
		SaveGame->PutEOF(m_level);
	}

	if (MyKeyborad[C2D2_I].pressionado)// infos da lista ligada
	{
		interator_partesFase = partesFase->GetIterator();
		cout << endl << "---------- LIST INFO ----------";
		while (interator_partesFase.Valid() != 0)
		{
			cout << endl << "X: " << interator_partesFase.m_node->m_data->getX();
			cout << endl << "Y: " << interator_partesFase.m_node->m_data->getY();
			cout << endl << "Angulo: " << interator_partesFase.m_node->m_data->getAngulo();
			cout << endl;
			interator_partesFase.Forth();
		}
		cout << endl;
	}

	if (MyKeyborad[C2D2_F1].pressionado)
	{
		if (isBola == false)
		{
			isBola = true;
			m_bola = new Bola(300, 300);
		}

		else if (isBola == true)
		{
			m_bola = new Bola(300, 300);
			isBola = false;
		}

		isPrintBola = true;
	}




	if (partesFase->m_count >= 1)
	{
		if (MyKeyborad[C2D2_X].pressionado && partesFase->m_tail->m_data->getName() == "plataforma")
		{
			partesFase->m_tail->m_data->rotPlat();

		}
	}

	// ANIM LIXEIRA
	if (Mymouse->MouseIsOverlapping(resetButton->GetX(), resetButton->GetY(), resetButton->GetW(), resetButton->GetH()))
		resetButton->SetFrame(1);
	else
		resetButton->SetFrame(0);
	//### ANIM LIXEIRA


	// LIXEIRA LIMPA FASE
	if (resetButton->GetFrame() == 1) // Mouse em cima da lixeira
	{
		bool Cleaned = false;

		if (Mymouse->OnAnyClick() && Cleaned == false)
		{
			while (partesFase->m_count >= 1)
				partesFase->RemoveTail();

			Cleaned = true;
		}
	}

	// LIXEIRA LIMPA FASE


	if (isBola && Mymouse->OnButtonDown() == false)
	{
		m_fisica.Aplicagravidade(m_bola); // se clicar play ai sim aplic a gravidade
		m_fisica.Setarcair(true);

		cout << "aplicando gravidade!";
	}



	if (isBola == true && Mymouse->OnButtonDown() == false) //             TESTAR COLISAO DA BOLA COM AS PLATAFORMAS QUANDO APERTAR F1
	{

		interator_partesFase = partesFase->GetIterator();
		while (interator_partesFase.Valid() == true) //  && !Mymouse->OnButtonDown()
		{
			if (C2D2_ColidiuSprites(m_bola->getSprite(), 0, m_bola->getX(), m_bola->getY(), interator_partesFase.m_node->m_data->m_sprite, interator_partesFase.m_node->m_data->m_indice, interator_partesFase.m_node->m_data->m_x, interator_partesFase.m_node->m_data->m_y))
			{
				if (interator_partesFase.m_node->m_data->m_nome == "plataforma")
					m_fisica.FisicaBolaPlat(m_bola, interator_partesFase.m_node->m_data);
				if (interator_partesFase.m_node->m_data->m_nome == "mola")
					m_fisica.AplicaForçaMola(m_bola, interator_partesFase.m_node->m_data);

				break;
			}
			cout << "Percorrendo lista!";
			interator_partesFase.Forth();
		}
					
		
	}

	if (isBola)
	{
		if (Mymouse->OnButtonDown() && C2D2_ColidiuSprites(m_bola->getSprite(), 0, m_bola->getX() - myCamera->m_x, m_bola->getY() - myCamera->m_y, Mymouse->getSprite(), 0, Mymouse->GetX(), Mymouse->GetY()))
		{
			bolaFoiClicada = true;
		}

		if (bolaFoiClicada == true)
		{
			m_bola->setX(Mymouse->GetX() + myCamera->m_x);
			m_bola->setY(Mymouse->GetY() + myCamera->m_y);
			m_bola->setVeloX(0);
			m_bola->setVeloY(0);
			m_bola->setSpeed(0);
		}
		if (bolaFoiClicada == true && Mymouse->ButtonUp())
		{
			bolaFoiClicada = false;
		}
	}
	
}

void LevelEditor::Draw()
{

	
	interator_partesFase = partesFase->GetIterator();
	while (interator_partesFase.Valid() == true)
	{
		interator_partesFase.m_node->m_data->Draw(myCamera->m_x, myCamera->m_y);
		interator_partesFase.Forth();
	}

	if (isPrintBola)
	{
		m_bola->Run(myCamera->m_x, myCamera->m_y);
	}
	hudFase->Draw();
	

	C2D2_DesenhaSprite(sprite_pressf1, 0, x_pressf1, y_pressf1);
}

void LevelEditor::AddItensFase(Item item_solto)
{
	itensFase->Append(new Item(item_solto));
}

void LevelEditor::AddPartesFase(Item item_solto)
{
	partesFase->Append(new Item(item_solto));
}

void LevelEditor::SoltarItem(Item* itemdraging)
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
					itemdraging->ReturnPosition();
					return;
				}
				// Testar se esta em cima de algum item da fase
				
			}

			//SaveGame->SaveObject(itemdraging->Get_Name(), itemdraging->Get_X(), itemdraging->Get_Y()); // salva os objetos logo após ao solta-los
			partesFase->Append(new Item(itemdraging->m_nome, itemdraging->m_x + myCamera->m_x, itemdraging->m_y + myCamera->m_y)); // cria um item igual na fase na posição que foi solto
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
				if (resetButton->GetFrame() == 1){

					//colidiu lixeira

					interator_partesFase = partesFase->GetIterator();
					while (interator_partesFase.Valid() == true)
					{
						if (interator_partesFase.m_node->m_data == itemdraging)
						{
							partesFase->Remove(interator_partesFase);
							Mymouse->itemDraging = nullptr;
							return;
						}
						else
						{
							interator_partesFase.Forth();
						}
					}
					resetButton->SetFrame(0);

					
				}

			}
		}
	}
	
}

//so pra dar checkin