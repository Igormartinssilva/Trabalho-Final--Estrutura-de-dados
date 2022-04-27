#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABP.h"
#include <locale.h>

int main(char nomeent[15],char nomedic[15],char nomesaida[15])
{

    int comp = 0;         //variavel global responsavel por contar as comparações
    FILE *arq_entrada;
    FILE *arq_saida;
    FILE *arq_dicio;
    pNodoABP *arvore = NULL;

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    if (!(arq_entrada=fopen(nomeent[15], "r")))
        printf("Erro ao abrir arquivo!\n");
    if (!(arq_dicio=fopen(nomedic[15], "r")))
        printf("Erro ao abrir arquivo!\n");

        LeDicio(arq_dicio,arvore);

}
