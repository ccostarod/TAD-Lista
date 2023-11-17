
/*
Aluno: Rodrigo Otávio Cantanhede Costa
main.c: Arquivo de visualizacao denominado "main.c".
Estrutura de Dados I - Professor Anselmo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#define TRUE 1
#define FALSE 0

// Função de comparação para encontrar um Filme na coleção
int compareFilmes(Filme *filme, Filme *key);
int compareFilmesConsulta(Filme *filme, Filme *key, int opcaoConsulta);
void printFilm(Filme *filme);
void printFilmList(DLList *l);
int main() {
    DLList *colecao = NULL;
    printf("----------------Acervo de Filmes do Rodrigo----------------");
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Criar colecao\n");
        printf("2. Inserir Filme\n");
        printf("3. Remover Filme\n");
        printf("4. Consultar Filmes\n");
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
                int opcaoConsulta;
                printf("Escolha o criterio de consulta:\n");
                printf("1. Nome\n");
                printf("2. Ano de Lancamento\n");
                printf("3. Nota do Filme\n");
                scanf("%d", &opcaoConsulta);

                Filme consultaFilme;

                switch (opcaoConsulta) {
                    case 1:
                        printf("Digite o nome do filme: ");
                        while (getchar() != '\n');
                        fgets(consultaFilme.nome, sizeof(consultaFilme.nome), stdin);
                        consultaFilme.nome[strcspn(consultaFilme.nome, "\n")] = '\0';
                        break;

                    case 2:
                        printf("Digite o ano do filme: ");
                        scanf("%d", &consultaFilme.ano);
                        break;

                    case 3:
                        printf("Digite a nota do filme: ");
                        scanf("%f", &consultaFilme.notaImdb);
                        break;

                    default:
                        printf("Opcao invalida.\n");
                        return;
                }
                DLList *filmesEncontrados = dllFindAll(colecao, &consultaFilme, compareFilmesConsulta, opcaoConsulta);

                if (filmesEncontrados != NULL && filmesEncontrados->first != NULL) {
                    printf("Filmes encontrados na colecao:\n");
                    printFilmList(filmesEncontrados);
                } else {
                    printf("Nenhum filme encontrado na colecao com essa caracteristica de pesquisa.\n");
                }
                } else {
                    printf("Crie a colecao primeiro ou coloque alguém na colecao.\n");
                }
                break;

            case 5: // Listar Filmes
                if (colecao != NULL) {
                    if (colecao->first != NULL){
                        printf("Lista de Filmes:\n");
                        Filme *filmeAtual = (Filme *)dllGetFirst(colecao);
                        while (filmeAtual != NULL) {
                            printFilm(filmeAtual);
                            filmeAtual = (Filme *)dllGetNext(colecao);
                        }
                    }
                    else{
                        printf("Nao ha filmes na colecao para serem listados!\n");
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

    // Comparar pelo nome, ano e notaImdb (Remocao)
    if (strcmp(f1->nome, f2->nome) == 0 && f1->ano == f2->ano && f1->notaImdb == f2->notaImdb) {
        return TRUE;
    }

    return FALSE;
}

int compareFilmesConsulta(Filme *filme, Filme *key, int opcaoConsulta) { //Para consulta
    Filme *f1 = filme;
    Filme *f2 = key;

    switch (opcaoConsulta) {
        case 1: // Nome
            return strcmp(f1->nome, f2->nome) == 0;

        case 2: // Ano de Lançamento
            return f1->ano == f2->ano;

        case 3: // Nota do Filme
            return f1->notaImdb == f2->notaImdb;

        default:
            return FALSE;
    }
}

// Função para imprimir um Filme
void printFilm(Filme *filme) {
    printf("%s, %d, %.2f\n", filme->nome, filme->ano, filme->notaImdb);
}
//Função para imprimri uma lista de Filmes (Usado na consulta)
void printFilmList(DLList *l) {
    DLNode *current = l->first;

    while (current != NULL) {
        printFilm(current->data);
        current = current->next;
    }
}