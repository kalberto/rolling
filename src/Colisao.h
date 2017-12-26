#include"Includes.h"
#include "Bola.h"

#define PI 3.14159265

bool CaixaBolinha(Bola* p_bola)
{
	for (int i = 0; i < 360; i++)
	{
		if (sqrt(2 * pow(p_bola->getRaio(), 2.0) - 2 * pow(p_bola->getRaio(), 2.0)*cos(i*PI / 180)) == 2)
		{
			return true;
		}
		else
			return false;
	}
}
