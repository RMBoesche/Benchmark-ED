#include "TAD.h"

int main()
{
	NODO_LSE *listaLSE = NULL, *nodoLSE = NULL;
	NODO_ABP *arvABP = NULL, *nodoABP = NULL;
	NODO_AVL *arvAVL = NULL, *nodoAVL = NULL;

	int i, opcao; //opcao eh uma variavel pra determinar se os valores serao aleatorios ou ordenados
	int ok = 0, ciclo = 0;

	int cmpsLSE = 0, cmpsABP = 0, cmpsAVL = 0;
	float tempo[3][2] = {0}; //Uma matrix TIPO (estrutura)x TEMPO (inserir e consultar)

	int *dados;
	dados = malloc(TAMANHO * sizeof(int));

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

		/*===============================================================================
                        Início - Lista Simplesmente Encadeada
		=================================================================================*/

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			listaLSE = inserirLSE(listaLSE, dados[i]);

		end = clock();

		tempo[LSE][1] += ((float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += dadosTotal / 1000)
			nodoLSE = consultarLSE(listaLSE, dados[i], &cmpsLSE);

		end = clock();

		tempo[LSE][2] += ((float)(end - start) / CLOCKS_PER_SEC);

		listaLSE = destruirLSE(listaLSE);
		/*===============================================================================
                        Fim - Lista Simplesmente Encadeada 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore de Pesquisa Binária
		=================================================================================*/

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvABP = inserirABP(arvABP, dados[i], &cmpsABP);

		end = clock();

		tempo[ABP][1] += ((float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += dadosTotal / 1000)
			nodoABP = consultarABP(arvABP, dados[i], &cmpsABP);

		end = clock();

		tempo[ABP][2] += ((float)(end - start) / CLOCKS_PER_SEC);

		arvABP = destruirABP(arvABP);

		/*===============================================================================
		                        Fim - Árvore de Pesquisa Binária 
		=================================================================================*/

		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/

		start = clock();

		for (i = 0; i < dadosTotal; i++)
			arvAVL = inserirAVL(arvAVL, dados[i], &ok, &cmpsAVL);

		end = clock();

		tempo[AVL][1] += ((float)(end - start) / CLOCKS_PER_SEC);

		start = clock();

		for (i = 0; i < dadosTotal; i += dadosTotal / 1000)
			nodoAVL = consultarAVL(arvAVL, dados[i], &cmpsAVL);

		end = clock();

		tempo[AVL][2] += ((float)(end - start) / CLOCKS_PER_SEC);

		arvAVL = destruirAVL(arvAVL);

		/*===============================================================================
                        Início - Árvore AVL
		=================================================================================*/
	}

	printf("- LSE\n cmps: %ld \n t inserir: %f s\n t consultar: %f s\n\n", cmpsLSE, tempo[LSE][1] / 3, tempo[LSE][2] / 3);
	printf("- ABP\n cmps: %ld \n t inserir: %f s\n t consultar: %f s\n\n", cmpsABP, tempo[ABP][1] / 3, tempo[ABP][2] / 3);
	printf("- AVL\n cmps: %ld \n t inserir: %f s\n t consultar: %f s\n\n", cmpsAVL, tempo[AVL][1] / 3, tempo[AVL][2] / 3);

	return 0;
}
