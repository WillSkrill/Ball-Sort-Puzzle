#include "puzzle.h"


//////////////////////////////////////
///////////CRIA PILHA VAZIA///////////
//////////////////////////////////////

Pilha* cria_pilha()
{
    // Cria e aloca memória para struct Pilha
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    // Aponta ponteiro "primeiro" para NULL
    p->primeiro = NULL;
    // Número de bolas zerado
    p->num_bolas = 0;
    // Retorna Pilha
    return p;
}



//////////////////////////////////////
///////INSERE NOVO NÓ NO TOPO/////////
//////////////////////////////////////

void insere_pilha(Pilha *p, int novo_item)
{
    // Cria novo nó
    No *novo_no = (No*) malloc(sizeof(No));
    // Insere item na struct no
    novo_no->item = novo_item;
    // Aponta variavel "proximo" para variavel primeiro da struct Pilha p
    novo_no->proximo = p->primeiro;
    // Variavel primeiro da struct pilha, aponta para novo nó
    p->primeiro = novo_no;
    // Acrescenta 1 na variável num_bolas da pilha
    p->num_bolas++;
}



//////////////////////////////////////
/////VERIFICA SE PILHA ESTÁ VAZIA/////
//////////////////////////////////////

int pilha_verifica(Pilha* p)
{
    // Se Pilha for vazia, retorna 0
    if(p->primeiro == NULL)
    {
        return 0;
    }

    // Retorna 1 caso Pilha não esteja vazia
    return 1;
}



//////////////////////////////////////
//////////RETIRA NÓ DO TOPO///////////
//////////////////////////////////////

int retira_pilha(Pilha *p)
{
    // Cria struct nó auxiliar
    No *aux;
    int item;

    // Se pila for vazia, retorna 0
    if (pilha_verifica(p) == 0)
    {
        return 0;
    }

    // Aponta struct auxiliar para primeiro nó da pilha
    aux = p->primeiro;
    // Guarda item do nó atual
    item = aux->item;
    // Primeiro nó da lista passa a ser o próximo
    p->primeiro = aux->proximo;

    // Libera nó atual
    free(aux);

    // Diminui número total de bolas na pilha
    p->num_bolas--;

    // Retorna item do nó retirado
    return item;
}



//////////////////////////////////////
//REMOVE TODOS OS NÓS E RESETA PILHA//
//////////////////////////////////////

void pilha_libera (Pilha *p)
{
    // Cria dois nós auxiliares
    // Aux2 aponta para topo da pilha
    No *aux, *aux2 = p->primeiro;

    // Repete enquanto pilha não estiver vazia
    // Libera todos os nós
    while (aux2 != NULL)
    {
        // aux aponta para próximo da pilha (um nó antes do topo)
        aux = aux2->proximo;
        // Remove aux2 que apontava para o topo da pilha
        free(aux2);
        // aux2 aponta para novo topo da pilha
        aux2 = aux;
    }

    // Libera pilha
    free(p);
}
