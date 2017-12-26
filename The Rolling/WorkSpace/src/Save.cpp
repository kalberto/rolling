#define _CRT_SECURE_NO_WARNINGS

#include "Save.h"


Save::Save()
{
	aux_keyboard = C2D2_PegaTeclas(); 
	x = 0;
	y = 0;
	FoiSobrescrito = false;
}


Save::~Save()
{
}

void Save::Update()
{
	if (aux_keyboard[C2D2_W].pressionado)
	{
		//SaveFile();
	}

	if (aux_keyboard[C2D2_R].pressionado)
	{
		//ReadFile();
	}

	if (aux_keyboard[C2D2_T].pressionado)
	{	
		SaveObject("Plataforma",10.5,1000);
		SaveObject("Catapulta", 230, 160);
	}
	
}

void Save::Run()
{
	Update();
}

bool Save::SaveFile()
{
		//gravar

		string teste2 = "\n ai meu deus \n yep";

		//strcat(p1,p2); // junta dois chares em um, colocando tudo no primeiro

		fp = fopen("./Save Files/save.gtx", "w");

		if (fp == NULL)
		{
			cout << endl << "Caminho para SALVAR os arquivos nao encontrado!";
			return false;
		}
		//fputs("teste", fp);
		fputs(teste2.c_str(), fp); // c_str() para eu "converter" a string em char
		fclose(fp);

		cout << "salvei!";	

	return true;
}

bool Save::ReadFile()
{
		char texto[100];

		char aux;

		fp = fopen("./Save Files/save.gtx", "r");
		if (fp == NULL)
		{
			cout << endl << "Caminho para LER os arquivos nao encontrado!";
			return false;
		}
			
		//fgets(texto, 100, fp);
		aux = fgetc(fp);
		strtok(texto, "/n");

		cout << aux;

	return true;
}

bool Save::ReadIsPassed(int p_level)
{
	string fileDirectory;

	char aux;
	if (p_level == 1)
	{
		fileDirectory = "./Save Files/level1ispassed.gtx";
		goto read;
	}


	if (p_level == 2)
	{
		fileDirectory = "./Save Files/level2ispassed.gtx";
		goto read;
	}

	if (p_level == 3)
	{
		fileDirectory = "./Save Files/level3ispassed.gtx";
		goto read;
	}

	if (p_level == 4)
	{
		fileDirectory = "./Save Files/level4ispassed.gtx";
		goto read;
	}

	if (p_level == 5)
	{
		fileDirectory = "./Save Files/level5ispassed.gtx";
		goto read;
	}

read:
	fp = fopen(fileDirectory.c_str(), "r");
	if (fp == NULL)
	{
		cout << endl << "Caminho para LER os arquivos nao encontrado!";
		return false;
	}

	aux = fgetc(fp);
	fclose(fp);

	if (aux == '1') // fase concluida!
		return true;

	else
		return false;
}

bool Save::SaveIsPassed(int p_level)
{
	string fileDirectory;

	if (p_level == 1)
	{
		fileDirectory = "./Save Files/level1ispassed.gtx";
		goto write;
	}


	if (p_level == 2)
	{
		fileDirectory = "./Save Files/level2ispassed.gtx";
		goto write;
	}

	if (p_level == 3)
	{
		fileDirectory = "./Save Files/level3ispassed.gtx";
		goto write;
	}

	if (p_level == 4)
	{
		fileDirectory = "./Save Files/level4ispassed.gtx";
		goto write;
	}

	if (p_level == 5)
	{
		fileDirectory = "./Save Files/level5ispassed.gtx";
		goto write;
	}

write:
	fp = fopen(fileDirectory.c_str(), "w");
	if (fp == NULL)
	{
		cout << endl << "Caminho para ESCREVER os arquivos nao encontrado!";
		return false;
	}

	fputc('1', fp);
	fclose(fp);

	return true;
}

