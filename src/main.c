#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;

	int cmpsLSE = 0, cmpsABP = 0, cmpsAVL = 0;
	float tInserirLSE = 0, tInserirABP = 0, tInserirAVL = 0;
	float tConsultLSE = 0, tConsultABP = 0, tConsultAVL = 0;

	int i = 0, ok = 0, ciclo = 0;

	int *dados, opcao = 0, dadosTotal = 0, difPesquisas = 0;
	dados = malloc(TAMANHO * sizeof(int));

	clock_t start, end;
	srand(time(NULL));

	printf("Numero de dados: \n");
	scanf("%d", &dadosTotal);

	printf("Dados ordenados (0) ou aleatorios (1): \n");
	scanf("%d", &opcao);

	difPesquisas = dadosTotal / QTD_CONSULTAS;

	if (opcao == 0)
		for (i = 0; i < dadosTotal; i++)
			dados[i] = i;

	else if (opcao == 1)
		for (i = 0; i < dadosTotal; i++) //CRIA O VETOR COM OS VALORES ALEATORIOS
			dados[i] = rand() % dadosTotal;

	for (ciclo = 0; ciclo < CICLOS; ciclo++)
	{
		/*===============================================================================
                        Início - Lista Simplesmente Encadeada
		=================================================================================*/
		cmpsLSE = 0;

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			listaLSE = inserirLSE(listaLSE, dados[i]);

		end = clock();

		tInserirLSE += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += difPesquisas)
			nodoLSE = consultarLSE(listaLSE, dados[i], &cmpsLSE);

		end = clock();

		tConsultLSE += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		listaLSE = destruirLSE(listaLSE);
		/*===============================================================================
                        Fim - Lista Simplesmente Encadeada 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore de Pesquisa Binária
		=================================================================================*/
		cmpsABP = 0;

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvABP = inserirABP(arvABP, dados[i], &cmpsABP);

		end = clock();

		tInserirABP += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += difPesquisas)
			nodoABP = consultarABP(arvABP, dados[i], &cmpsABP);

		end = clock();

		tConsultABP += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		arvABP = destruirABP(arvABP);

		/*===============================================================================
		                        Fim - Árvore de Pesquisa Binária 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/
		cmpsAVL = 0;

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvAVL = inserirAVL(arvAVL, dados[i], &ok, &cmpsAVL);

		end = clock();

		tInserirAVL += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += difPesquisas)
			nodoAVL = consultarAVL(arvAVL, dados[i], &cmpsAVL);

		end = clock();

		tConsultAVL += (1000 * (float)(end - start) / CLOCKS_PER_SEC);

		arvAVL = destruirAVL(arvAVL);

		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/
	}

	printf("- LSE\n cmps: %ld \n t inserir: %f ms\n t consultar: %f ms\n\n", cmpsLSE, tInserirLSE / CICLOS, tConsultLSE / CICLOS);
	printf("- ABP\n cmps: %ld \n t inserir: %f ms\n t consultar: %f ms\n\n", cmpsABP, tInserirABP / CICLOS, tConsultABP / CICLOS);
	printf("- AVL\n cmps: %ld \n t inserir: %f ms\n t consultar: %f ms\n\n", cmpsAVL, tInserirAVL / CICLOS, tConsultAVL / CICLOS);

	free(dados);

	return 0;
}
