#ifndef PUZZLE_H_INCLUDED
#define PUZZLE_H_INCLUDED

#include "pilha.h"
#include <locale.h>

// Struct hist�rico
typedef struct historico {
    int num_tubos; // N�mero total de tubos escolhido no jogo atual
    int movimentos; // Total de movimentos feitos pelo usu�rio at� vencer, ou desistir do jogo
    int venceu; // Define se usu�rio venceu, 1 caso tenha vencido e 0 caso o contr�rio
} Historico;

Historico* inicia_jogo(); // Cria um jogo e inicia, e chama outras fun��es que manipulam o jogo, retorna um hist�rico com informa��es da partida
Pilha** cria_puzzle(Pilha **vetor_pilhas, int num_tubos); // � chamada em inicia_jogo(), cria um puzzle aleat�rio com o n�mero de tubos desejados
Historico joga_jogo(Pilha **vetor_pilhas, int num_tubos, Historico hist); // � chamada em inicia_jogo(), recebe input do usu�rio para jogar o jogo
int opera_puzzle(Pilha *pilha1, Pilha *pilha2); // � chamada em joga_jogo, tenta pegar item em pilha1 e colocar em pilha 2, retorna 1 caso tenha sido um sucesso
int verif_puzzle(Pilha **vetor_pilhas, int num_pilhas); // Verifica se usu�rio venceu o jogo
void libera_jogo(Pilha **vetor_pilhas, int num_pilhas); // Libera mem�ria ocupada por puzzle
void print_puzzle(Pilha **vetor_pilhas, int num_pilhas, Historico hist); // Printa puzzle com todos os tubos
void print_menu(); // Printa menu principal do main
void print_historico(Historico *vetor_historico, int jogos); // Printa hist�rico de partidas
void print_manual(); // Printa manual de como o jogo funciona



// Fun��es de aux�lio
int filtraInteiro(); // Filtra input do usu�rio

// Fun��es de cor
void red();
void green();
void yellow();
void reset();
void cores_tubo(int num); // Printa uma cor espec�fica de acordo com o n�mero recebido


#endif // PUZZLE_H_INCLUDED
