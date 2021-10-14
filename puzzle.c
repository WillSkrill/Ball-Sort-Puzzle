#include "puzzle.h"


//////////////////////////////////////
////////INICIA JOGO COM PUZZLE////////
//////////////////////////////////////

Historico* inicia_jogo(Historico *vetor_historico, int *jogos)
{
    // Cria vetor de ponteiros para pilhas vazio
    Pilha **vetor_pilhas = NULL;

    for(;;)
    {
        system("cls"); // Limpa a tela

        yellow();
        printf("      Utilize '-1' para cancelar.\n");
        printf("Digite o número de tubos: (entre 6 e 12)\n\n");
        printf("-> ");
        reset();

        // Recebe input do número de tubos que o puzzle deve ter
        int num_tubos = filtraInteiro();

        system("cls"); // Limpa a tela

        // Se usuário digitar '-1' cancela e volta para menu
        if (num_tubos==-1)
        {
            return vetor_historico; // Retorna para menu
        }

        // Se usuário digitar um número de tubos válido
        else if ((num_tubos>=6) && (num_tubos<=12))
        {
            // Cria puzzle
            vetor_pilhas = cria_puzzle(vetor_pilhas, num_tubos);

            // Acrescenta 1 na variável 'jogos' no main
            *jogos = *jogos + 1;

            vetor_historico = (Historico*) realloc(vetor_historico,(*jogos) * sizeof(Historico)); // Aloca no vetor_historico espaço para mais um historico
            vetor_historico[*jogos-1].num_tubos = num_tubos; // Guarda número de tubos escolhido, dentro deste novo histórico
            vetor_historico[*jogos-1].movimentos = 0; // Zera número de movimentos do histórico
            vetor_historico[*jogos-1].venceu = 0; // Define que usuário ainda não venceu

            // Vai para menu de jogadas
            vetor_historico[*jogos-1] = joga_jogo(vetor_pilhas, num_tubos, vetor_historico[*jogos-1]);

            // Volta para menu principal quando acabar
            return vetor_historico;
        }

        // Caso usuário digite um número de tubos inválido
        else
        {
            // Mensagem de erro
            red();
            printf("Digite um número válido!\n\n");
            reset();

            system("pause");
        }
    }
}



//////////////////////////////////////
/////////CRIA PUZZLE ALEATÓRIO////////
//////////////////////////////////////

Pilha** cria_puzzle(Pilha **vetor_pilhas, int num_tubos)
{
    srand(time(NULL));

    for(;;)
    {
        int verif = 0;

        // Vetor com todos os números possíveis de dentro das pilhas
        int vet[40] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10};

        // Repete até criar todas as pilhas desejadas
        for (int cont=0; cont<num_tubos; cont++)
        {
            // Aloca espaço para nova pilha no vetor de pilhas
            vetor_pilhas = (Pilha**) realloc(vetor_pilhas,(cont+1) * sizeof(Pilha*));

            // Aloca nova pilha e inicializa zerada
            vetor_pilhas[cont] = cria_pilha();

            // Preenche tubos com números aleatórios (só até num_tubos-2, pois dois tubos devem ser vazios)
            if(cont<num_tubos-2)
            {
                int cont_igual = 0;
                int primeiro_pilha;
                // Repete até preencher pilha com 4 elementos
                for (int cont2 = 1; cont2<=4;)
                {
                    // Variável 'pos' recebe valor aleatório entre 0 e (num_tubos - 2) * 4
                    // Definindo de qual posição do vetor 'vet' se deve pegar o valor
                    int pos = rand() % ((num_tubos - 2) * 4);

                    // Se a posição do vetor 'vet' for diferente de 0, insere valor de vet[pos] na pilha
                    // Se for igual a zero, repete até encontrar
                    if (vet[pos] != 0)
                    {
                        // Se for o primeiro da pilha
                        if (cont2==1)
                        {
                            // Guarda o primeiro valor inserido na pilha
                            primeiro_pilha = vet[pos];
                        }

                        // Se o novo elemento a ser inserido na pilha for igual ao primeiro
                        if(vet[pos] == primeiro_pilha)
                        {
                            // Acrescenta mais um em 'cont_igual'
                            cont_igual++;

                            // Se cont_igual for = 4, indica que tubo atual está com todas as cores iguais
                            if(cont_igual==4)
                            {
                                verif = 1; // Verif=1 indicando que algum tubo do jogo já está completo
                            }
                        }

                        // Insere valor de vet[pos] na pilha
                        insere_pilha(vetor_pilhas[cont], vet[pos]);

                        // Posição do vetor é zerada
                        vet[pos] = 0;

                        // Acrescenta 1 no segundo contador, indicando que deve ir pode ir pro próximo elemento da pilha
                        cont2++;
                    }
                }
            }
        }

        // Se algum tubo estiver completo com cores iguais
        if (verif == 1)
        {
            // Libera jogo e refaz todo o puzzle
            libera_jogo(vetor_pilhas, num_tubos);
            vetor_pilhas = NULL;
        }

        // Caso nenhum tubo esteja completo
        else
        {
            // Retorna vetor_pilhas
            return vetor_pilhas;
        }
    }
}



