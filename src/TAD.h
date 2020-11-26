#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 1000000
#define CICLOS 3
#define QTD_CONSULTAS 2500

/*===============================================================================
                        Início - Lista Simplesmente Encadeada
=================================================================================*/
typedef struct nodoLSE NODO_LSE;
struct nodoLSE
{
    int num;
    NODO_LSE *prox;
};

NODO_LSE *inserirLSE(NODO_LSE *, int);
NODO_LSE *consultarLSE(NODO_LSE *, int, int *);
NODO_LSE *destruirLSE(NODO_LSE *);
/*===============================================================================
                        Fim - Lista Simplesmente Encadeada 
=================================================================================*/

/*===============================================================================
                        Início - Árvore de Pesquisa Binária
=================================================================================*/
typedef struct nodoABP NODO_ABP;
struct nodoABP
{
    int num;
    NODO_ABP *esq;
    NODO_ABP *dir;
};

NODO_ABP *inserirABP(NODO_ABP *, int, int *);
NODO_ABP *consultarABP(NODO_ABP *, int, int *);
NODO_ABP *destruirABP(NODO_ABP *);
/*===============================================================================
                        Fim - Árvore de Pesquisa Binária 
=================================================================================*/

/*===============================================================================
                        Início - Árvore AVL
=================================================================================*/
typedef struct nodoAVL NODO_AVL;
struct nodoAVL
{
    int num;
    int FB;
    NODO_AVL *esq;
    NODO_AVL *dir;
};

NODO_AVL *rotacao_direita(NODO_AVL *);
NODO_AVL *rotacao_esquerda(NODO_AVL *);
NODO_AVL *rotacao_dupla_direita(NODO_AVL *, int *);
NODO_AVL *rotacao_dupla_esquerda(NODO_AVL *, int *);
NODO_AVL *caso1(NODO_AVL *, int *, int *);
NODO_AVL *caso2(NODO_AVL *, int *, int *);
NODO_AVL *inserirAVL(NODO_AVL *, int, int *, int *);
NODO_AVL *consultarAVL(NODO_AVL *, int, int *);
NODO_AVL *destruirAVL(NODO_AVL *);
/*===============================================================================
                        Início - Árvore AVL
=================================================================================*/