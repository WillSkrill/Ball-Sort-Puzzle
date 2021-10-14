#include "puzzle.h"


//////////////////////////////////////
///////////CRIA PILHA VAZIA///////////
//////////////////////////////////////

Pilha* cria_pilha()
{
    // Cria e aloca mem�ria para struct Pilha
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    // Aponta ponteiro "primeiro" para NULL
    p->primeiro = NULL;
    // N�mero de bolas zerado
    p->num_bolas = 0;
    // Retorna Pilha
    return p;
}



//////////////////////////////////////
///////INSERE NOVO N� NO TOPO/////////
//////////////////////////////////////

void insere_pilha(Pilha *p, int novo_item)
{
    // Cria novo n�
    No *novo_no = (No*) malloc(sizeof(No));
    // Insere item na struct no
    novo_no->item = novo_item;
    // Aponta variavel "proximo" para variavel primeiro da struct Pilha p
    novo_no->proximo = p->primeiro;
    // Variavel primeiro da struct pilha, aponta para novo n�
    p->primeiro = novo_no;
    // Acrescenta 1 na vari�vel num_bolas da pilha
    p->num_bolas++;
}



//////////////////////////////////////
/////VERIFICA SE PILHA EST� VAZIA/////
//////////////////////////////////////

int pilha_verifica(Pilha* p)
{
    // Se Pilha for vazia, retorna 0
    if(p->primeiro == NULL)
    {
        return 0;
    }

    // Retorna 1 caso Pilha n�o esteja vazia
    return 1;
}



//////////////////////////////////////
//////////RETIRA N� DO TOPO///////////
//////////////////////////////////////

int retira_pilha(Pilha *p)
{
    // Cria struct n� auxiliar
    No *aux;
    int item;

    // Se pila for vazia, retorna 0
    if (pilha_verifica(p) == 0)
    {
        return 0;
    }

    // Aponta struct auxiliar para primeiro n� da pilha
    aux = p->primeiro;
    // Guarda item do n� atual
    item = aux->item;
    // Primeiro n� da lista passa a ser o pr�ximo
    p->primeiro = aux->proximo;

    // Libera n� atual
    free(aux);

    // Diminui n�mero total de bolas na pilha
    p->num_bolas--;

    // Retorna item do n� retirado
    return item;
}



//////////////////////////////////////
//REMOVE TODOS OS N�S E RESETA PILHA//
//////////////////////////////////////

void pilha_libera (Pilha *p)
{
    // Cria dois n�s auxiliares
    // Aux2 aponta para topo da pilha
    No *aux, *aux2 = p->primeiro;

    // Repete enquanto pilha n�o estiver vazia
    // Libera todos os n�s
    while (aux2 != NULL)
    {
        // aux aponta para pr�ximo da pilha (um n� antes do topo)
        aux = aux2->proximo;
        // Remove aux2 que apontava para o topo da pilha
        free(aux2);
        // aux2 aponta para novo topo da pilha
        aux2 = aux;
    }

    // Libera pilha
    free(p);
}
