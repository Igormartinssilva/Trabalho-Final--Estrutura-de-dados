typedef struct TNodoABP pNodoABP;

pNodoABP* InsereArvore(pNodoABP *a, char word, char sin);
char consultaABP(pNodoABP *a, char word, int comp);
void LeDicio(FILE *dic, pNodoABP *a);
