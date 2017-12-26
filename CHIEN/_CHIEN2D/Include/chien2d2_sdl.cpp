/*

Chien 2D 2.0 SDL Renderer

Copyright 2007-2010, Paulo Vinicius Wolski Radtke (pvwradtke@gmail.com)

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

/**
	Data original: 12/06/20 08

	Hist�rico de altera��es:

	Data       Programador      Altera��o
	========== ================ ======================================================================
	12/08/2010 Paulo Radtke	    Inclus�o do callback do usu�rio durante a sincroniza��o.

**/


// Includes padr�o do C
#include <stdlib.h>
#include <string.h>

// Inclui o header do arquivo (sem coment�rios)
#include <./chien2d2.h>
#include <./chien2d2_interno.h>
#include <./chien2d2_sdl.h>

// Vari�vel externa para a fun��o de callback do usu�rio durante a sincroniza��o
extern void (*C2D2_SincronizaUsuario)();

// A cor que usa para limpar a tela
Uint32 clearColor = 0;

// Fun��es da Chien2D 2


bool C2D2SDL_Inicia(unsigned int largura, unsigned int altura, 
        int modoVideo, char *tituloJanela)
{
    if(inicializado)
        return false; 
	else
		reset();

    // Testa se j� foi inicializado o v�deo (se foi, cai fora!)
    if(SDL_WasInit(SDL_INIT_VIDEO))
        return false;

	// Indica que n�o est� em shutdown
	c_shutdown = false;

    // Inicia o v�deo
	if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 ) 
    {
        printf("A Chien2D 2 n�o conseguiu iniciar a SDL. Mensagem do sistema: %s\n", 
                SDL_GetError());
        return false;
    }

    // Imprime informa��o do modo de v�deo requisitado
    printf("Iniciando o modo de v�deo: %ix%ix32bpp\n", largura, altura);
    
    // Flags do modo de v�deo (se ficar assim, roda em janela)
    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF; // | SDL_SRCALPHA;
    // Se for rodar em tela cheia, tem que colocar um flag a mair
	switch(modoVideo)
	{
	case C2D2_JANELA:
		printf("A aplica��o requisitou um modo de v�deo em janela.\n");
		break;
	case C2D2_TELA_CHEIA:
		printf("A aplica��o requisitou um modo de v�deo em tela cheia.\n");
		flags |= SDL_FULLSCREEN;
		break;
	default:
		printf("A aplica��o requisitou um modo de v�deo inv�lido. Por seguran�a, ser� utilizado um modo em janela.\n");
		break;
	}

	printf("A Chien2DLite vai verificar a disponibilidade do modo de v�deo requisitado.\n");
    
    if(SDL_VideoModeOK(largura, altura, 32, flags) ) 
    {
        printf("O sistema indica que o modo � suportado. Tenta iniciar.\n"); 
        
        // Inicia o modo de v�deo e recupera a surface (diferente de 0 se tudo ok)
        screen = SDL_SetVideoMode(largura, altura, 32,  flags);
        if ( screen == 0 ) 
        {
            printf("N�o foi poss�vel iniciar o modo de v�deo requisitado. Encerrando.");
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            return false;
        }
    }
    else
    {
        printf("O modo de v�deo n�o � suportado pelo hardware. Encerrando.");; 
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }
    printf("Modo de v�deo iniciado com sucesso!\n");

    // Coloca o nome na janela
    SDL_WM_SetCaption(tituloJanela, 0);
    // Desabilita o cursor do mouse
    SDL_ShowCursor(SDL_DISABLE);
  
	// Preenche os ponteiros de fun��o
	C2D2_Encerra = &C2D2SDL_Encerra ;
	C2D2_Sincroniza = &C2D2SDL_Sincroniza;
	C2D2_LimpaTela = &C2D2SDL_LimpaTela;
	C2D2_TrocaCorLimpezaTela=C2D2SDL_TrocaCorLimpezaTela;
	C2D2_LimitaAreaDesenho=&C2D2SDL_LimitaAreaDesenho;
	C2D2_LiberaAreaDesenho=&C2D2SDL_LiberaAreaDesenho;
	C2D2_CarregaSpriteSet=&C2D2SDL_CarregaSpriteSet;
	C2D2_RemoveSpriteSet=&C2D2SDL_RemoveSpriteSet;
	C2D2_DesenhaSprite=&C2D2SDL_DesenhaSprite;
	C2D2_DesenhaSpriteEfeito = &C2D2SDL_DesenhaSpriteEfeito;

    // Indica que foi iniciado e pula fora
    inicializado=true;
    return true;
}


