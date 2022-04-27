
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cabelho.h"

//incializa arvore
pNodoA* cria_arvore()
{
    return NULL;
}

void preFixadoEsq(pNodoA* a)
{
    if(a != NULL)
    {
        printf("a palavra e:%s\n e seu sinonimos e: %s\n", a->palavra, a->traducao);
        preFixadoEsq(a->esq);
        preFixadoEsq(a->dir);
    }
}

pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;

    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;

    return p;
}

pNodoA* rotacao_esq(pNodoA *p)
{
    pNodoA *z;

    z = p->dir;
    p->dir = z->esq;
    p->FB = 0;
    p = z;

    return p;
}

pNodoA* rotacao_dupla_direita(pNodoA* p)
{
    pNodoA *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    if(v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if(v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;

    p = v;

    return p;
}

pNodoA* rotacao_dupla_esquerda(pNodoA* p)
{
    pNodoA *z, *y;

    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir =y->esq;
    y->esq = p;

    if(y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if(y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;

    p = y;

    return p;
}

pNodoA* InsereAVL(pNodoA *a, char palavra[], char trad[], int *ok)
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->palavra,palavra);
        strcpy(a->traducao,trad);

        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        ok = 1;
        a->altura = 1;

    }
    //a->palavra > palavra == 1
    //a->palavra < palavra == -1
    //strcmp(a->palavra,palavra) == 1)
    else if(strcmp(a->palavra,palavra) > 0)
    {
        a->esq = InsereAVL(a->esq,palavra,trad,ok);
        if(ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = Caso1(a,ok);
                break;
            }
        }
    }

    else
    {
        a->dir = InsereAVL(a->dir,palavra,trad,ok);
        if(ok)
        {
            switch(a->FB)
            {
            case 1:
                a->FB = 0;
                ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }

    return a;

}

pNodoA* Caso1(pNodoA *a, int *ok)
{
    pNodoA *z;

    z =a->esq;

    if(z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);

    a->FB = 0;
    ok = 0;
    return a;
}

pNodoA* Caso2(pNodoA *a, int *ok)
{
    pNodoA *z;

    z = a->dir;
    if(z->FB == -1)
        a = rotacao_esq(a);
    else
        a = rotacao_dupla_esquerda(a);

    a->FB = 0;
    ok = 0;

    return a;
}

int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;

    if(a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);

        if(Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

void ImprimeTraco(pNodoA *a, int sinal)
{
    int i;

    if (a!= NULL)
    {
        for(i=0; i<sinal; i++)
            printf("=");

        printf("plavra: %s\n sinonimo: %s\n", a->palavra, a->traducao);
        ImprimeTraco(a->esq,sinal+1);
        ImprimeTraco(a->dir,sinal+1);
    }

}

char consultaAVL(pNodoA *a, char word)
{
    if (a==NULL)
        return NULL;
    else if (strcmp(a->palavra,word) == 0)
        return a->traducao;
    else if (strcmp(a->palavra,word) > 0)
        return consultaAVL(a->esq,word);
    else
        return consultaAVL(a->dir,word);
}

int AbreDicionario(pNodoA *arvore)
{
    FILE *arq;
    char nomeDic[20]="dict_10K.txt";
    int falhou;
    char *palavra, *trad,*t;
    char linha[100];
    int *ok;

   // printf("digite o nome do dcionario: ");
   // scanf("%s", nomeDic);

    arq = fopen(nomeDic,"r");

    if(!arq)
    {
        falhou = 0;// quando ha falha a flag retorna zero
    }
    else
    {
        falhou = 1;

        while(feof(arq) != 0)
        {
            if(fgets(linha,sizeof(linha),arq) != NULL)
            {
                strcpy(palavra,strtok(linha,"   "));
                strcpy(trad,strtok(NULL,"   "));


                arvore = InsereAVL(arvore,palavra,trad,ok);
            }

        }
    }

    fclose(arq);

    return falhou;
}

