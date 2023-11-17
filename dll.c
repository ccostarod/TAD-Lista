/*
Aluno: Rodrigo Otávio Cantanhede Costa
dll.c: Arquivo de implementação denominado "dll.c".
Estrutura de Dados I - Professor Anselmo.
*/

#include "dll.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

DLList *dllCreate(){
    DLList *l;
    l = (DLList *)malloc(sizeof(DLList));
    if (l != NULL){
        l->first = NULL;
        l->cur = NULL;
        return l;
    }
    return NULL;
}

int dllDestroy(DLList *l){
    if (l != NULL){
        if (l->first == NULL){
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

int dllInsertAsFirst(DLList *l, Filme *data){
    DLNode *newnode, *next;
    if (l != NULL){
        newnode = (DLNode *)malloc(sizeof(DLNode));
        if (newnode != NULL){
            newnode->data = data;
            newnode->next = l->first;
            newnode->prev = NULL;
            next = l->first;
            if (next != NULL){
                next->prev = newnode;
            }
            l->first = newnode;
            return TRUE;
        }
    }
    return FALSE;
}

int dllInsertAsLast(DLList *l, Filme* data){
    DLNode *newnode, *last;
    if (l != NULL){
        if (l->first == NULL){
            last = NULL;
        }
        else{
            last = l->first;
            while(last->next != NULL){
                last = last->next;
            }
        }
        newnode = (DLNode *)malloc(sizeof(DLNode));
        if (newnode != NULL){
            newnode->data = data;
            newnode->next = NULL;
            newnode->prev = last;
        }
        if (last == NULL){
            l->first = newnode;
        }
        else{
            last->next = newnode;
        }
        return TRUE;
    }
    return FALSE;
}

void *dllRemoveSpec(DLList *l, Filme *key, int (*cmp)(Filme *, Filme *)) {
    DLNode *current = l->first;

    while (current != NULL) {
        if (cmp(current->data, key) == TRUE) {
            void *data = current->data;
            DLNode *prev = current->prev;
            DLNode *next = current->next;

            if (prev != NULL) {
                prev->next = next;
            } else {
                l->first = next;
            }

            if (next != NULL) {
                next->prev = prev;
            }

            free(current);
            return data;
        }
        current = current->next;
    }

    return NULL; // Retorna NULL se o filme não for encontrado
}

void * dllGetFirst(DLList *l){
    if (l != NULL){
        l->cur = l->first;
        if (l->first != NULL){
            return l->cur->data;
        }
    }
    return NULL;
}

void * dllGetNext(DLList *l){
    if (l != NULL){
        if (l->cur != NULL){
            l->cur = l->cur->next;
            if (l->cur != NULL){
                return l->cur->data;
            }
        }
    }
    return NULL;
}

void dllClear(DLList *l) {
    if (l != NULL) {
        DLNode *current = l->first;
        DLNode *next;

        while (current != NULL) {
            next = current->next;
            free(current->data);
            free(current);
            current = next;
        }

        l->first = NULL;
        l->cur = NULL;
    }
}

void *dllFind(DLList *l, Filme *key, int (*cmp)(Filme *, Filme *)) {
    DLNode *current = l->first;

    while (current != NULL) {
        if (cmp(current->data, key) == TRUE) {
            return current->data; // Retorna o filme encontrado
        }
        current = current->next;
    }

    return NULL; // Retorna NULL se o filme não for encontrado
}
