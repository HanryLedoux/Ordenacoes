#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


//GERADOR DE VETORES


void gerarVetor(int vetor[], int TAMANHO_VETOR) {
    for (int i = 0; i < TAMANHO_VETOR; i++)
        vetor[i] = rand();
}

void gerarVetorDecrescente(int vetor[], int TAMANHO_VETOR) {
    for (size_t i = 0; i < TAMANHO_VETOR; i++) {
        vetor[i] = (int)(TAMANHO_VETOR - i);
    }
}

void gerarVetorCrescente(int vetor[], int TAMANHO_VETOR) {
    for (size_t i = 0; i < TAMANHO_VETOR; i++) {
        vetor[i] = (int)(i + 1);
    }
}


void FuncaoGerarVetor(int vetor[], int TAMANHO_VETOR) {

    int escolha;

    printf("Selecione o caso de Ordenação:\n");
    printf("1. Aleatório\n");
    printf("2. Decrescente (Pior caso)\n");
    printf("3. Crescente (Melhor caso)\n");
    printf("Digite o número da opção: ");
    scanf("%d", &escolha);

    switch (escolha){
        case 1:
            gerarVetor(vetor, TAMANHO_VETOR);
        break;
        case 2:
            gerarVetorDecrescente(vetor, TAMANHO_VETOR);    
        break;
        case 3:
            gerarVetorCrescente(vetor, TAMANHO_VETOR);
        break;
        default:
        printf("Opção inválida.\n");
        break;
    }
}


//CALCULADOR DE TEMPO MÉDIO


void calcularTempoMedio(void (*sortFunc)(int*, int), int TAMANHO_VETOR, const char* nome, int repeticoes, int caso) {
    double soma_tempos = 0.0;
    int *vetor = (int*)calloc(TAMANHO_VETOR, sizeof(int));
    int *vetor_copia = (int*)calloc(TAMANHO_VETOR, sizeof(int));

    for (int i = 0; i < repeticoes; i++) {
        switch (caso) {
            case 1: 
                gerarVetor(vetor, TAMANHO_VETOR); 
                break;
            case 2: 
                gerarVetorDecrescente(vetor, TAMANHO_VETOR); 
                break;
            case 3: 
                gerarVetorCrescente(vetor, TAMANHO_VETOR); 
                break;
            default: 
                gerarVetor(vetor, TAMANHO_VETOR); 
                break;
        }
        for (int j = 0; j < TAMANHO_VETOR; j++)
            vetor_copia[j] = vetor[j];

        clock_t inicio = clock();
        sortFunc(vetor_copia, TAMANHO_VETOR);
        clock_t fim = clock();

        soma_tempos += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    printf("Tempo médio de execução do %s para %d elementos: %f segundos\n", nome, TAMANHO_VETOR, soma_tempos / repeticoes);

    free(vetor);
    free(vetor_copia);
}


// LINEAR SEARCH


int LinearSearch(int vetor[], int TAMANHO_VETOR, int valor) {
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        if (vetor[i] == valor) {
            printf("Valor %d encontrado na posição %d.\n", valor, i);
            return i;
        }
    }
    printf("Valor %d não encontrado no vetor.\n", valor);
}


// BINARY SEARCH


