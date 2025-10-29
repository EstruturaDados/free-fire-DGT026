#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para contagem de comparações
int comparacoes = 0;

// Funções
void bubbleSortNome(Componente comps[], int n);
void insertionSortTipo(Componente comps[], int n);
void selectionSortPrioridade(Componente comps[], int n);
int buscaBinariaPorNome(Componente comps[], int n, char nome[]);
void mostrarComponentes(Componente comps[], int n);
void cadastrarComponentes(Componente comps[], int *total);

int main() {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    char nomeBusca[30];

    // Cadastro dos componentes
    cadastrarComponentes(componentes, &total);

    do {
        printf("\n======= TORRE DE FUGA =======\n");
        printf("Escolha a opcao:\n");
        printf("1 - Ordenar por Nome (Bubble Sort)\n");
        printf("2 - Ordenar por Tipo (Insertion Sort)\n");
        printf("3 - Ordenar por Prioridade (Selection Sort)\n");
        printf("4 - Buscar Componente-Chave (apenas por Nome)\n");
        printf("5 - Mostrar Componentes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        clock_t inicio, fim;
        double tempo;

        switch(opcao) {
            case 1:
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por NOME!\n");
                mostrarComponentes(componentes, total);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;
            case 2:
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por TIPO!\n");
                mostrarComponentes(componentes, total);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;
            case 3:
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(componentes, total);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por PRIORIDADE!\n");
                mostrarComponentes(componentes, total);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;
            case 4:
                printf("Digite o nome do componente-chave para buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                comparacoes = 0;
                int pos = buscaBinariaPorNome(componentes, total, nomeBusca);
                if (pos != -1) {
                    printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n", 
                           componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                    printf("Comparacoes realizadas na busca binaria: %d\n", comparacoes);
                } else {
                    printf("Componente NAO encontrado.\n");
                    printf("Comparacoes realizadas na busca binaria: %d\n", comparacoes);
                }
                break;
            case 5:
                mostrarComponentes(componentes, total);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

//-----------------------------
// Funções
//-----------------------------

// Cadastro de componentes
void cadastrarComponentes(Componente comps[], int *total) {
    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", total);
    getchar(); // limpar buffer

    if(*total > MAX_COMPONENTES) *total = MAX_COMPONENTES;

    for(int i=0; i<*total; i++) {
        printf("\nComponente %d\n", i+1);
        printf("Nome: ");
        fgets(comps[i].nome, sizeof(comps[i].nome), stdin);
        comps[i].nome[strcspn(comps[i].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(comps[i].tipo, sizeof(comps[i].tipo), stdin);
        comps[i].tipo[strcspn(comps[i].tipo, "\n")] = 0;

        printf("Prioridade (1 a 10): ");
        scanf("%d", &comps[i].prioridade);
        getchar(); // limpar buffer
    }
}

// Mostrar todos os componentes
void mostrarComponentes(Componente comps[], int n) {
    printf("\n=== Componentes ===\n");
    for(int i=0; i<n; i++) {
        printf("%d - Nome: %s | Tipo: %s | Prioridade: %d\n", 
               i+1, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
}

// Bubble Sort por Nome
void bubbleSortNome(Componente comps[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            comparacoes++;
            if(strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                Componente temp = comps[j];
                comps[j] = comps[j+1];
                comps[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por Tipo
void insertionSortTipo(Componente comps[], int n) {
    for(int i=1; i<n; i++) {
        Componente key = comps[i];
        int j = i - 1;
        while(j >= 0) {
            comparacoes++;
            if(strcmp(comps[j].tipo, key.tipo) > 0) {
                comps[j+1] = comps[j];
                j--;
            } else {
                break;
            }
        }
        comps[j+1] = key;
    }
}

// Selection Sort por Prioridade
void selectionSortPrioridade(Componente comps[], int n) {
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++) {
            comparacoes++;
            if(comps[j].prioridade < comps[min_idx].prioridade)
                min_idx = j;
        }
        Componente temp = comps[i];
        comps[i] = comps[min_idx];
        comps[min_idx] = temp;
    }
}

// Busca binária por Nome (assumindo vetor ordenado por nome)
int buscaBinariaPorNome(Componente comps[], int n, char nome[]) {
    int inicio = 0, fim = n-1;
    while(inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim)/2;
        int cmp = strcmp(comps[meio].nome, nome);
        if(cmp == 0)
            return meio;
        else if(cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
