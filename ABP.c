#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABP.h"
#include <locale.h>

struct TNodoABP
{
    char palavra[15];
    char sinonimo[15];
    struct TNodoABP *esq;
    struct TNodoABP *dir;
};
typedef struct TNodoABP pNodoABP;

pNodoABP* InsereArvore(pNodoABP *a, char word, char sin)
{
    if (a == NULL)
    {
        a = (pNodoABP*) malloc(sizeof(pNodoABP));
        strcpy(a->sinonimo,sin);
        strcpy(a->palavra,word);
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (strcmp(a->palavra,word) > 0)
        a->esq = InsereArvore(a->esq,word,sin);
    else if(strcmp(a->palavra,word) < 0)
        a->dir = InsereArvore(a->dir,word,sin);
    return a;
}

char consultaABP(pNodoABP *a, char word,int comp)
{
    while (a != NULL)
    {
        comp++;
        if (strcmp(a->palavra,word) == 0){
            comp++;
            return a->sinonimo;
        }
        else{
            comp++;
            if (strcmp(a->palavra,word) > 0)
            return consultaABP(a->esq,word,comp);
        else
            return consultaABP(a->dir,word,comp);
        }

    }
}

void LeDicio(FILE *dic,pNodoABP *a){
    char buf[100];
    char temp_word[15];
    char temp_s[15];

    while(!feof(dic)){
        if (fgets(buf,100,dic) != NULL) {
                strcpy(temp_word,strtok(buf,"\t"));
                strcpy(temp_s,strtok(NULL,"\t"));
                a = InsereArvore(a,temp_word,temp_s);
    }
}
}