// Fun��o que encerra a Chien2D 2
//
// Data: 29/03/2007

void C2D2SDL_Encerra()
{
    // Testa por via das d�vidas para n�o ter problemas
    if(!inicializado)
        return;
    // Indica que est� encerrando
    c_shutdown = true;
        
    printf("Apagando os spritesets e fontes do sistema.\n");

    // Apaga as fontes
    for(int i=0;i<C2D2_MAX_FONTES;i++)
        C2D2_RemoveFonte(i+1);

    // Apaga os sprite sets
    for(int i=0;i<C2D2_MAX_SPRITESET;i++)
        C2D2_RemoveSpriteSet(i+1);

    printf("Encerrando a SDL.\n");
    // Encerra o v�deo
    if(screen != 0)
        SDL_FreeSurface(screen);        
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    printf("Encerrou a SDL.\n");
    
    inicializado=false;
}


// Fun��o para sincronizar o v�deo a 60ppfps
//
// Data: 13/04/2007
//
// Altera��o:
//	12/08/2010	Paulo Radtke	Chamada do callback do usu�rio.
//
void C2D2SDL_Sincroniza(Uint8 fps)
{
    // Inicializa e pega o tempo atual (s� faz isso a primeira vez)
    static Uint32 tempoAnterior=0;

    // Chama a fun��o de sincroniza��o do usu�rio
    if(C2D2_SincronizaUsuario != 0)
        C2D2_SincronizaUsuario();

	// Verifica se o par�metro � v�lido
	if (fps <= 0) fps = 1;

    // -- Espera 16ms entre cada quadro --	
    // Vari�vel para o tempo atual
    int espera=(1000/fps)-SDL_GetTicks()+tempoAnterior;
    if(espera > 0)
       SDL_Delay(espera);
    tempoAnterior=SDL_GetTicks();

    // Troca os buffers
    SDL_Flip(screen);
    // Atualiza as entradas
    C2D2_Entrada();
}

// Fun��o para limpar a tela
//
// Data: 13/04/2007
//
void C2D2SDL_LimpaTela()
{
	SDL_FillRect(screen, 0, clearColor);
}

// Fun��o para escolher a cor de limpeza da tela
//
// Data: 13/04/2007
//
void C2D2SDL_TrocaCorLimpezaTela(Uint8 r, Uint8 g, Uint8 b)
{
	clearColor = SDL_MapRGB(screen->format, r, g, b);
}

// Fun��o para limitar a �rea de desenho da tela
//
// Data: 16/08/2007
//
void C2D2SDL_LimitaAreaDesenho(int x, int y, int largura, int altura)
{
	// Pega a surface da tela
	SDL_Surface *tela = SDL_GetVideoSurface();	
	// Prepara o ret�ngulo de cliping
	SDL_Rect rect;
	rect.x=x;
	rect.y=y;
	rect.w=largura;
	rect.h=altura;
	// Clipa!
	SDL_SetClipRect(tela, &rect);
}

// Fun��o para eliminar o limite da �rea de desenho
//
// Data: 16/08/2007
//
void C2D2SDL_LiberaAreaDesenho()
{
	// Pega a surface da tela
	SDL_Surface *tela = SDL_GetVideoSurface();	
	// Remove o clipping
	SDL_SetClipRect(tela, 0);
}




//////////////////////////////////
// Fun��es para manipular sprites
//////////////////////////////////