//////////////////////////////////////
////////////JOGADAS DO JOGO///////////
//////////////////////////////////////

Historico joga_jogo(Pilha **vetor_pilhas, int num_tubos, Historico hist)
{
    int verif2 = 0;

    for(;;)
    {
        //Printa todos os tubos
        print_puzzle(vetor_pilhas, num_tubos, hist);

        printf("         Use '-1' para desistir e voltar\n");
        yellow();
        printf("Digite o número do tubo que deseja retirar uma cor:\n");
        printf("-> ");
        reset();

        // Recebe input do usuário para tubo1
        // Subtrai 1 deste número, pois vetor_pilhas começa de '0'
        int tubo1 = filtraInteiro() - 1;

        // Caso usuário digite '-1' para desistir do jogo
        if ((tubo1==-2))
        {
            libera_jogo(vetor_pilhas, num_tubos); // Libera memória das pilhas e do vetor de ponteiros para pilhas
            system("cls"); // Limpa a tela
            return hist; // Volta para menu
        }

        yellow();
        printf("\nDigite o número do tubo que deseja pôr a cor:\n");
        printf("-> ");
        reset();

        // Recebe input do usuário para tubo2
        // Subtrai 1 deste número, pois vetor_pilhas começa de '0'
        int tubo2 = filtraInteiro() - 1;

        system("cls"); // Limpa a tela

        // Caso usuário digite '-1' para desistir do jogo
        if ((tubo2==-2))
        {
            libera_jogo(vetor_pilhas, num_tubos);  // Libera memória das pilhas e do vetor de ponteiros para pilhas
            system("cls"); // Limpa a tela
            return hist; // Volta para menu
        }

        // Caso tubos digitados não existam no jogo
        else if(((tubo1>num_tubos-1) || (tubo1<0)) || ((tubo2>num_tubos-1) || (tubo2<0)))
        {
            print_puzzle(vetor_pilhas, num_tubos, hist); // Printa jogo

            // Mensagem de erro
            red();
            printf("Tubos 1 ou 2 inexistentes!\n");
            printf("Por favor, tente novamente.\n\n");
            reset();

            system("pause"); // Pausa cmd
            system("cls"); // Limpa a tela
        }

        // Caso tubos digitados sejam os mesmos
        else if(tubo1 == tubo2)
        {
            print_puzzle(vetor_pilhas, num_tubos, hist); // Printa jogo

            // Mensagem de erro
            red();
            printf("Escolha 2 tubos diferentes!\n");
            printf("Por favor, tente novamente.\n\n");
            reset();

            system("pause"); // Pausa cmd
            system("cls"); // Limpa a tela
        }

        // Caso tubos digitados sejam válidos
        else
        {
            // Tenta mover bola do tubo1 e inserir no tubo2
            // Retorna 0 caso tubo1 esteja vazio, e não faz operação
            // Retorna -1 caso tubo2 esteja cheio, e não faz operação
            // Retorna -2 caso tubos tenham topos diferentes, e não faz operação
            // Retorna 1 caso operação tenha sido um sucesso
            int verif = opera_puzzle(vetor_pilhas[tubo1], vetor_pilhas[tubo2]);

            switch (verif)
            {
            // Caso tubo1 esteja vazio
            case 0:
                print_puzzle(vetor_pilhas, num_tubos, hist); // Printa jogo

                // Mensagem de erro
                red();
                printf("Tubo %i vazio!\n", tubo1+1);
                printf("Por favor, tente novamente.\n\n");
                reset();

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela
                break;

            // Caso tubo2 esteja cheio
            case -1:
                print_puzzle(vetor_pilhas, num_tubos, hist); // Printa jogo

                // Mensagem de erro
                red();
                printf("Tubo %i cheio!\n", tubo2+1);
                printf("Por favor, tente novamente.\n\n");
                reset();

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela
                break;

            // Caso tubos tenham topos diferentes
            case -2:
                print_puzzle(vetor_pilhas, num_tubos, hist); // Printa jogo

                // Mensagem de erro
                red();
                printf("Jogada incompatível! (Tubos com cores diferentes no topo)\n");
                printf("Por favor, tente novamente.\n\n");
                reset();

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela
                break;

            // Caso operação tenha sido um sucesso
            default:
                // Verifica se usuário venceu o jogo
                // Retorna 1 se venceu
                // Retorna -1 se ainda não venceu
                verif2 = verif_puzzle(vetor_pilhas, num_tubos);
                // Acrescenta +1, no número de movimentos, no histórico
                hist.movimentos = hist.movimentos + 1;
                break;
            }

            // Se verif2 for igual a 1, indicando que o usuário venceu
            if (verif2==1)
            {
                // Guarda no histórico que usuário venceu
                hist.venceu=1;

                // Printa jogo
                print_puzzle(vetor_pilhas, num_tubos, hist);
                // Mensagem de sucesso
                green();
                printf("Parabéns, você venceu!\n\n");
                reset();

                // Libera memória das pilhas e do vetor de ponteiros para pilhas
                libera_jogo(vetor_pilhas, num_tubos);

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela

                return hist; // Sai da função
            }
        }
    }
}



