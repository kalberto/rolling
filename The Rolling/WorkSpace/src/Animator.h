void Animador(int* p_frameCount,int * p_spriteFrame,float p_SegundossPorFrame)
{
	// SPF 1
	float aux = 60 * p_SegundossPorFrame;
	int aux2 = aux;
	if (*p_frameCount % aux2 == 0)
	{					
		*p_spriteFrame += 1;
		if (*p_spriteFrame == 6)
		{
			*p_spriteFrame = 0;
		}
		
	}

	*p_frameCount+= 1;
}