#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;
	int num, opcao, i; //opcao eh uma variavel pra determinar se os valores serao aleatorios ou ordenados
	long int totalvalores = 0;
	int vet[TAMANHO]; //ordenados = 0 e aleatorios = 1
	int cmpsLSE, cmpsABP, cmpsAVL;
	float tLSE = 0, tABP = 0, tAVL = 0;
	int ok = 0, ciclo = 0;

	clock_t start, end;

	printf("Escolha o numero de valores a serem carregados: \n");
	scanf("%ld", &totalvalores);

	printf("Escolha se os valores devem ser ordenados (0) ou aleatorios (1): \n");
	scanf("%d", &opcao);
	srand(time(NULL));

	if (opcao == 1)
	{
		for (i = 0; vet[i] < TAMANHO; i++) //CRIA O VETOR COM OS VALORES ALEATORIOS
			vet[i] = rand() % 1000000;
	}

	for (ciclo = 0; ciclo < 3; ciclo++)
	{
		cmpsLSE = 0;
		cmpsABP = 0;
		cmpsAVL = 0;

		start = clock();

		for (num = 0; num < totalvalores; num++)
		{
			if (opcao == 1)
				listaLSE = inserirLSE(listaLSE, vet[num]);
			else
				listaLSE = inserirLSE(listaLSE, num);
		}

		for (num = 0; num <= totalvalores; num += 10)
		{
			if (opcao == 1)
				nodoLSE = consultarLSE(listaLSE, vet[num], &cmpsLSE);
			else
				nodoLSE = consultarLSE(listaLSE, num, &cmpsLSE);
		}

		end = clock();

		tLSE += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		//============================================================================

		start = clock();

		for (num = 0; num < totalvalores; num++)
		{
			if (opcao == 1)
				arvABP = inserirABP(arvABP, vet[num], &cmpsABP);
			else
				arvABP = inserirABP(arvABP, num, &cmpsABP);
		}

		for (num = 0; num <= totalvalores; num += 10)
		{
			if (opcao == 1)
				nodoABP = consultarABP(arvABP, vet[num], &cmpsABP);
			else
				nodoABP = consultarABP(arvABP, num, &cmpsABP);
		}

		end = clock();

		tABP += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		//============================================================================

		start = clock();

		for (num = 0; num < totalvalores; num++)
		{
			if (opcao == 1)
				arvAVL = inserirAVL(arvAVL, vet[num], &ok, &cmpsAVL);
			else
				arvAVL = inserirAVL(arvAVL, num, &ok, &cmpsAVL);
		}

		for (num = 0; num <= totalvalores; num += 10)
		{
			if (opcao == 1)
				nodoAVL = consultarAVL(arvAVL, vet[num], &cmpsAVL);
			else
				nodoAVL = consultarAVL(arvAVL, num, &cmpsAVL);
		}

		end = clock();

		tAVL += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		listaLSE = destruirLSE(listaLSE);
		arvABP = destruirABP(arvABP);
		arvAVL = destruirAVL(arvAVL);
	}

	printf("- LSE:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsLSE, tLSE / 3);
	printf("- ABP:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsABP, tABP / 3);
	printf("- AVL:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsAVL, tAVL / 3);
	printf("\n tempo total: %f ms\n\n", (tLSE + tABP + tAVL) / 3);

	return 0;
}