//////////////////////////////////////
///////////////OPERAÇAO///////////////
//////////////////////////////////////

int opera_puzzle(Pilha *pilha1, Pilha *pilha2)
{
    // Verifica se pilha1 está vazia
    // Retorna 0 caso esteja vazia
    int verif = pilha_verifica(pilha1);

    // Se pilha for vazia
    if (verif==0)
    {
        return 0;
    }

    // Se pilha2 estiver cheia
    else if (pilha2->num_bolas==4)
    {
        return -1;
    }

    // Se pilha2 não for vazia
    else if (pilha2->num_bolas != 0)
    {
        // Se ambas as pilhas não tiverem seu topo igual
        if (pilha1->primeiro->item != pilha2->primeiro->item)
        {
            return -2;
        }
    }

    // Caso nenhuma das opções acima tenham ocorrido
    // Retira nó da pilha1 e guarda valor na variável 'item'
    int item = retira_pilha(pilha1);

    // Insere na pilha2 o item retirado da pilha1
    insere_pilha(pilha2, item);

    // Retorna 1 indicando que operação foi um sucesso
    return 1;
}



//////////////////////////////////////
///////////VERIFICA PUZZLE////////////
//////////////////////////////////////

int verif_puzzle(Pilha **vetor_pilhas, int num_pilhas)
{
    // Cria um auxiliar para cada pilha existente em vetor_pilhas
    No* aux[num_pilhas];

    // Repete até passar por todas as pilhas
    for (int x=0; x<num_pilhas; x++)
    {
        // Aponta auxiliar para sua pilha correspondente
        aux[x] = vetor_pilhas[x]->primeiro;
    }


    for(int x=0; x<num_pilhas; x++)
    {
        // Se pilha não for vazia
        if (aux[x]!=NULL)
        {
            // Guarda primeiro item da pilha
            int prim_item = aux[x]->item;

            // Repete até chegar no último elemento da pilha
            for (int y=0; ; y++)
            {
                // Se elemento atual for igual ao primeiro item da pilha
                if (aux[x]->item == prim_item)
                {
                    // Caso este seja o último da pilha, mas não seja o quarto elemento (Indicando que tubo ainda não está completo)
                    if ((aux[x]->proximo == NULL) && (y<3))
                    {
                        // Retorna -1 indicando que pilha não está completa e que o jogo não terminou
                        return -1;
                    }

                    // Se elemento atual seja o último da pilha e também seja o quarto elemento
                    else if ((aux[x]->proximo == NULL) && (y==3))
                    {
                        // Vai para próxima pilha, indicando que esta está completa
                        break;
                    }

                    // Vai para próximo elemento, até achar o final da pilha
                    else
                    {
                        aux[x] = aux[x]->proximo;
                    }
                }

                // Se elemento atual não for igual ao primeiro da pilha
                else
                {
                    // Retorna -1 indicando que pilha não está completa e que o jogo não terminou
                    return -1;
                }
            }
        }
    }

    // Retorna 1 indicando que o usuário venceu o jogo
    return 1;
}



