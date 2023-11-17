/*
Aluno: Rodrigo Otávio Cantanhede Costa
dll.h: Arquivo de especificação denominado "dll.h".
Estrutura de Dados I - Professor Anselmo.
*/

#ifndef _DLL_H_
#define _DLL_H_

typedef struct {
    char nome[30];
    int ano;
    float notaImdb;
} Filme;

typedef struct _dlnode_
{
    struct _dlnode_ *next, *prev;
    Filme *data;
}DLNode;

typedef struct _dllist_
{
    DLNode *first;
    DLNode *cur;
}DLList;

DLList *dllCreate();
int dllDestroy(DLList *l); //so em lista vazia
int dllInsertAsFirst ( DLList *l, Filme *data);
int dllInsertAsLast(DLList *l, Filme *data);
void * dllRemoveSpec(DLList *l, Filme *key, int (*cmp)(Filme *, Filme *));
void * dllGetFirst(DLList *l);
void * dllGetNext(DLList *l);
void dllClear(DLList *l);
// void *dllFind(DLList *l, Filme *key, int (*cmp)(Filme *, Filme *, int), int opcaoConsulta);
DLList* dllFindAll(DLList *l, Filme *key, int (*cmp)(Filme *, Filme *, int), int opcaoConsulta);

#endif