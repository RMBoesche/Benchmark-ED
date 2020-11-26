#include "TAD.h"

/*===============================================================================
                        Início - Lista Simplesmente Encadeada
=================================================================================*/
NODO_LSE *inserirLSE(NODO_LSE *lista, int num)
{
    NODO_LSE *novo;

    novo = (NODO_LSE *)malloc(sizeof(NODO_LSE));
    novo->num = num;

    novo->prox = lista;
    lista = novo;

    return lista;
}

NODO_LSE *consultarLSE(NODO_LSE *lista, int num, int *cmps)
{
    NODO_LSE *nodo = lista;

    if ((lista != NULL) && (lista->num != num))
    {
        do
        {
            *cmps += 2;
            nodo = nodo->prox;
        } while ((nodo != NULL) && (nodo->num != num));
    }

    return nodo;
}

NODO_LSE *destruirLSE(NODO_LSE *lista)
{
    NODO_LSE *aux;

    while (lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
    return NULL;
}
/*===============================================================================
                        Fim - Lista Simplesmente Encadeada
=================================================================================*/

/*===============================================================================
                        Início - Árvore de Pesquisa Binária
=================================================================================*/
NODO_ABP *inserirABP(NODO_ABP *arv, int num, int *cmps)
{
    *cmps += 1;
    if (arv == NULL)
    {
        arv = (NODO_ABP *)malloc(sizeof(NODO_ABP));
        arv->num = num;
        arv->esq = NULL;
        arv->dir = NULL;
        return arv;
    }
    else
    {
        if (num < arv->num)
            arv->esq = inserirABP(arv->esq, num, cmps);
        else if (num > arv->num)
        {
            arv->dir = inserirABP(arv->dir, num, cmps);
            *cmps += 1;
        }
    }
    *cmps += 1;
    return arv;
}

NODO_ABP *consultarABP(NODO_ABP *arv, int num, int *cmps)
{
    *cmps += 1;
    while (arv != NULL)
    {
        *cmps += 1;
        if (arv->num == num)
            return arv;
        else
        {
            if (arv->num > num)
                arv = arv->esq;
            else
                arv = arv->dir;
            *cmps += 1;
        }
    }
    return NULL;
}

NODO_ABP *destruirABP(NODO_ABP *arv)
{
    if (arv != NULL)
    {
        destruirABP(arv->esq);
        destruirABP(arv->dir);
        free(arv);
    }
    return NULL;
}
/*===============================================================================
                        Fim - Árvore de Pesquisa Binária
=================================================================================*/

/*===============================================================================
                        Início - Árvore AVL
=================================================================================*/
NODO_AVL *rotacao_direita(NODO_AVL *pt)
{
    NODO_AVL *ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

NODO_AVL *rotacao_esquerda(NODO_AVL *pt)
{
    NODO_AVL *ptu;

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

NODO_AVL *rotacao_dupla_direita(NODO_AVL *pt, int *cmps)
{
    NODO_AVL *ptu, *ptv;

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)
        pt->FB = -1;
    else
        pt->FB = 0;
    if (ptv->FB == -1)
        ptu->FB = 1;
    else
        ptu->FB = 0;
    pt = ptv;
    *cmps += 2;
    return pt;
}

NODO_AVL *rotacao_dupla_esquerda(NODO_AVL *pt, int *cmps)
{
    NODO_AVL *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
        pt->FB = 1;
    else
        pt->FB = 0;
    if (ptv->FB == 1)
        ptu->FB = -1;
    else
        ptu->FB = 0;
    pt = ptv;
    *cmps += 2;
    return pt;
}

NODO_AVL *caso1(NODO_AVL *arv, int *ok, int *cmps)
{
    NODO_AVL *ptu;

    ptu = arv->esq;
    if (ptu->FB == 1)
        arv = rotacao_direita(arv);

    else
        arv = rotacao_dupla_direita(arv, cmps);

    *cmps += 1;
    arv->FB = 0;
    *ok = 0;
    return arv;
}

NODO_AVL *caso2(NODO_AVL *arv, int *ok, int *cmps)
{
    NODO_AVL *ptu;

    ptu = arv->dir;
    if (ptu->FB == -1)
        arv = rotacao_esquerda(arv);

    else
        arv = rotacao_dupla_esquerda(arv, cmps);

    *cmps += 1;
    arv->FB = 0;
    *ok = 0;
    return arv;
}

NODO_AVL *inserirAVL(NODO_AVL *arv, int x, int *ok, int *cmps)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
  x, a numave a ser inserida e h a altura da árvore */
    if (arv == NULL)
    {
        arv = (NODO_AVL *)malloc(sizeof(NODO_AVL));
        arv->num = x;
        arv->esq = NULL;
        arv->dir = NULL;
        arv->FB = 0;
        *ok = 1;
    }
    else if (x < arv->num)
    {
        arv->esq = inserirAVL(arv->esq, x, ok, cmps);
        if (*ok)
        {
            switch (arv->FB)
            {
            case -1:
                *cmps += 1;
                arv->FB = 0;
                *ok = 0;
                break;
            case 0:
                *cmps += 2;
                arv->FB = 1;
                break;
            case 1:
                *cmps += 3;
                arv = caso1(arv, ok, cmps);
                break;
            }
        }
    }
    else
    {
        arv->dir = inserirAVL(arv->dir, x, ok, cmps);
        if (*ok)
        {
            switch (arv->FB)
            {
            case 1:
                *cmps += 1;
                arv->FB = 0;
                *ok = 0;
                break;
            case 0:
                *cmps += 2;
                arv->FB = -1;
                break;
            case -1:
                *cmps += 3;
                arv = caso2(arv, ok, cmps);
                break;
            }
        }
    }
    *cmps += 2;
    return arv;
}

NODO_AVL *consultarAVL(NODO_AVL *arv, int num, int *cmps)
{
    while (arv != NULL)
    {
        *cmps += 1;
        if (arv->num == num)
            return arv;
        else
        {
            if (arv->num > num)
                arv = arv->esq;
            else
                arv = arv->dir;
            *cmps += 1;
        }
    }
    return NULL;
}

NODO_AVL *destruirAVL(NODO_AVL *arv)
{
    if (arv != NULL)
    {
        destruirAVL(arv->esq);
        destruirAVL(arv->dir);
        free(arv);
    }
    return NULL;
}
/*===============================================================================
                        Fim - Árvore AVL
=================================================================================*/