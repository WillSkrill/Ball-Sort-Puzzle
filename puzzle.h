#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include "pilha.h"
#include <locale.h>

// Struct histórico
typedef struct historico {
    int num_tubos; // Número total de tubos escolhido no jogo atual
    int movimentos; // Total de movimentos feitos pelo usuário até vencer, ou desistir do jogo
    int venceu; // Define se usuário venceu, 1 caso tenha vencido e 0 caso o contrário
} Historico;

Historico* inicia_jogo(); // Cria um jogo e inicia, e chama outras funções que manipulam o jogo, retorna um histórico com informações da partida
Pilha** cria_puzzle(Pilha **vetor_pilhas, int num_tubos); // É chamada em inicia_jogo(), cria um puzzle aleatório com o número de tubos desejados
Historico joga_jogo(Pilha **vetor_pilhas, int num_tubos, Historico hist); // É chamada em inicia_jogo(), recebe input do usuário para jogar o jogo
int opera_puzzle(Pilha *pilha1, Pilha *pilha2); // É chamada em joga_jogo, tenta pegar item em pilha1 e colocar em pilha 2, retorna 1 caso tenha sido um sucesso
int verif_puzzle(Pilha **vetor_pilhas, int num_pilhas); // Verifica se usuário venceu o jogo
void libera_jogo(Pilha **vetor_pilhas, int num_pilhas); // Libera memória ocupada por puzzle
void print_puzzle(Pilha **vetor_pilhas, int num_pilhas, Historico hist); // Printa puzzle com todos os tubos
void print_menu(); // Printa menu principal do main
void print_historico(Historico *vetor_historico, int jogos); // Printa histórico de partidas
void print_manual(); // Printa manual de como o jogo funciona



// Funções de auxílio
int filtraInteiro(); // Filtra input do usuário

// Funções de cor
void red();
void green();
void yellow();
void reset();
void cores_tubo(int num); // Printa uma cor específica de acordo com o número recebido


#endif // PUZZLE_H_INCLUDED