// fun��o para carregar um sprite set na mem�ria
//
// Data: 13/04/2007
//
unsigned int C2D2SDL_CarregaSpriteSet(const char *arquivo, int largura, int altura)
{
    // Verifica se o spriteset n�o existe j�
    unsigned int idx = C2D2_ProcuraSpriteSet(arquivo);
    // Se j� existe um sprite com o nome do arquivo, retorna o �ndice associado
    if(idx != 0)
    {
		sprites[idx-1].usuarios=sprites[idx-1].usuarios+1;
        return idx;
    }
        
    // Se n�o existe, procura o primeiro �ndice vago (idx ainda � igual a 0)
    for(int i=0;i<C2D2_MAX_SPRITESET;i++)
        // O spriteset � vago (n�o tem imagem associada?
        if(sprites[i].imagem == 0)
        {
            idx=i+1;
            break;
        }
 
    // Testa se ainda tem espa�o na lista
    //
    // ATEN��O: n�o ter espa�o na mem�ria n�o � relacionado a este teste. Apenas
    // testa-se aqui se existe um �ndice vago na lista. Se n�o existe, idx==0
    if(idx==0)
        // Retorna um �ndice inv�lido para indicar que a fun��o falhou
        return 0;
    
    // Se chegou at� aqui, idx cont�m o identificador correto 
    // Calcula a posi��o no array (sem incrementar 1)
    idx-=1;    
    // Indica o caminho do arquivo no apelido
    strcpy(sprites[idx].apelido,arquivo);

    // Carrega a imagem no spriteset
    sprites[idx].imagem = IMG_Load(arquivo);

    // Testa: conseguiu abrir a imagem? Se deu erro, retorna spriteset inv�lido
    if (sprites[idx].imagem == 0) 
    {
		printf("A fun��o C2D2_CarregaSPriteset falhou ao carregar o arquivo %s. Erro: %s.\n",
                arquivo, SDL_GetError());
        sprites[idx].apelido[0] = '\0';
        return 0;
    }

    // Preenche as dimens�es da imagem do spriteset
	sprites[idx].largura = sprites[idx].imagem->w;

	sprites[idx].altura = sprites[idx].imagem->h;
    // Preenche as dimens�es dos sprites. Se for menor ou igual a 0, pega a da imagem em si
	if(largura > 0 && altura > 0)
	{
		sprites[idx].spLargura = largura;
		sprites[idx].spAltura = altura;
	}
	else
	{
		sprites[idx].spLargura = sprites[idx].imagem->w;
		sprites[idx].spAltura = sprites[idx].imagem->h;
	}

	// Testa se as dimens�es dos sprites s�o v�lidas em rela��o a imagem.
	// Para isto, a imagem deve ter dimens�es em valor m�ltiplo de inteiro com as do sprite.
	if( sprites[idx].altura%sprites[idx].spAltura != 0 || sprites[idx].largura%sprites[idx].spLargura != 0)
	{
            printf("Erro ao carregar a imagem %s. A altura e largura da imagem deve ser m�ltiplos do tamanho do sprite.\n", arquivo);
            SDL_FreeSurface(sprites[idx].imagem);
            sprites[idx].imagem=0;
            sprites[idx].apelido[0] = '\0';
            return 0;
    }
    // Preenche os tamanhos da matriz de sprites (in�til??)
    sprites[idx].matrizX =  sprites[idx].largura/sprites[idx].spLargura;
    sprites[idx].matrizY = sprites[idx].altura/sprites[idx].spAltura;

    // Define o magenta (R=255, B=255, G=0) para cor transparente
    SDL_SetColorKey(sprites[idx].imagem, SDL_RLEACCEL | SDL_SRCCOLORKEY | SDL_SRCALPHA,
        SDL_MapRGB(sprites[idx].imagem->format, 255, 0, 255));

        
    // Converte a imagem para o formato do v�deo do sistema
    SDL_Surface *temp=SDL_DisplayFormatAlpha(sprites[idx].imagem);
    //SDL_Surface *temp=SDL_DisplayFormat(sprites[idx].imagem);
    if(temp == 0) 
    {
        printf("N�o conseguiu criar a imagem tempor�ria ao carregar os sprites do arquivo %s. Erro: %s.\n",
            arquivo, SDL_GetError());
        SDL_FreeSurface(sprites[idx].imagem);
        sprites[idx].imagem = 0;
        sprites[idx].apelido[0] = '\0';
        return 0;
    }   
    // Apaga a surface antiga
    SDL_FreeSurface(sprites[idx].imagem);
    // Associa a nova
    sprites[idx].imagem = temp;

    // Cria a m�scara de colis�o 
	sprites[idx].bmask = C2D2_CriaVetorBitMasks(sprites[idx].imagem, sprites[idx].spLargura, sprites[idx].spAltura, sprites[idx].largura, sprites[idx].altura);
	// Se falhou, deve indicar isto
    if(sprites[idx].bmask == 0) 
    {
		printf("N�o conseguiu criar o vetor de bitmasks ao carregar os sprites do arquivo %s.\n", arquivo);
        SDL_FreeSurface(sprites[idx].imagem);
		sprites[idx].imagem = 0;
		sprites[idx].apelido[0] = '\0';
        return 0;
    }   
	// Daqui pra frente � ladeira, n�o tem porqu� falhar
	C2D2_PreencheVetorBitMasks(sprites[idx].imagem, sprites[idx].spLargura, sprites[idx].spAltura, sprites[idx].largura, sprites[idx].altura, sprites[idx].bmask);
	// Indica que tem um usu�rio
    sprites[idx].usuarios = 1;
    // idx+1 indica o identificador. Retorna e encerra (ufa!)
    return idx+1;
}


