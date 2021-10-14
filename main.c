#include "pilha.h"
#include "puzzle.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int menu = 0; // Op��o do menu
    int jogos = 0; // N�mero de jogos jogados

    // Cria Hist�rico
    Historico *vetor_historico = NULL;

    for (;;)
    {
        // Limpa tela
        system("cls");

        // Printa menu principal
        print_menu();

        // Recebe intput do menu e filtra (caso o usu�rio digite algo que n�o seja um inteiro)
        menu = filtraInteiro();

        // Limpa tela
        system("cls");

        switch (menu)
        {
        case 1:
            vetor_historico = inicia_jogo(vetor_historico, &jogos); // Fun��o que chama todas as outras relacionadas ao jogo e retorna
            break;

        case 2:
            print_historico(vetor_historico, jogos); // Fun��o que printa hist�rico de todas as partidas
            break;

        case 3:
            print_manual(); // Fun��o que printa manual
            break;

        case 4:
            return 0; // Sai do programa
            break;

        // Caso o usu�rio digite um n�mero/input inexistente no menu
        default:
            // Printa menu principal
            print_menu();

            // Mensagem de erro
            red();
            printf("Digite algo que corresponda a uma op��o existente!\n\n");
            reset();

            // Pausa e limpa a tela
            system("pause");
            system("cls");
            break;
        }
    }
}
