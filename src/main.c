#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;

	unsigned long int cmpsLSE = 0, cmpsABP = 0, cmpsAVL = 0, aux = 0;

	float tInserirLSE = 0, tInserirABP = 0, tInserirAVL = 0;
	float tConsultLSE = 0, tConsultABP = 0, tConsultAVL = 0;

	int i = 0, ok = 0, ciclo = 0, segFault = 0;

	int *dados, opcao = 0, dadosTotal = 0, difPesquisas = 0;

	clock_t start, end;

	printf("Numero de dados: \n");
	scanf("%d", &dadosTotal);

	printf("Dados ordenados (0) ou aleatorios (1): \n");
	scanf("%d", &opcao);
	printf("\n");

	srand(time(NULL));
	difPesquisas = dadosTotal / QTD_CONSULTAS;
	dados = malloc(dadosTotal * sizeof(int));

	if ((opcao == ORDENADOS) && (dadosTotal > LIMITE_ABP))
		segFault = 1;

	if (opcao == ORDENADOS)
		for (i = 0; i < dadosTotal; i++)
			dados[i] = i;

	else if (opcao == ALEATORIOS)
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
		tInserirLSE += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);

		start = clock();
		for (i = 0; i < dadosTotal; i += difPesquisas)
			nodoLSE = consultarLSE(listaLSE, dados[i], &cmpsLSE);

		end = clock();
		tConsultLSE += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);

		listaLSE = destruirLSE(listaLSE);
		/*===============================================================================
                        Fim - Lista Simplesmente Encadeada 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore de Pesquisa Binária
		=================================================================================*/
		if (segFault == 0)
		{
			arvABP = NULL;
			cmpsABP = 0;

			start = clock();
			for (i = 0; i < dadosTotal; i++)
				arvABP = inserirABP(arvABP, dados[i], &cmpsABP);

			end = clock();
			tInserirABP += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);

			start = clock();
			for (i = 0; i < dadosTotal; i += difPesquisas)
				nodoABP = consultarABP(arvABP, dados[i], &cmpsABP);

			end = clock();
			tConsultABP += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);
		}
		/*===============================================================================
		                        Fim - Árvore de Pesquisa Binária 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/
		arvAVL = NULL;
		cmpsAVL = 0;

		start = clock();
		for (i = 0; i < dadosTotal; i++)
			arvAVL = inserirAVL(arvAVL, dados[i], &ok, &cmpsAVL);

		end = clock();
		tInserirAVL += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);

		start = clock();
		for (i = 0; i < dadosTotal; i += difPesquisas)
			nodoAVL = consultarAVL(arvAVL, dados[i], &cmpsAVL);

		end = clock();
		tConsultAVL += (float)(1000 * (float)(end - start) / CLOCKS_PER_SEC);
		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/
	}

	printf("- LSE\n cmps: %lu \n t inserir: %.3f ms\n t consultar: %.3f ms\n\n", cmpsLSE, tInserirLSE / CICLOS, tConsultLSE / CICLOS);
	if (segFault == 0)
		printf("- ABP\n cmps: %lu \n t inserir: %.3f ms\n t consultar: %.3f ms\n\n", cmpsABP, tInserirABP / CICLOS, tConsultABP / CICLOS);
	printf("- AVL\n cmps: %lu \n t inserir: %.3f ms\n t consultar: %.3f ms\n\n", cmpsAVL, tInserirAVL / CICLOS, tConsultAVL / CICLOS);

	free(dados);

	return 0;
}