int BinarySearch(int vetor[], int TAMANHO_VETOR, int valor) {
    int inicio = 0;
    int fim = TAMANHO_VETOR - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (vetor[meio] == valor) {
            printf("Valor %d encontrado na posição %d.\n", valor, meio);
            return meio;
        }
        if (vetor[meio] < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Valor %d não encontrado no vetor.\n", valor);
}


//MERGE SORT


void merge(int vetor[], int esquerda, int meio, int direita) {
    int i, j, k;
    int TAMANHO_esquerdo = meio - esquerda + 1;
    int TAMANHO_direito = direita - meio;


    int vetor_esquerdo[TAMANHO_esquerdo], vetor_direito[TAMANHO_direito];


    for (i = 0; i < TAMANHO_esquerdo; i++) 
        vetor_esquerdo[i] = vetor[esquerda + i];
    for (j = 0; j < TAMANHO_direito; j++)
        vetor_direito[j] = vetor[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;


    while (i < TAMANHO_esquerdo && j < TAMANHO_direito) {
        if (vetor_esquerdo[i] <= vetor_direito[j]) {
            vetor[k] = vetor_esquerdo[i];
            i++;
        } else {
            vetor[k] = vetor_direito[j];
            j++;
        }
        k++;
    }


    while (i < TAMANHO_esquerdo) {
        vetor[k] = vetor_esquerdo[i];
        i++;
        k++;
    }


    while (j < TAMANHO_direito) {
        vetor[k] = vetor_direito[j];
        j++;
        k++;
    }
}


void mergeSort(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;


        mergeSort(vetor, esquerda, meio);
        mergeSort(vetor, meio + 1, direita);


        merge(vetor, esquerda, meio, direita);
    }
}

void FuncaoMergeSort() {
    int TAMANHO_VETOR;
    printf("MergeSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);


    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);


    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;


    tempo_inicio = clock();
    mergeSort(vetor, 0, TAMANHO_VETOR - 1);
    tempo_fim = clock();


    printf("\nElementos do array em ordem crescente:\n");
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");


    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;

    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}



//QUICK SORT


void quicksort(int vetor[], int inicio, int fim) {
    int pivo = vetor[(inicio + fim) / 2];
    int esquerdo = inicio;
    int direito = fim;


    while (esquerdo <= direito) {
        while (vetor[esquerdo] < pivo) esquerdo++;
        while (vetor[direito] > pivo) direito--;


        if (esquerdo <= direito) {
            int temp = vetor[esquerdo];
            vetor[esquerdo] = vetor[direito];
            vetor[direito] = temp;
            esquerdo++;
            direito--;
        }
    }


    if (inicio < direito)
        quicksort(vetor, inicio, direito);
    if (esquerdo < fim)
        quicksort(vetor, esquerdo, fim);
}


void FuncaoQuickSort() {
    int TAMANHO_VETOR;
    printf("QuickSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);

    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);


    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;


    tempo_inicio = clock();
    quicksort(vetor, 0, TAMANHO_VETOR - 1);
    tempo_fim = clock();


    printf("\nElementos do array em ordem crescente:\n");
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");


    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}

//Bubble SORT

void BubbleSort(int vetor[], int TAMANHO_VETOR) {
    int i, j, aux;
    int n = TAMANHO_VETOR;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int FuncaoBubbleSort() {
    int TAMANHO_VETOR;
    printf("BubbleSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);

    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);

    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;

    tempo_inicio = clock();
    BubbleSort(vetor, TAMANHO_VETOR);
    tempo_fim = clock();

    printf("\nElementos do array em ordem crescente:\n");
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");

    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}

//COCKTAIL SORT


void CocktailSort(int vetor[], int TAMANHO_VETOR) {
   
    int i, aux;
    int n = TAMANHO_VETOR;


    int inicio = 0;
    int fim = TAMANHO_VETOR - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = inicio; i < fim; i++)
        {
            if (vetor[i] > vetor[i + 1])
            {
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                swapped = 1;
            }
        }

        if(!swapped) {
            break;
        }

        swapped = 0;
        fim--;

        for (int i = fim; i > inicio; i--)
        {
            if (vetor[i] < vetor[i - 1])
            {
                aux = vetor[i];
                vetor[i] = vetor[i - 1];
                vetor[i - 1] = aux;
                swapped = 1;
            }
        }
        inicio++;
    }
}

int FuncaoCockTail()
{
    int i;
    int TAMANHO_VETOR;
    

    printf("CocktailSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);
    
    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));
    
    FuncaoGerarVetor(vetor, TAMANHO_VETOR);

    clock_t start_time = clock();

    CocktailSort(vetor, TAMANHO_VETOR);

    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nElementos do array em ordem crescente:\n");

    for (i = 0; i < TAMANHO_VETOR; i++)
    {
        printf("%d ", vetor[i]);
    }

    printf("\n");

    printf("Tempo de execução em segundos: %f\n", time_taken);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    return 0;
}



//INSERTION SORT

void InsertionSort(int vetor[], int TAMANHO_VETOR) {
 
    int i;
    int j;
    int insert_index;
    int current_value;

    int n = TAMANHO_VETOR;
    for (i = 0; i < n; i++) {
        insert_index = i;
        current_value = vetor[i];
        
        for(j = i - 1; j > -1; j--) {
            if (vetor[j] > current_value) {
                vetor[j + 1] = vetor[j];
                insert_index = j;
            }
            else {
                break;
            }
        }
        vetor[insert_index] = current_value;
    }
}

int FuncaoInsertionSort() {
    int TAMANHO_VETOR;
    printf("InsertionSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);

    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);

    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;

    tempo_inicio = clock();
    InsertionSort(vetor, TAMANHO_VETOR);
    tempo_fim = clock();

    printf("\nElementos do array em ordem crescente:\n");
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");

    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}


//SELECTION SORT

void SelectionSort(int vetor[], int TAMANHO_VETOR) {

    int i;
    int j;
    int num_minimo;
    int n = TAMANHO_VETOR;

    for(i = 0; i < n - 1; i++) {
        num_minimo = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[num_minimo]) {
                num_minimo = j;
            }
        }
        if (num_minimo != i) {
            int temp = vetor[i];
            vetor[i] = vetor[num_minimo];
            vetor[num_minimo] = temp;
        }
    }
}

