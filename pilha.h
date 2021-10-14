#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct nó
typedef struct no {
    int item;
    struct no *proximo;
} No;

//Struct pilha
typedef struct pilha {
    No *primeiro;
    int num_bolas;
} Pilha;


Pilha *cria_pilha(); // Cria uma nova pilha
void insere_pilha(Pilha *p, int novo_item); // Insere novo item na pilha
int pilha_verifica(Pilha* p); // Verifica se pilha está vazia, retorna 0 caso esteja ou retorna 1 caso não
int retira_pilha(Pilha *p); // Retira item da pilha e retorna valor do item
void pilha_libera (Pilha *p); // Libera memória ocupada por pilha


#endif // PILHA_H_INCLUDED