bool Save::ReadObject(DlinkedList<Item*>* p_list)
{
	cout << endl << endl << endl << "------------------- Loading Objects -------------------" << endl << endl;

	int ArrayIndex = 0;
	int CursorIndex = 0;
	x = 0;
	y = 0;
	string str_x;
	string str_y;
	string str_name;

	string line;
	string TotalFile;
	string FileName = "level1.gtx";
	string FileDirectory = "./Save Files/" + FileName;
	string FileChar; // FileChar == TotalFile[CursorIndex]

	if (isFile(FileName) == false)
		return false;

	ifstream infile(FileDirectory);
	while (getline(infile, line)) // pegar todo o arquivo e por no TOTALFILE
	{
		istringstream iss(line);
		TotalFile += line + "\n";
	}

	FileChar = TotalFile[CursorIndex];
	while (FileChar != ".")// '.' == eof (pela minha convençâo)
	{
		while (FileChar != "<")
			CursorIndex++;

		if (FileChar == "<") // Início de Tag!
		{
			cout << endl << "Inicio de Tag!";
			while (FileChar != "X" || FileChar != "Y" || FileChar != "O")
			{
				CursorIndex++;
				FileChar = TotalFile[CursorIndex];
				if (FileChar == "X")
				{

					CursorIndex += 3;
					FileChar = TotalFile[CursorIndex]; // avançei até o inicio do num

					while (FileChar != "\n")
					{
						str_x += FileChar;
						CursorIndex++;
						FileChar = TotalFile[CursorIndex];
					}
					x = 0;
					x = atof(str_x.c_str());
					cout << endl << "Encontrado X: " << x;
					//p_array[ArrayIndex].Set_X(x);
				}

				if (FileChar == "Y")
				{
					CursorIndex += 3;
					FileChar = TotalFile[CursorIndex]; // avançei até o inicio do num

					while (FileChar != "\n")
					{
						str_y += FileChar;
						CursorIndex++;
						FileChar = TotalFile[CursorIndex];
					}
					y = 0;
					y = atof(str_y.c_str());
					cout << endl << "Encontrado Y: " << y;
					//p_array[ArrayIndex].Set_Y(y);
					p_list->Append(new Item(str_name, x, y));
					//ArrayIndex++;
				}

				if (FileChar == "O")
				{

					str_y.clear();
					str_x.clear();
					str_name.clear();

					CursorIndex += 8;
					FileChar = TotalFile[CursorIndex]; // avançei até o inicio do nome do objeto

					while (FileChar != "\n")
					{
						str_name += FileChar;
						CursorIndex++;
						FileChar = TotalFile[CursorIndex];
					}

					cout << endl << endl << "Encontrado Objeto: " << str_name;

					//p_array[ArrayIndex].Set_Name(str_name);	


				}

				if (FileChar == ".")
					goto fim;
			}
		}

		CursorIndex++;
		FileChar = TotalFile[CursorIndex];
	}
fim:
	cout << endl << "Fim do Arquivo de leutura!";
	cout << endl << endl << "------------- Finished Loading the Objects -------------" << endl << endl;
	return true;
}

bool Save::isFile(string p_FileName)
{
	string FileDirectory = "./Save Files/" + p_FileName;
	fp = fopen(FileDirectory.c_str(), "r");
	if (fp == NULL)
	{
		cout << endl << "Caminho para LER os arquivos nao encontrado!";
		return false;
	}
	fclose(fp);
	return true;
}

bool Save::PutEOF(string p_FileName)// '.' == EOF
{
	if (isFile(p_FileName) == false)
		return false;

	string FileDirectory = "./Save Files/" + p_FileName;
	fp = fopen( FileDirectory.c_str(), "a");
	fputs(".", fp); // c_str() para eu "converter" a string em char
	fclose(fp);
	return true;
}

bool Save::SaveObject(string p_ItemName, float p_X, float p_Y)
{
	string FileName = "level1.gtx";
	string FileDirectory = "./Save Files/" + FileName;

	if (FoiSobrescrito == false)
	{
		fp = fopen(FileDirectory.c_str(), "w");
		fclose(fp);

		FoiSobrescrito = true;
	}

	string Object = "<OBJECT> ";
	string X = "<X> ";
	string Y = "<Y> ";

	

	string m_ItemName = p_ItemName;

	stringstream x_stream; // stream usada para converter o int em str
	x_stream << p_X;
	string m_X = x_stream.str();;

	stringstream y_stream;
	y_stream << p_Y;
	string m_Y = y_stream.str();

	string FinalString = Object + m_ItemName + "\n" + X + m_X + "\n" + Y + m_Y + "\n\n";

	fp = fopen(FileDirectory.c_str(), "a"); // W sobrescreve | A adiciona ao final

	if (fp == NULL)
	{
		cout << endl << "Caminho para SALVAR os arquivos nao encontrado!";
		return false;
	}
	//fputs("teste", fp);
	fputs(FinalString.c_str(), fp); // c_str() para eu "converter" a string em char
	fclose(fp);

	cout << endl << "salvei!";

	return true;
}

void Save::OverwriteFile()
{
	FoiSobrescrito = false;
}

float Save::GetX()
{
	return x;
}

float Save::GetY()
{
	return y;
}

string Save::GetObjectName()
{
	return ObjectName;
}