int FuncaoSelectionSort() {
    int TAMANHO_VETOR;
    printf("SelectionSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);

    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);

    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;

    tempo_inicio = clock();
    SelectionSort(vetor, TAMANHO_VETOR);
    tempo_fim = clock();

    printf("\nElementos do array em ordem crescente:\n");

    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");

    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}


//SHELL SORT

void ShellSort(int vetor[], int TAMANHO_VETOR) {

    int i;
    int j;
    int intervalo;
    int n = TAMANHO_VETOR;

    for (intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (i = intervalo; i < n; i++) {
            int temp = vetor[i];
            j = i;

            while (j >= intervalo && vetor[j - intervalo] > temp) {
                vetor[j] = vetor[j - intervalo];
                j -= intervalo;
            }
            vetor[j] = temp;
        }
    }
}

int FuncaoShellSort() {
    int TAMANHO_VETOR;
    printf("ShellSort \n");
    printf("Selecione o TAMANHO do array: ");
    scanf("%d", &TAMANHO_VETOR);

    int *vetor = (int *)calloc(TAMANHO_VETOR, sizeof(int));

    FuncaoGerarVetor(vetor, TAMANHO_VETOR);

    clock_t tempo_inicio, tempo_fim;
    double tempo_execucao;

    tempo_inicio = clock();
    ShellSort(vetor, TAMANHO_VETOR);
    tempo_fim = clock();

    printf("\nElementos do array em ordem crescente:\n");
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("%4d ", vetor[i]);
    }
    printf("\n");

    tempo_execucao = ((double)(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    printf("1. LinearSearch \n");
    printf("2. BinarySearch \n");
    printf("sair\n");
    printf("Selecione o método de busca: ");
    int metodoBusca;
    scanf("%d", &metodoBusca);

    int valor;
    
    switch (metodoBusca) {
        case 1:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            LinearSearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            BinarySearch(vetor, TAMANHO_VETOR, valor);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }

    free(vetor);
}

//Funções Wrapper para Merge Sort e Quick Sort (para conseguir chamar no main)

void mergeSortWrapper(int vetor[], int TAMANHO_VETOR) {
    mergeSort(vetor, 0, TAMANHO_VETOR - 1);
}

void quicksortWrapper(int vetor[], int TAMANHO_VETOR) {
    quicksort(vetor, 0, TAMANHO_VETOR - 1);
}


//MAIN


int main() {
    int selecao;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf("Escolha o método de ordenação: ");
    printf("\n1. Merge Sort");
    printf("\n2. Quick Sort");
    printf("\n3. Cocktail Sort");
    printf("\n4. Insertion Sort");
    printf("\n5. Selection Sort");
    printf("\n6. Shell Sort");
    printf("\n7. Cálculo do tempo médio");
    printf("\nDigite o número da opção: ");
    scanf("%d", &selecao);

    switch (selecao) {
        case 1:
            FuncaoMergeSort();
            break;
        case 2:
            FuncaoQuickSort();
            break;
        case 3:
            FuncaoCockTail();
            break;
        case 4:
            FuncaoInsertionSort();
            break;
        case 5:
            FuncaoSelectionSort();
            break;
        case 6:
            FuncaoShellSort();
            break;
        case 7:
            int TAMANHO_VETOR;
            int repeticoes;
            int caso;
            printf("\nDigite o tamanho do vetor para teste: ");
            scanf("%d", &TAMANHO_VETOR);
            
            printf("Digite o número de repetições para calcular o tempo médio: ");
            scanf("%d", &repeticoes);
            
            printf("Selecione o caso de Ordenação:\n");
            printf("1. Aleatório\n");
            printf("2. Decrescente (Pior caso)\n");
            printf("3. Crescente (Melhor caso)\n");
            printf("Digite o número da opção: ");
            scanf("%d", &caso);

            printf("\n");
            calcularTempoMedio(InsertionSort, TAMANHO_VETOR, "InsertionSort", repeticoes, caso);
            calcularTempoMedio(SelectionSort, TAMANHO_VETOR, "SelectionSort", repeticoes, caso);
            calcularTempoMedio(ShellSort, TAMANHO_VETOR, "ShellSort", repeticoes, caso);
            calcularTempoMedio(CocktailSort, TAMANHO_VETOR, "CocktailSort", repeticoes, caso);
            calcularTempoMedio(mergeSortWrapper, TAMANHO_VETOR, "MergeSort", repeticoes, caso);
            calcularTempoMedio(quicksortWrapper, TAMANHO_VETOR, "QuickSort", repeticoes, caso);
            printf("\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
    return 0;

}