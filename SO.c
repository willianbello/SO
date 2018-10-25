/*
Simulador de Gerenciamento de memória do tipo:
First Fit
Next Fit
Best Fit
Worst Fit

É um algoritmo simples que visa exemplificar a alocação de um processo dependendo do tipo de gerenciamento escolhido

- As Lacunas representam a quantidade de memória disponível no sistema para ser usada.
- As Requisições representam a quantidade necessária para o processo executar.
*/
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#define limpatela() system("cls")
#define ajustaTela() system("mode con:cols=110 lines=30")
#else
#define limpatela() system("clear")
#define ajustaTela() 
#endif

int tela (){

}

int iniciar(){
	
	int teste, opcao;
	
    limpatela();
    ajustaTela();
	printf ("Criado por: Isaias Fernandes, Willian Bello.\n\n");
	printf ("******************************************************\n");
	printf ("************** Gerenciamento de Memoria **************\n");
	printf ("******************************************************\n\n\n");
	printf ("1 - Preencher Automatico (8 Lacunas - 3 Requisicoes)\n");
	printf ("2 - Preencher Manual\n");
	printf ("0 - Sair\n\n");
	printf ("Opcao: ");
	
	do{
		teste = scanf ("%d", &opcao);
		if (teste != 1) while (getchar() != '\n');
	}while  (teste!=1);
    limpatela();
	return opcao;
}

int* preencheLacAut(int *vetor, int *tam){
	
	int i;
	
	vetor = malloc (8 * sizeof(int));
	if (vetor == NULL) {
		printf ("\nEspaco nao alocado\n");
		return NULL;
	}
	int vetAux [8] = {10,4,20,18,7,9,12,13};
    *tam = 8;
    for (i = 0; i < 8; i ++) vetor[i] = vetAux[i];
	return vetor;	
}

int* preencheReqAut(int *vetor, int *tam){
		
	int i;
	
	vetor = malloc (3 * sizeof(int));
	if (vetor == NULL) {
		printf ("\nEspaco nao alocado\n");
		return NULL;
	}
	int vetAux [3] = {5,10,16};
    *tam = 3;
    for (i = 0; i < 3; i ++) vetor[i] = vetAux[i];
	return vetor;	
}

int* preencheLacMan(int *vetor, int *tam){
	
    int i, qnt, teste;

    printf ("Numero de Lacunas: ");
    scanf ("%d", &qnt);

    vetor = malloc (qnt * sizeof(int));
    if (vetor == NULL) {
        printf ("\nEspaco nao alocado ou memoria insuficiente\n");
        return NULL;
    }
    *tam = qnt;
    for (i = 0; i < qnt; i ++){
        do{
            printf ("Lacuna %i: ", i+1);
            teste = scanf ("%d", &vetor[i]);
            if (teste != 1) printf ("ERRO. Nao foi possivel ler o valor. Tente Novamente.\n");
            while (getchar() != '\n');
        }while(teste != 1);
    }

    return vetor;
}

int* preencheReqMan(int *vetor, int *tam){
	
    int i, qnt, teste;

    printf ("Numero de Requisicoes: ");
    scanf ("%d", &qnt);

    vetor = malloc (qnt * sizeof(int));
    if (vetor == NULL) {
        printf ("\nEspaco nao alocado ou memoria insuficiente\n");
        return NULL;
    }
    *tam = qnt;
    for (i = 0; i < qnt; i ++){
        do{
            printf ("Requisicao %i: ", i+1);
            teste = scanf ("%d", &vetor[i]);
            if (teste != 1) printf ("ERRO. Nao foi possivel ler o valor. Tente Novamente.\n");
            while (getchar() != '\n');
        }while(teste != 1);
    }
    return vetor;
}

int firstFit (int *lacunas, int *requisicoes, int qntLac, int qntReq){
	
    int i, j, k;

    printf ("\nFirst Fit: \n\n");
    for (i = 0; i < qntLac; i ++) printf ("  [%2d]", lacunas[i]);
    printf ("\n");
    for (i = 0; i < qntReq; i ++){
		for (j = 0; j < qntLac; j ++){
            if (requisicoes[i] <= lacunas [j]){
                lacunas[j] -= requisicoes[i];
                for (k = 0; k < qntLac; k ++){
                    if (k == j) {
                        printf (" >[%2d]", lacunas[k]);
                    }
                    else printf ("  [%2d]", lacunas[k]);
                }
                printf ("\n");
                break;
            }else if(j == (qntLac-1)){
                printf ("Nao foi possivel atender a requisicao: [%d]\n", requisicoes[i]);
                break;
            }
        }
	}
}

int nextFit (int *lacunas, int *requisicoes, int qntLac, int qntReq){
    int i, j, k, frag;

    printf ("\nNext Fit: \n\n");
    for (i = 0; i < qntLac; i ++) printf ("  [%2d]", lacunas[i]);
    printf ("\n");

    i = 0;
    j = 0;
    frag = 0;
    while (i < qntReq){
        if (requisicoes[i] <= lacunas [j]){
            lacunas[j] -= requisicoes[i];
            for (k = 0; k < qntLac; k ++){
                if (k == j) {
                    printf (" >[%2d]", lacunas[k]);
                }
                else printf ("  [%2d]", lacunas[k]);
            }
            printf ("\n");
            i ++;
        }
        j++;

        if (frag == 0 && j >= qntLac){
            frag = 1;
            j = 0;
        }
        if (frag == 1 && j >= qntLac){
            j = 0;
            frag = 2;
        }
        if (frag == 2 && j >= qntLac){
            printf ("Nao foi possivel atender a requisicao: [%d]\n", requisicoes[i]);
            i++;
            frag = 0;
            //break;
        }
    }
}

