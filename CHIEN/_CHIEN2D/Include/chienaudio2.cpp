/*
ChienAudio 2.0

Copyright 2008-2010, Paulo Vinicius Wolski Radtke (pvwradtke@gmail.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

// Includes da biblioteca
#include <stdio.h>
#include <string.h>
#include <./chienaudio2.h>

// Vari�vel que indica a tela do sistema
extern SDL_Surface *screen;
// A largura da tela
int lTela=-1;


// Fun��o de uso exclusivo da biblioteca. O programador n�o deve NUNCA utiliz�-la
void CA2_Reset();

// �rea de vari�veis globais do programa
// indica se a Chien Audio 2 j� foi inicializada. Por default, n�o foi ainda.
bool CA2_inicializado = false;
// A m�sica sendo tocada no momento, nula no in�cio
unsigned int musica = 0;
// Os volumes dos efeitos e m�sica
unsigned int volMusica = 100;
unsigned int volEfeitos = 100;
// O vetor de efeitos sonoros
CA2_Efeito efeitos[CA2_MAX_EFEITOS];
// O vetor de m�sicas
CA2_Musica musicas[CA2_MAX_MUSICAS];

// Fun��o de uso exclusivo da biblioteca. O programador n�o deve NUNCA utiliz�-la
//
// Data: 02/02/2008

void CA2_Reset()
{
	// Volume no m�ximo inicialmente
	volMusica = 100;
	volEfeitos = 100;
	// N�o est� tocando nenhuma m�sica
	musica=0;
    // Zera as estruturas de m�sica e efeitos
	for(int i=0;i<CA2_MAX_EFEITOS;i++)
    {
        efeitos[i].usuarios = 0;
        strcpy(efeitos[i].apelido, "");
		efeitos[i].efeito= 0;
		efeitos[0].tempo=0;
    }
	for(int i=0;i<CA2_MAX_MUSICAS;i++)
    {
        musicas[i].usuarios = 0;
        strcpy(musicas[i].apelido, "");
		musicas[i].musica = 0;
		musicas[i].tempo=0;
    }
}

// Fun��o que inicia a Chien Audio 2. Caso o sistema j� esteja inicializado, retorna verdade. Caso contr�riom, inicia e
// retorna um valor booleano de acordo com o sucesso (true) ou falha (false).
//
// Data: 02/02/2007

bool CA2_Inicia()
{
	// Testa se j� inicializou ou n�o
	if(CA2_inicializado)
		return true;
	// Limpa as vari�veis
	CA2_Reset();
    // Testa se j� foi inicializado o v�deo (se n�o foi, cai fora!)
    if(SDL_WasInit(SDL_INIT_AUDIO))
        return false;
    // Inicia a parte de �udio da SDL
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) 
    {        
		printf("N�o conseguiu iniciar a Chien Audio 2 (subseistema SDL). Erro do sistema: %s\n", SDL_GetError());
        return false;
    }
    // Abre o sistema de mixagem
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, CA2_BUFFER_MIXER) < 0)
    {
        // Fecha o �udio da SDL
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    	printf("N�o conseguiu iniciar a Chien Audio 2 (formato de �udio). Erro do sistema: %s\n", SDL_GetError());
    	return false;
   	}
	// Indica que est� inicializado e retorna
	CA2_inicializado = true;
	// Ajusta o volume no m�ximo (default)
	CA2_AjustaVolume(100, 100);
	lTela = screen->w;
	return true;
}

// Fun��o que encerra a Chien2D 2
//
// Data: 02/02/2008

void CA2_Encerra()
{
	// Se n�o inicializou, pula fora!
	if(!CA2_inicializado)
		return;
    // Encerra a m�sica atual
    if(Mix_PlayingMusic())
    {
        Mix_HaltMusic();
        musica = 0;
    }
    // P�ra todos os efeitos sonoros
    Mix_HaltChannel(-1);
    // Apaga todos os efeitos
	for(int i=0;i<CA2_MAX_EFEITOS;i++)
        CA2_RemoveEfeito(i+1);
    // Apaga as m�sicas
	for(int i=0;i<CA2_MAX_MUSICAS;i++)
        CA2_RemoveMusica(i+1);
    // Fecha o sistema de mixagem
    Mix_CloseAudio();
    // Fecha o �udio da SDL
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    // Indica que acabou
    CA2_inicializado = false;
}

// Fun��o para sincronizar o �udio ???
//
// Data: 02/02/2008

void CA2_Sincroniza()
{

}

// Fun��o que ajusta o volume dos efeitos e m�sicas no sistema
//
// Data: 02/02/2008

bool CA2_AjustaVolume(unsigned int musica, unsigned int efeitos)
{
	// Testa se est� inicializado
	if(!CA2_inicializado)
	{
		printf("Aten��o: tentativa de mudar o volume do �udio sem iniciar o sistema de �udio!\n");
		return false;
	}
	// Calcula o valor dos volumes entre 0 e 100
	if(musica > 100)
		volMusica = 100;
	else
		volMusica = musica;
	if(efeitos > 100)
		volEfeitos = 100;
	else
		volEfeitos = efeitos;
	// Ajusta o volume dos canais
	Mix_Volume(-1,(volEfeitos*MIX_MAX_VOLUME)/100);
	Mix_VolumeMusic((volMusica*MIX_MAX_VOLUME)/100);
	return true;
}

// Fun��es para manipular efeitos sonoros

// fun��o para carregar um efeito na mem�ria
//
// Data: 02/02/2008

unsigned int CA2_CarregaEfeito(const char *arquivo)
{
    // Verifica se o efeito n�o existe j�
	unsigned int idx =  CA2_ProcuraEfeito(arquivo);
    // Se j� existe um efeito com o apelido, retorna o �ndice associado e aumenta
    // o n�mero de usu�rios do mesmo
    if(idx != 0)
    {
        efeitos[idx-1].usuarios++;
        return idx;
    }
        
    // Se n�o existe, procura o primeiro �ndice vago (idx ainda � igual a 0)
	for(int i=0;i<CA2_MAX_EFEITOS;i++)
        // O efeito � vago (n�o tem audio associado?
		if(efeitos[i].efeito == 0)
        {
            idx=i+1;
            break;
        }
    
    // Testa se ainda tem espa�o na lista
    //
    // ATEN��O: n�o ter espa�o na mem�ria n�o � relacionado a este teste. Apenas
    // testa-se aqui se existe um �ndice vago na lista. Se n�o existe, idx==0
    if(idx==0)
	{
		printf("Estourou o limite de efeitos sonoros carregados no sistema. \n");
        // Retorna um �ndice inv�lido para indicar que o m�todo falhou
        return 0;
	}
    
    // Se chegou at� aqui, idx cont�m o identificador correto 
    // Calcula a posi��o no array (sem incrementar 1)
    idx=idx-1;    
    // Carrega o efeito propriamente dito
    efeitos[idx].efeito = Mix_LoadWAV(arquivo);
    // Se falhou, volta
    if(efeitos[idx].efeito == 0)
    {
        printf("Erro ao carregar o arquivo %s.\n", arquivo);
        return 0;
    }
    // Indica o apelido
    strcpy(efeitos[idx].apelido, arquivo);
    printf("Carregou o efeito %s.\n", arquivo);
    // Indica que tem um usu�rio
    efeitos[idx].usuarios++;
    // REtorna o �ndice real
    return idx+1;
}

// Remove um efeito da mem�ria
//
// Data: 02/02/2008

void CA2_RemoveEfeito(unsigned int id)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_EFEITOS || id == 0)
        return;
    // S� remove efetivamente se tiver apenas um usu�rio 
    if(efeitos[id-1].usuarios > 1)
        efeitos[id-1].usuarios--;
	else 
    {
		// Just in case, testa antes de remover
		if(efeitos[id-1].efeito != 0)
			Mix_FreeChunk(efeitos[id-1].efeito);
        efeitos[id-1].efeito = 0; 
		// Indica apelido vazio
        strcpy(efeitos[id-1].apelido, "");
		// Zera o n�mero de usu�rios
		efeitos[id-1].usuarios = 0;
    }   
}

// Procura um efeito pelo nome do arquivo original
//
// Data: 02/02/2008

unsigned int CA2_ProcuraEfeito(const char *apelido)
{
    // �ndice de efeito inv�lido, caso n�o encontre
    unsigned int idx=0;
	for(int i=0;i<CA2_MAX_EFEITOS;i++)
        if(strcmp(efeitos[i].apelido, apelido)==0)
        {
            // O �ndice � a posi��o atual + 1
            idx=i+1;
            // Encerra a busca
            break;
        }
    return idx;
}

// Fun��o para tocar um efeito. -100 � um som � esquerda e 100 � direita. 0 para centro.
// Se funcionar, retorna o canal em que o som est� tocando. Caso contr�rio, retorna 0
//
// Data: 02/02/2008

int CA2_TocaEfeito(unsigned int id, int posicao)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_EFEITOS || id == 0)
        return 0;
    // Verifica se o efeito existe
    if(efeitos[id-1].efeito != 0)
	{
		// Ajusta o volume, se necess�rio
		if(posicao<CA2_ESQUERDA)
			posicao = CA2_ESQUERDA;
		else if(posicao>CA2_DIREITA)
			posicao = CA2_DIREITA;
		// Calcula o volume para cada canal. Por default, consideramos que ambos est�o no m�ximo

		int esquerda, direita;
		// 254 � o volume m�ximo de um canal. Assim, centro indica 127 em CADA canal. Som em um canal s� indica 254 apenas em um canal
		esquerda = ((100-posicao)*254)/200;
		direita = ((100+posicao)*254)/200;
        int canal = Mix_PlayChannel(-1,efeitos[id-1].efeito,0);
        Mix_SetPanning(canal, esquerda, direita);
		return canal;
	}
    return 0;
}

// Fun��o para tocar um efeito em loop
//
// Data: 30/01/2011
//
int CA2_TocaEfeitoLoop(unsigned int id, int posicao, int loop)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_EFEITOS || id == 0)
        return 0;
    // Verifica se o efeito existe
    if(efeitos[id-1].efeito != 0)
	{
		// Ajusta o volume, se necess�rio
		if(posicao<CA2_ESQUERDA)
			posicao = CA2_ESQUERDA;
		else if(posicao>CA2_DIREITA)
			posicao = CA2_DIREITA;
		// Calcula o volume para cada canal. Por default, consideramos que ambos est�o no m�ximo

		int esquerda, direita;
		// 254 � o volume m�ximo de um canal. Assim, centro indica 127 em CADA canal. Som em um canal s� indica 254 apenas em um canal
		esquerda = ((100-posicao)*254)/200;
		direita = ((100+posicao)*254)/200;
        int canal = Mix_PlayChannel(-1,efeitos[id-1].efeito,loop);
        Mix_SetPanning(canal, esquerda, direita);
		return canal;
	}
    return 0;

}


// Fun��o para tocar um efeito posicional baseado na coordenada x na tela

// Se funcionar, retorna o canal em que o som est� tocando. Caso contr�rio, retorna 0
//
// Data: 02/02/2008

int CA2_TocaEfeitoTela(unsigned int id, int posicao)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_EFEITOS || id == 0)
        return 0;
    // Verifica se o efeito existe
    if(efeitos[id-1].efeito != 0)
	{

		// Ajusta a posi��o se necess�rio
		if(posicao<0)
			posicao=0;
		else if(posicao > lTela)
			posicao = lTela;
		// Calcula o volume para cada canal. Por default, consideramos que ambos est�o no m�ximo
		int esquerda, direita;
		posicao = (200*posicao)/800 - 100;
		// 254 � o volume m�ximo de um canal. Assim, centro indica 127 em CADA canal. Som em um canal s� indica 254 apenas em um canal
		esquerda = ((100-posicao)*254)/200;
		direita = ((100+posicao)*254)/200;
        int canal = Mix_PlayChannel(-1,efeitos[id-1].efeito,0);
        Mix_SetPanning(canal, esquerda, direita);
		return canal;	
	}
	return 0;
}

// Fun��o para cortar o efeito tocando em um canal
//
// Data: 30/01/2011
//
int CA2_CortaEfeito(int canal, int tempo)
{
	return Mix_FadeOutChannel(canal, tempo);
}


// Fun��o para pausar a reprodu��o de efeitos sonoros
//
// Data: 02/02/2008

void CA2_PausaEfeitos()
{
	Mix_Pause(-1);
}

// Fun��o para continuar a reprodu��o de efeitos sonoros (ap�s pausa)
//
// Data: 02/02/2008

void CA2_ContinuaEfeitos()
{
	Mix_Resume(-1);
}

// Fun��es para manipular m�sicas

// fun��o para carregar um efeito na mem�ria
//
// Data: 02/02/2008

unsigned int CA2_CarregaMusica(const char *arquivo)
{
    // Verifica se a m�sica n�o existe j�
	unsigned int idx =  CA2_ProcuraMusica(arquivo);
    // Se j� existe um efeito com o apelido, retorna o �ndice associado e aumenta
    // o n�mero de usu�rios do mesmo
    if(idx != 0)
    {
		musicas[idx-1].usuarios++;
        return idx;
    }
        
    // Se n�o existe, procura o primeiro �ndice vago (idx ainda � igual a 0)
	for(int i=0;i<CA2_MAX_MUSICAS;i++)
        // O efeito � vago (n�o tem audio associado?
		if(musicas[i].musica == 0)
        {
            idx=i+1;
            break;
        }
    
    // Testa se ainda tem espa�o na lista
    //
    // ATEN��O: n�o ter espa�o na mem�ria n�o � relacionado a este teste. Apenas
    // testa-se aqui se existe um �ndice vago na lista. Se n�o existe, idx==0
    if(idx==0)
	{
		printf("Estourou o limite de m�sicas carregadas no sistema. \n");
        // Retorna um �ndice inv�lido para indicar que o m�todo falhou
        return 0;
	}
    
    // Se chegou at� aqui, idx cont�m o identificador correto 
    // Calcula a posi��o no array (sem incrementar 1)
    idx=idx-1;    
    // Carrega o efeito propriamente dito
	musicas[idx].musica = Mix_LoadMUS(arquivo);
    // Se falhou, volta
    if(musicas[idx].musica == 0)
    {
        printf("Erro ao carregar o arquivo %s.\n", arquivo);
        return 0;
    }
    // Indica o apelido
    strcpy(musicas[idx].apelido, arquivo);
    printf("Carregou a m�sica %s.\n", arquivo);
    // Indica que tem um usu�rio
    musicas[idx].usuarios++;
    // REtorna o �ndice real
    return idx+1;
}

// Remove uma m�sica da mem�ria
//
// Data: 02/02/2008

void CA2_RemoveMusica(unsigned int id)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_MUSICAS || id == 0)
        return;
    // S� remove efetivamente se tiver apenas um usu�rio 
    if(musicas[id-1].usuarios > 1)
        musicas[id-1].usuarios--;
	else 
    {
		// Just in case, testa antes de remover
		if(musicas[id-1].musica != 0)
			Mix_FreeMusic(musicas[id-1].musica);
        musicas[id-1].musica = 0; 
		// Indica apelido vazio
        strcpy(musicas[id-1].apelido, "");
		// Zera o n�mero de usu�rios
		musicas[id-1].usuarios = 0;
    }   

}

// Procura uma m�sica pelo nome do arquivo original
//
// Data: 02/02/2008

unsigned int CA2_ProcuraMusica(const char *apelido)
{
    // �ndice de m�sica inv�lida, caso n�o encontre
    unsigned int idx=0;
	for(int i=0;i<CA2_MAX_MUSICAS;i++)
        if(strcmp(musicas[i].apelido, apelido)==0)
        {
            // O �ndice � a posi��o atual + 1
            idx=i+1;
            // Encerra a busca
            break;
        }
    return idx;

}

// Fun��o para tocar uma m�sica
//
// Data: 02/02/2008

bool CA2_TocaMusica(unsigned int id, int vezes)
{
    // O efeito � v�lido?
	if(id > CA2_MAX_MUSICAS || id == 0)
        return 0;
    // Verifica se o efeito existe
    if(musicas[id-1].musica != 0)
	{
		// Ajusta as vezes se necess�rio no caso de loop infinito incorreto
		if(vezes < -1)
			vezes=-1;
		if(Mix_PlayMusic(musicas[id-1].musica, vezes))
			return false;
		return true;
	}
    return false;

}

// Fun��o para pausar a reprodu��o da m�sica
//
// Data: 02/02/2008

void CA2_PausaMusica()
{
	Mix_PauseMusic();
}

// Fun��o para continuar a reprodu��o da m�sica (ap�s pausa)
//
// Data: 02/02/2008

void CA2_ContinuaMusica()
{
	Mix_ResumeMusic();
}

// Fun��o para encerrar a reprodu��o da m�sica (fade)
//
// Data: 02/02/2008

void CA2_FadeMusica(unsigned int tempo)
{
	Mix_FadeOutMusic(tempo);
}
