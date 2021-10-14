#include "pilha.h"
#include "puzzle.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int menu = 0; // Opção do menu
    int jogos = 0; // Número de jogos jogados

    // Cria Histórico
    Historico *vetor_historico = NULL;

    for (;;)
    {
        // Limpa tela
        system("cls");

        // Printa menu principal
        print_menu();

        // Recebe intput do menu e filtra (caso o usuário digite algo que não seja um inteiro)
        menu = filtraInteiro();

        // Limpa tela
        system("cls");

        switch (menu)
        {
        case 1:
            vetor_historico = inicia_jogo(vetor_historico, &jogos); // Função que chama todas as outras relacionadas ao jogo e retorna
            break;

        case 2:
            print_historico(vetor_historico, jogos); // Função que printa histórico de todas as partidas
            break;

        case 3:
            print_manual(); // Função que printa manual
            break;

        case 4:
            return 0; // Sai do programa
            break;

        // Caso o usuário digite um número/input inexistente no menu
        default:
            // Printa menu principal
            print_menu();

            // Mensagem de erro
            red();
            printf("Digite algo que corresponda a uma opção existente!\n\n");
            reset();

            // Pausa e limpa a tela
            system("pause");
            system("cls");
            break;
        }
    }
}
