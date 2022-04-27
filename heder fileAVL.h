#include<stdio.h>
#include<stdlib.h>

struct Info
{
    int numero;
};
typedef struct Info TipoInfo;

struct TNodoA
{
    char palavra[20];
    char traducao[20];
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
    int altura;
};
typedef struct TNodoA pNodoA;

pNodoA* cria_arvore(void);
void preFixadoEsq(pNodoA *a);
pNodoA* rotacao_direita(pNodoA* p);
pNodoA* rotacao_esquerda(pNodoA* p);
pNodoA* rotacao_dupla_direita(pNodoA* p);
pNodoA* rotacao_dupla_esquerda(pNodoA* p);
pNodoA* InsereAVL(pNodoA *arvore, char palavra[], char trad[], int *ok);
char consultaAVL(pNodoA *a, char word);
pNodoA* Caso1(pNodoA *a, int *ok);
pNodoA* Caso2(pNodoA *a, int *ok);
int Altura (pNodoA *a);
void ImprimeTraco(pNodoA *a, int sinal);
pNodoA* InsereArvore(pNodoA *a, int ch);
int AbreDicionario(pNodoA *arvore);

