/*****************************************************************************
 * Arquivo: image.h
 * Descri��o: Defini��o de um TAD em C para manipula��o de imagens PPM e PGM
 * Modificado por: Wagner Ferreira de Barros
 * Ultima Modifica��o: 16/05/2004
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ------------- Estruturas e Variaveis Globais -----------------------*/

typedef struct {
  char tipo[80];
  long horizontal;
  long vertical;
  unsigned char **pixel;
  //unsigned char DXY[MAXLIN][MAXCOL];
} Imagem;

/* --------------------- Declaracao de Funcoes -----------------------*/
void Le_Imagem(Imagem *Fonte, const char *NomeArq);
void Escreve_Imagem(Imagem Fonte, const char *NomeArq);
unsigned char **alocapixels(long height, long width);
