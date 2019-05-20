/* ---------------Comentarios--------------------------------------*/
/*
   Este código permite leitura e escrita de uma imagem em formato
   PGM /PPM, seja do tipo RAW ou ASC.
*/

#include "image.h"

/* -------------Area de Funcoes de Operações --------------------------*/

/* Funcao "Le_arquivo". Abre o arquivo e faz a leitura do cabeçalho
   e dos pixels colocando os valores na estrutura "Fonte"  */
void Le_Imagem(Imagem *Fonte, const char *NomeArq){

    FILE *fp;
    char Comentario[80];
    long x,y,max;

    /* Le, atribui e imprime cabeçalho */
    if((fp=fopen(NomeArq,"rb"))==NULL)
    {
        printf("O arquivo %s não pode ser lido.\n",NomeArq);
        exit(1);
    }
    fgets(Fonte->tipo,80,fp);
    fgets(Comentario,80,fp);
    while(!strncmp(Comentario,"#",1)) fgets(Comentario,80,fp);

    sscanf(Comentario,"%ld %ld", &Fonte->horizontal, &Fonte->vertical);
    fscanf(fp,"%ld\n",&max);
    strcpy(Comentario,"Imagem não possui comentário\n");


/* Le e atribui pixels */
    if (!strncmp(Fonte->tipo,"P6",2)) 	 // PPM formato raw
    {
        Fonte->pixel = alocapixels(3*Fonte->horizontal, Fonte->vertical);
        for (y=0; y < Fonte->vertical; y++){
            for (x=0; x < 3*Fonte->horizontal; x++)
                Fonte->pixel[y][x] = getc(fp);           // Red, Green e Blue
        }
    }

    fclose(fp);

} /*Fim Le_Imagem*/


/* Funcao "Escreve_Imagem". escreve a imagem a partir da estrutura Fonte */

void Escreve_Imagem(Imagem Fonte, const char *NomeArq)
{

    FILE *fp;
    long x,y;

    if((fp=fopen(NomeArq,"wb"))==NULL)
    {
        printf("O arquivo não pode ser criado.\n");
        exit(1);
    }

    /*Escreve imagem conforme o tipo*/

    if (!strncmp(Fonte.tipo,"P6",2))          // PPM formato raw
    {
        fprintf(fp,"%s%ld %ld\n%d\n",Fonte.tipo,Fonte.horizontal,Fonte.vertical,255);
        for(y=0 ; y < Fonte.vertical; y++){
            for(x=0; x< 3*Fonte.horizontal; x++)
                fputc(Fonte.pixel[y][x],fp);
        }
    }

    fclose(fp);

}/* Fim Escreve_imagem */

unsigned char **alocapixels(long width, long height){
	long i;

	unsigned char **m;

	//aloca as linhas
	m = (unsigned char**) malloc( height * sizeof(unsigned char*));
	if(m == NULL){
	   printf("\n Erro. Memoria Insuficiente. \n");
	   exit(0);
	}

	//agora aloca as colunas
	for(i=0; i<height; i++){
	  m[i] = (unsigned char*) malloc(width * sizeof(unsigned char));

	  if(m[i] == NULL){
	   printf("\n Erro. Memoria Insuficiente. \n");
	   exit(0);
	  }

	}

	int j;
	for(i = 0; i < height; i++){
        for(j = 0; j < width; j++)
            m[i][j] = (char) 0;
	}

	//retorna m
	return m;
}
