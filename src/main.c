#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;
	int num;

	int cmpsLSE, cmpsABP, cmpsAVL;
	float tLSE = 0, tABP = 0, tAVL = 0;
	int ok = 0, ciclo = 0;

	clock_t start, end;

	for (ciclo = 0; ciclo < 3; ciclo++)
	{
		cmpsLSE = 0;
		cmpsABP = 0;
		cmpsAVL = 0;

		start = clock();

		for (num = 0; num < 10000; num++)
			listaLSE = inserirLSE(listaLSE, num);

		for (num = 0; num <= 10000; num += 10)
			nodoLSE = consultarLSE(listaLSE, num, &cmpsLSE);

		end = clock();

		tLSE += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		//============================================================================

		start = clock();

		for (num = 0; num < 10000; num++)
			arvABP = inserirABP(arvABP, num, &cmpsABP);

		for (num = 0; num <= 10000; num += 10)
			nodoABP = consultarABP(arvABP, num, &cmpsABP);

		end = clock();

		tABP += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		//============================================================================

		start = clock();

		for (num = 0; num < 10000; num++)
			arvAVL = inserirAVL(arvAVL, num, &ok, &cmpsAVL);

		for (num = 0; num <= 10000; num += 10)
			nodoAVL = consultarAVL(arvAVL, num, &cmpsAVL);

		end = clock();

		tAVL += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		listaLSE = destruirLSE(listaLSE);
		arvABP = destruirABP(arvABP);
		arvAVL = destruirAVL(arvAVL);
	}

	printf("- LSE:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsLSE, tLSE / 3);
	printf("- ABP:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsABP, tABP / 3);
	printf("- AVL:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsAVL, tAVL / 3);

	return 0;
}