//////////////////////////////////////
////////////LIBERA PUZZLE/////////////
//////////////////////////////////////

void libera_jogo(Pilha **vetor_pilhas, int num_pilhas)
{
    // Repete até liberar todas as pilhas do vetor_pilhas
    for(int x=0; x<num_pilhas; x++)
    {
        // Libera pilha atual
        pilha_libera (vetor_pilhas[x]);
    }

    // Libera vetor_pilhas
    free(vetor_pilhas);
}



//////////////////////////////////////
////////////PRINTA PUZZLE/////////////
//////////////////////////////////////

void print_puzzle(Pilha **vetor_pilhas, int num_pilhas, Historico hist)
{
    // Cria um auxiliar para cada pilha existente em vetor_pilhas
    No* aux[num_pilhas];

    // Repete até passar por todas as pilhas
    for (int x = 0; x<num_pilhas; x++)
    {
        // Aponta auxiliar para sua pilha correspondente
        aux[x] = vetor_pilhas[x]->primeiro;
    }

    // Repete por 4 linhas
    for (int x = 0; x<4; x++)
    {
        int verif = 0;

        // Repete até chegar na última pilha
        for (int y = 0; y<num_pilhas; y++)
        {
            // Caso pilha atual possua menos bolas do do que 4-x (feito para bolas não ficarem sendo sempre printadas a partir do topo do tubo)
            if (vetor_pilhas[y]->num_bolas < 4-x)
            {
                yellow();
                printf("|   |  ");
                reset();
            }

            // Se auxiliar atual não for vazio, printa item atual dele
            else if (aux[y]!=NULL)
            {
                // Printa item de auxiliar
                yellow();
                printf("|");
                reset();

                cores_tubo(aux[y]->item); // Função que printa cor correspondente ao número

                yellow();
                printf("|  ");
                reset();
            }

            // Se auxiliar for vazio
            else
            {
                // Printa espaço em branco
                yellow();
                printf("|   |  ");
                reset();
            }

            if ((x==2) && (y==num_pilhas-1))
            {
                yellow();
                printf("Número de jogadas: ");
                reset();
                printf("%i", hist.movimentos);
            }

            // Se já printou conteúdo atual de todas as pilhas, pula para próxima linha
            if (y==num_pilhas-1)
            {
                printf("\n");
                verif = 1;
            }
        }

        // Se foi para próxima linha
        if (verif==1)
        {
            // Repete até passar por todas as pilhas
            for (int z = 0; z<num_pilhas; z++)
            {
                // Se auxiliar atual não for NULL
                if(aux[z] != NULL)
                {
                    // Feito para atualizar apenas se algum elemento da pilha foi printado anteriormente
                    // (feito para bolas não ficarem sendo sempre printadas a partir do topo do tubo)
                    if (vetor_pilhas[z]->num_bolas >= 4-x)
                    {
                        // Auxiliar aponta para próximo da pilha
                        aux[z] = aux[z]->proximo;
                    }
                }
            }
        }
    }

    // Depois de printar todos os elementos de todas as pilhas, printa fundo dos tubos
    for (int x = 0; x<num_pilhas; x++)
    {
        yellow();
        printf("|___|  ");
        reset();
    }

    // Pula linha
    printf("\n");

    // Printa numeração dos tubos
    for (int x = 1; x<=num_pilhas; x++)
    {
        yellow();
        printf("  %-2i   ", x);
        reset();
    }

    // Pula 3 linhas
    printf("\n\n\n");
}