int bestFit (int *lacunas, int *requisicoes, int qntLac, int qntReq){

    int i, j, menor, k;

    //impressão das lacunas e requisições
    printf ("\nBest Fit: \n\n");
    for (i = 0; i < qntLac; i ++) printf ("  [%2d]", lacunas[i]);
    printf ("\n");

    for (i = 0; i < qntReq; i++){
        menor = 0;
        for (j = 0; j < qntLac; j++){
            if ((lacunas[j] - requisicoes[i]) >= 0) {
                menor = j;
                break;
            }
        }

        for (;j < qntLac; j++){
            if (lacunas[j] >= requisicoes[i] && lacunas[j] < lacunas[menor]) menor = j;
        }

        //compara se o valor da lacuna é maior que o da requisição
        if (lacunas[menor] >= requisicoes[i]) {
            lacunas[menor] -= requisicoes[i];

            //imprime tabela
            for (k = 0; k < qntLac; k ++){
                if (k == menor) {
                    printf (" >[%2d]", lacunas[k]);
                }
                else printf ("  [%2d]", lacunas[k]);
            }
            printf ("\n");
        }
        else printf ("Nao foi possivel atender a requisicao: [%d]\n", requisicoes[i]);
    }
}

int worstFit (int *lacunas, int *requisicoes, int qntLac, int qntReq){

    int i, j, maior, k;

    printf ("\nWorst Fit: \n\n");
    for (i = 0; i < qntLac; i ++) printf ("  [%2d]", lacunas[i]);
    printf ("\n");

    for (i = 0; i < qntReq; i++){
        maior = 0;
        for (j = 0; j < qntLac; j++){
            if (lacunas[j] > lacunas[maior]) maior = j;
        }
        if (lacunas[maior] >= requisicoes[i]) {
            lacunas[maior] -= requisicoes[i];
            for (k = 0; k < qntLac; k ++){
                if (k == maior) {
                    printf (" >[%2d]", lacunas[k]);
                }
                else printf ("  [%2d]", lacunas[k]);
            }
            printf ("\n");
        }
        else printf ("Nao foi possivel atender a requisicao: [%d]\n", requisicoes[i]);
    }
}

int menu2 (){
    
    int opcao, teste;

    limpatela();
    printf ("Escolha um dos metodos abaixo:\n\n");
    printf ("1 - First Fit\n");
    printf ("2 - Next Fit\n");
    printf ("3 - Best Fit\n");
    printf ("4 - Worst Fit\n");

    do{
        printf ("Opcao: ");
        teste = scanf ("%d", &opcao);
        if (teste != 1) printf ("ERRO. Nao foi possivel ler o valor. Tente Novamente.\n");
        while (getchar() != '\n');
    }while(teste != 1);
    return opcao;
}
int imprimeLacEReq (int *vetorLac, int *vetorReq, int qntLac, int qntReq){
	int i;
	
	printf ("\nVetor Lacunas: ");
	for (i = 0; i < qntLac; i ++){
		printf ("[%d] ", vetorLac[i]);
	}
	printf ("\nVetor Requisicoes: ");
	for (i = 0; i < qntReq; i ++){
		printf ("[%d] ", vetorReq[i]);
	}
	printf ("\n");
}

int main (){
	
    int i, teste = 0;
	int *lacunas;
	int *requisicao;
	int opcao, qntLac, qntReq;
    char letra;
	do {
        opcao = iniciar();
        
        switch (opcao){
            case 0:
                return 0;
            case 1:
                lacunas = preencheLacAut(lacunas, &qntLac);
                requisicao = preencheReqAut(requisicao, &qntReq);
                break;
            case 2:
                lacunas = preencheLacMan(lacunas, &qntLac);
                requisicao = preencheReqMan(requisicao, &qntReq);
                break;
            default:
                printf ("\nOpcao Invalida\n");
        }

        opcao = menu2();
        limpatela();
        imprimeLacEReq (lacunas, requisicao, qntLac, qntReq);

        switch (opcao){
            case 1:
                firstFit(lacunas, requisicao, qntLac, qntReq);
                break;
            case 2:
                nextFit(lacunas, requisicao, qntLac, qntReq);
                break;
            case 3:
                bestFit(lacunas, requisicao, qntLac, qntReq);
                break;
            case 4:
                worstFit(lacunas, requisicao, qntLac, qntReq);
                break;
            default:
                printf ("\nOpcao Invalida\n");
        }


        free(lacunas);
        free(requisicao);
        printf ("\nDeseja continuar? (1 = Sim)\n");
        if (scanf ("%d", &teste) != 1) teste = 0;
        limpatela();
    }while (teste == 1);
}
