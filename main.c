#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pixel{
	unsigned char imagempixel[3];
};

struct posicao{
	long int i;
	long int j;
};

int main(void)
{
	//menu do programa
	printf("\t\t###################################\n\n");
	printf("\t\t######## C O N T A D O R ##########\n\n");
	printf("\t\t############## D E ################\n\n");
	printf("\t\t######## O B J E T O S ############\n\n");
	printf("\t\t###################################\n\n");
	
	getchar();
	system("cls");
	//fim do menu
	int pixel, k = 0;
	char nome_da_imagem[3];
	int colunas=0, linhas=0; //altura e largura da imagem
	int coluna = 0, linha = 0;
	int max ; //Valor máximo de cada pixel
	int i,j,z;
	unsigned char r, g, b;
	unsigned char r0,g0,b0;
	int **matriz_zero_um;
	int cont_objetos=0;
	int cont_pilha=0;
	struct pixel** alocarmatriz;
	struct posicao* pilha;
	FILE *arquivo;
	char nome_arquivo[30];
	
	printf("DIGITE O NOME DO ARQUIVO/ENDERECO\n");
	scanf("%[^\n]s", nome_arquivo);
	if((arquivo = fopen(nome_arquivo, "r"))== NULL)
	{
		printf("ARQUIVO NAO ENCONTRADO\n");
	}else
	{
		//LER O TAMANHO DA IMAGEM
		arquivo = fopen(nome_arquivo, "r");
		fscanf(arquivo, "%s %d %d %d", nome_da_imagem, &colunas, &linhas, &max);
		if(strcmp("P6", nome_da_imagem)!=0)
		{
			printf("IMAGEM NAO EH DO TIPO PPM\n");
			exit(1);
		}
		fscanf(arquivo, "%c", nome_da_imagem);
		
		//Alocar a matriz de zero e um
		matriz_zero_um = (int**) malloc(linhas*sizeof(int*));
			for(i=0;i<linhas;i++)
			{
				matriz_zero_um[i]=(int*) malloc(colunas*sizeof(int));
			for(j=0;j<colunas;j++)
			{
				matriz_zero_um[i][j];	
			}
			}
		//ALOCAR A MATRIZ DE PIXEL
		//Preencher a matriz de pixel, marcando cada r,g e b na struct
		alocarmatriz = (struct pixel**) malloc(linhas * sizeof(struct pixel*));
		for(i=0;i<linhas;i++)
		{
			alocarmatriz[i] = (struct pixel*) malloc(colunas * sizeof(struct pixel));
			for(j=0;j<colunas;j++)
			{
				fscanf(arquivo,"%c %c %c", &r,&g,&b);
				
				alocarmatriz[i][j].imagempixel[0]=r;
				alocarmatriz[i][j].imagempixel[1]=g;
				alocarmatriz[i][j].imagempixel[2]=b;
				
				//definindo o primeiro pixel como cor de fundo
				r0 = alocarmatriz[0][0].imagempixel[0];
				g0 = alocarmatriz[0][0].imagempixel[1];
				b0 = alocarmatriz[0][0].imagempixel[2];
				if((r == r0) &&(g == g0) && (b == b0))
				{
					matriz_zero_um[i][j] = 0;
				}else
				{
					matriz_zero_um[i][j]= 1;
				}
			}
		}
		printf("\n\n\n");
			
		}
		
		//mostrar a matriz_zero_um montando a imagem
		for(i=0;i<linhas;i++)
		{
			for(j=0;j<colunas;j++)
			{
				printf("%d", matriz_zero_um[i][j]);
			}
			printf("\n");
		}
		free(alocarmatriz);
		fclose(arquivo);
		//Inicio da procura por objeto
		pilha = (struct posicao*) malloc((linhas*colunas) * sizeof(struct posicao)); //Cria uma pilha

		for(i=0;i<linhas;i++)
		{
			for(j=0;j<colunas;j++)
			{
				if(matriz_zero_um[i][j] == 1) //1 != de fundo
				{
					matriz_zero_um[i][j] = 2;  //Marcação de que o pixel ja foi visitado(qualquer coisa !=1)
					linha = i;                  //salva linha e coluna de onde achou o pixel para iniciar o preenchimento 
					coluna = j;
				
				while(1)
				{
					if(i+1<=linhas){
					
					if(matriz_zero_um[i+1][j] == 1) //ANALISA O PIXEL DE BAIXO
					{
						matriz_zero_um[i+1][j] = 2;
						pilha[cont_pilha].i=i+1;          //Salva em uma pilha(vetor) os endereços a se visitar.
						pilha[cont_pilha++].j=j;
					}
				}
				
				    if(i-1>=0){
					
					if(matriz_zero_um[i-1][j] == 1) //ANALISA O PIXEL DE CIMA
					{
						matriz_zero_um[i-1][j] = 2;
						pilha[cont_pilha].i=i-1;         
						pilha[cont_pilha++].j=j;
					}
				}
				    if(j+1<=colunas){
					
					if(matriz_zero_um[i][j+1] == 1) //ANALISA O PIXEL DA DIREITA
					{
						matriz_zero_um[i][j+1] = 2;
						pilha[cont_pilha].i=i;         
						pilha[cont_pilha++].j=j+1;
					}
				}
				    if(j-1>=0){
					
					if(matriz_zero_um[i][j-1] == 1) //ANALISA O PIXEL DA ESQUERDA
					{
						matriz_zero_um[i][j-1] = 2;
						pilha[cont_pilha].i=i;          
						pilha[cont_pilha++].j=j-1;
					}
				}
					if(cont_pilha >0)              //quantidade de elementos na pilha
					{
						i=pilha[--cont_pilha].i;   //Vai para o ultimo elemento da pilha ainda não visto     
						j=pilha[cont_pilha].j;
					}
					else                           //Sai do while caso ja tenha preenchido tudo
								break;
					
				}
				cont_objetos++;
				i=linha; //volta para o endereço do primeiro pixel do objeto para continuar a procura de outros objetos
				j=coluna;
			}
		}
	}
	printf("NUMERO DE OBJETOS: %d\n\n", cont_objetos);
	printf("LINHAS E COLUNAS: %d  %d",linhas, colunas);
	free(pilha);
	free(matriz_zero_um);
}