//////////////////////////////////////
/////////////PRINTA MENU//////////////
//////////////////////////////////////

void print_menu()
{
    system("cls");
    printf("  \e[4;33mEscolha uma das opções abaixo\n");
    reset();

    yellow();
    printf(" _______________________________\n");
    reset();

    yellow();
    printf("| |                             |\n");
    reset();

    yellow();
    printf("|");
    reset();

    printf("\e[0;33m1");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Iniciar jogo                ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    printf("\e[0;33m2");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Histórico                   ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    printf("\e[0;33m3");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Manual                      ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|");
    reset();

    red();
    printf("4");
    reset();

    yellow();
    printf("|");
    reset();

    printf(" Sair                        ");

    yellow();
    printf("|\n");
    reset();

    yellow();
    printf("|_|_____________________________|\n\n");
    printf("-> ");
    reset();
}



//////////////////////////////////////
///////////PRINTA HISTÓRICO///////////
//////////////////////////////////////

void print_historico(Historico *vetor_historico, int jogos)
{
    int verif = 0;

    printf("        \e[4;37mHISTÓRICO\n");
    reset();

    // Repete até passar por todas structs em vetor_historico
    for (int x=0; x<jogos; x++)
    {
        yellow();
        printf(" ________________________ \n");
        printf("|                        |\n");
        printf("| Número de tubos:   %-2i  |\n", vetor_historico[x].num_tubos); // Printa número de tubos
        printf("| Número de jogadas: %-3i |", vetor_historico[x].movimentos); // Printa número de movimentos
        printf("  JOGO %i\n", x+1);
        printf("| Venceu: ");

        // Caso usuário tenha vencido esse jogo (vetor_historico[x].venceu = 1)
        if (vetor_historico[x].venceu)
        {
            printf("SIM            |\n");
        }
        // Caso usuário tenha perdido esse jogo (vetor_historico[x].venceu = 0)
        else
        {
            printf("NÃO            |\n");
        }

        printf("|________________________|\n\n");
        reset();


        verif = 1; // Verificador = 1, indicando que houve pelo menos 1 jogo
    }

    // Caso não tenha tido nenhum jogo
    if (verif==0)
    {
        // Mensagem de erro
        red();
        printf("Não houve nenhum jogo até agora!\n\n");
        reset();
    }

    system("pause"); // Pausa sistema
}



//////////////////////////////////////
////////////PRINTA MANUAL/////////////
//////////////////////////////////////

void print_manual()
{
    printf("                              \e[4;33mOBJETIVO:\n\n");
    reset();

    printf("                Ball Sort Puzzle é um jogo estratégico,\n");
    printf(" onde seu único objetivo é deixar todos os tubos com apenas uma cor dentro!\n\n\n");

    printf("                             \e[4;33mCOMO JOGAR:\n\n");
    reset();

    printf(". Escolha um tubo que queira remover uma cor, e a coloque no topo de outro tubo.\n");
    printf(". A regra é que você só pode mover uma cor para cima de outra cor igual.\n");
    printf(". Você sempre pode mover uma cor para um tubo vazio.\n");
    printf(". Quanto mais tubos, mais difícil o jogo se torna.\n");
    printf(". Cuidado com seus movimentos, você pode acabar ficando preso no jogo.\n");
    printf(". Não se preocupe, caso fique preso, é possível começar outro jogo.\n");
    printf(". Para vencer, sempre haverão dois tubos completamente vazios.\n\n");

    system("pause");
}







