#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#define TRUE 1
#define FALSE 0

// Função de comparação para encontrar um Filme na coleção
int compareFilmes(Filme *filme, Filme *key);
void printFilm(Filme *filme);
int main() {
    DLList *colecao = NULL;
    
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Criar colecao\n");
        printf("2. Inserir Filme\n");
        printf("3. Remover Filme\n");
        printf("4. Consultar Filme\n");
        printf("5. Listar Filmes\n");
        printf("6. Destruir colecao\n");
        printf("7. Esvaziar colecao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Criar colecao
                if (colecao == NULL) {
                    colecao = dllCreate();
                    printf("Colecao criada.\n");
                } else {
                    printf("A colecao ja foi criada.\n");
                }
                break;

            case 2: // Inserir Filme
                if (colecao != NULL) {
                    Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
                    while (getchar() != '\n');
                    printf("Digite o nome do filme: ");
                    fgets(novoFilme->nome, sizeof(novoFilme->nome), stdin);
                    novoFilme->nome[strcspn(novoFilme->nome, "\n")] = '\0';
                    printf("Digite o ano do filme: ");
                    scanf("%d", &novoFilme->ano);
                    printf("Digite a nota do filme: ");
                    scanf("%f", &novoFilme->notaImdb);

                    dllInsertAsLast(colecao, novoFilme);
                    printf("Filme inserido na colecao.\n");
                } else {
                    printf("Crie a colecao primeiro.\n");
                }
                break;

            case 3: // Remover Filme
                if (colecao != NULL && colecao->first != NULL) {
                    while (getchar() != '\n');
                    Filme consultaFilme;
                    printf("Digite o nome do filme: ");
                    fgets(consultaFilme.nome, sizeof(consultaFilme.nome), stdin);
                    consultaFilme.nome[strcspn(consultaFilme.nome, "\n")] = '\0';
                    // scanf("%s", consultaFilme.nome);
                    printf("Digite o ano do filme: ");
                    scanf("%d", &consultaFilme.ano);
                    printf("Digite a nota do filme: ");
                    scanf("%f", &consultaFilme.notaImdb);
                    
                    Filme *filmeRemovido = dllRemoveSpec(colecao, &consultaFilme, compareFilmes);
                    if (filmeRemovido != NULL) {
                        printf("Filme removido da colecao:\n");
                        printFilm(filmeRemovido);
                        free(filmeRemovido);
                    } else {
                        printf("Filme nao encontrado na colecao.\n");
                    }
                } else {
                    printf("Crie a colecao primeiro ou coloque alguem na colecao.\n");
                }
                break;

            case 4: // Consultar Filme
                if (colecao != NULL && colecao->first != NULL) {
                    Filme consultaFilme;
                    while (getchar() != '\n');
                    printf("Digite o nome do filme: ");
                    fgets(consultaFilme.nome, sizeof(consultaFilme.nome), stdin);
                    consultaFilme.nome[strcspn(consultaFilme.nome, "\n")] = '\0';
                    // scanf("%s", consultaFilme.nome);
                    printf("Digite o ano do filme: ");
                    scanf("%d", &consultaFilme.ano);
                    printf("Digite a nota do filme: ");
                    scanf("%f", &consultaFilme.notaImdb);

                    Filme *filmeEncontrado = dllFind(colecao, &consultaFilme, compareFilmes);
                    if (filmeEncontrado != NULL) {
                        printf("Filme encontrado na colecao:\n");
                        printFilm(filmeEncontrado);
                    } else {
                        printf("Filme nao encontrado na colecao.\n");
                    }
                } else {
                    printf("Crie a colecao primeiro ou coloquye alguem na colecao.\n");
                }
                break;

            case 5: // Listar Filmes
                if (colecao != NULL) {
                    printf("Lista de Filmes:\n");
                    Filme *filmeAtual = (Filme *)dllGetFirst(colecao);
                    while (filmeAtual != NULL) {
                        printFilm(filmeAtual);
                        filmeAtual = (Filme *)dllGetNext(colecao);
                    }
                } else {
                    printf("Crie a colecao primeiro.\n");
                }
                break;

            case 6: // Destruir colecao
                if (colecao != NULL) {
                    int destruir = dllDestroy(colecao);
                    if (destruir != 0){
                        printf("Colecao destruida.\n");
                        colecao = NULL;
                    }
                    else{
                        printf("Esvazie a colecao primeiro.\n");
                    }
                } else {
                    printf("A colecao nao existe.\n");
                }
                break;

            case 7: // Esvaziar colecao
                if (colecao != NULL) {
                    dllClear(colecao);
                    printf("Colecao esvaziada.\n");
                } else {
                    printf("Crie a colecao primeiro.\n");
                }
                break;

            case 0: // Sair
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
int compareFilmes(Filme *filme, Filme *key) {
    Filme *f1 = filme;
    Filme *f2 = key;

    // Comparar pelo nome, ano e notaImdb
    if (strcmp(f1->nome, f2->nome) == 0 && f1->ano == f2->ano && f1->notaImdb == f2->notaImdb) {
        return TRUE;
    }

    return FALSE;
}

// Função para imprimir um Filme
void printFilm(Filme *filme) {
    printf("%s, %d, %.2f\n", filme->nome, filme->ano, filme->notaImdb);
}