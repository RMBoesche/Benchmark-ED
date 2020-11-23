#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;

	int i, opcao; //opcao eh uma variavel pra determinar se os valores serao aleatorios ou ordenados
	int ok = 0, ciclo = 0;

	int cmpsLSE = 0, cmpsABP = 0, cmpsAVL = 0;
	float tLSE = 0, tABP = 0, tAVL = 0;

	int dados[TAMANHO]; //ordenados = 0 e aleatorios = 1
	int dadosTotal = 0;

	clock_t start, end;

	printf("Escolha o numero de dados a serem carregados: \n");
	scanf("%d", &dadosTotal);

	printf("Escolha se os valores devem ser ordenados (0) ou aleatorios (1): \n");
	scanf("%d", &opcao);

	if (opcao == 0)
		for (i = 0; i < dadosTotal; i++)
			dados[i] = i;

	else if (opcao == 1)
	{
		srand(time(NULL));

		for (i = 0; i < dadosTotal; i++) //CRIA O VETOR COM OS VALORES ALEATORIOS
			dados[i] = rand() % dadosTotal;
	}

	for (ciclo = 0; ciclo < 3; ciclo++)
	{
		cmpsLSE = 0;
		cmpsABP = 0;
		cmpsAVL = 0;

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			listaLSE = inserirLSE(listaLSE, dados[i]);

		for (i = 0; i < dadosTotal; i += dadosTotal / 10)
			nodoLSE = consultarLSE(listaLSE, dados[i], &cmpsLSE);

		end = clock();

		tLSE += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		listaLSE = destruirLSE(listaLSE);

		//============================================================================

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvABP = inserirABP(arvABP, dados[i], &cmpsABP);

		for (i = 0; i < dadosTotal; i += dadosTotal / 10)
			nodoABP = consultarABP(arvABP, dados[i], &cmpsABP);

		end = clock();

		tABP += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		arvABP = destruirABP(arvABP);

		//============================================================================

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvAVL = inserirAVL(arvAVL, dados[i], &ok, &cmpsAVL);

		for (i = 0; i < dadosTotal; i += dadosTotal / 10)
			nodoAVL = consultarAVL(arvAVL, dados[i], &cmpsAVL);

		end = clock();

		tAVL += ((float)(end - start) / CLOCKS_PER_SEC * 1000);

		arvAVL = destruirAVL(arvAVL);
	}

	printf("- LSE:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsLSE, tLSE / 3);
	printf("- ABP:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsABP, tABP / 3);
	printf("- AVL:\n Numero de comparacoes: %d\n Tempo: %f ms\n\n", cmpsAVL, tAVL / 3);
	printf("\n tempo total: %f ms\n\n", (tLSE + tABP + tAVL) / 3);

	return 0;
}