// Remove um sprite set da mem�ria
//
// Data: 13/04/2007
//
void C2D2SDL_RemoveSpriteSet(unsigned int id)
{
    // O identificador � v�lido?
    if(id > C2D2_MAX_SPRITESET || id == 0)
        return;
    // S� apaga se o n�mero de usu�rios for um ou se estiver em shutdown
    if(sprites[id-1].usuarios > 1 && !c_shutdown)
    {
        sprites[id-1].usuarios -= 1;
        return;
    }
    // Se cair aqui, � porqu� n�o tem mais usu�rios
    sprites[id-1].usuarios = 0;
    // Tem uma surface SDL associada?
    if(sprites[id-1].imagem != 0)
    {
        // Apaga a surface
        SDL_FreeSurface(sprites[id-1].imagem);
        // Associa um valor nulo para reutilizar depois
        sprites[id-1].imagem = 0;
        // Tem que tirar o nome
        sprites[id-1].apelido[0] = '\0';
    }
    // Se tem m�scara de colis�o, apaga
	if(sprites[id-1].bmask != 0)
	{
		// Apaga as m�scaras do vetor
		for(int i=0;i<sprites[id-1].matrizX*sprites[id-1].matrizY;i++)
			C2D2_RemoveBitMask(sprites[id-1].bmask[i]);
		// Apaga o vetor das m�scaras     
		free(sprites[id-1].bmask);
        // Prepara para o pr�ximo uso
        sprites[id-1].bmask=0;
    }

	/*	if(sprites[id-1].colisao != 0)
	{
		// Apaga a m�scara     
		free(sprites[id-1].colisao);
        // Prepara para o pr�ximo uso
        sprites[id-1].colisao=0;
    }*/
}


// Fun��o para desenhar um sprite
//
// Data: 13/04/2007
//
bool C2D2SDL_DesenhaSprite(unsigned int identificador, unsigned int indice, int x, int y)
{
	// O �ndice � v�lido?
	if(identificador<=0 || identificador > C2D2_MAX_SPRITESET)
	{
		printf("Erro ao tentar desenhar o spriteset %i. Este �ndice � inv�lido.\n", identificador);
		return false;
	}
    // Tem que existir a imagem
    if(sprites[identificador-1].imagem == 0)
        return false;
    
    // Seleciona o spriteset que vai desenhar
    C2D2_SpriteSet *sprite = &(sprites[identificador-1]);
    
    // Tamanho em pixels do spriteset
	int tamX = sprite->spLargura;
	int tamY = sprite->spAltura;
    // Define os rects para o blit
	SDL_Rect orig, dest;
 	dest.x = (Sint16)x;
	dest.y = (Sint16)y;
	dest.w = tamX;
	dest.h = tamY;
	orig.x = (indice%sprite->matrizX)*tamX;
	orig.y = (indice/sprite->matrizX)*tamY;
	orig.w = tamX;
	orig.h = tamY;
	SDL_BlitSurface(sprite->imagem, &orig, screen, &dest);
	// Faz o blit
    return true;
}

// Fun��o para desenhar um sprite distorcido e com efeitos de cor/alpha
bool C2D2SDL_DesenhaSpriteEfeito(unsigned int identificador, unsigned int indice, int x[4], int y[4], Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// Por default, n�o consegue desenhar neste modo e retorna falso (d���!)
	return false;
}
