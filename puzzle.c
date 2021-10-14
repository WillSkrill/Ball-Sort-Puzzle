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
        printf("Digite o n�mero de tubos: (entre 6 e 12)\n\n");
        printf("-> ");
        reset();

        // Recebe input do n�mero de tubos que o puzzle deve ter
        int num_tubos = filtraInteiro();

        system("cls"); // Limpa a tela

        // Se usu�rio digitar '-1' cancela e volta para menu
        if (num_tubos==-1)
        {
            return vetor_historico; // Retorna para menu
        }

        // Se usu�rio digitar um n�mero de tubos v�lido
        else if ((num_tubos>=6) && (num_tubos<=12))
        {
            // Cria puzzle
            vetor_pilhas = cria_puzzle(vetor_pilhas, num_tubos);

            // Acrescenta 1 na vari�vel 'jogos' no main
            *jogos = *jogos + 1;

            vetor_historico = (Historico*) realloc(vetor_historico,(*jogos) * sizeof(Historico)); // Aloca no vetor_historico espa�o para mais um historico
            vetor_historico[*jogos-1].num_tubos = num_tubos; // Guarda n�mero de tubos escolhido, dentro deste novo hist�rico
            vetor_historico[*jogos-1].movimentos = 0; // Zera n�mero de movimentos do hist�rico
            vetor_historico[*jogos-1].venceu = 0; // Define que usu�rio ainda n�o venceu

            // Vai para menu de jogadas
            vetor_historico[*jogos-1] = joga_jogo(vetor_pilhas, num_tubos, vetor_historico[*jogos-1]);

            // Volta para menu principal quando acabar
            return vetor_historico;
        }

        // Caso usu�rio digite um n�mero de tubos inv�lido
        else
        {
            // Mensagem de erro
            red();
            printf("Digite um n�mero v�lido!\n\n");
            reset();

            system("pause");
        }
    }
}



//////////////////////////////////////
/////////CRIA PUZZLE ALEAT�RIO////////
//////////////////////////////////////

Pilha** cria_puzzle(Pilha **vetor_pilhas, int num_tubos)
{
    srand(time(NULL));

    for(;;)
    {
        int verif = 0;

        // Vetor com todos os n�meros poss�veis de dentro das pilhas
        int vet[40] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10};

        // Repete at� criar todas as pilhas desejadas
        for (int cont=0; cont<num_tubos; cont++)
        {
            // Aloca espa�o para nova pilha no vetor de pilhas
            vetor_pilhas = (Pilha**) realloc(vetor_pilhas,(cont+1) * sizeof(Pilha*));

            // Aloca nova pilha e inicializa zerada
            vetor_pilhas[cont] = cria_pilha();

            // Preenche tubos com n�meros aleat�rios (s� at� num_tubos-2, pois dois tubos devem ser vazios)
            if(cont<num_tubos-2)
            {
                int cont_igual = 0;
                int primeiro_pilha;
                // Repete at� preencher pilha com 4 elementos
                for (int cont2 = 1; cont2<=4;)
                {
                    // Vari�vel 'pos' recebe valor aleat�rio entre 0 e (num_tubos - 2) * 4
                    // Definindo de qual posi��o do vetor 'vet' se deve pegar o valor
                    int pos = rand() % ((num_tubos - 2) * 4);

                    // Se a posi��o do vetor 'vet' for diferente de 0, insere valor de vet[pos] na pilha
                    // Se for igual a zero, repete at� encontrar
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

                            // Se cont_igual for = 4, indica que tubo atual est� com todas as cores iguais
                            if(cont_igual==4)
                            {
                                verif = 1; // Verif=1 indicando que algum tubo do jogo j� est� completo
                            }
                        }

                        // Insere valor de vet[pos] na pilha
                        insere_pilha(vetor_pilhas[cont], vet[pos]);

                        // Posi��o do vetor � zerada
                        vet[pos] = 0;

                        // Acrescenta 1 no segundo contador, indicando que deve ir pode ir pro pr�ximo elemento da pilha
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
        printf("Digite o n�mero do tubo que deseja retirar uma cor:\n");
        printf("-> ");
        reset();

        // Recebe input do usu�rio para tubo1
        // Subtrai 1 deste n�mero, pois vetor_pilhas come�a de '0'
        int tubo1 = filtraInteiro() - 1;

        // Caso usu�rio digite '-1' para desistir do jogo
        if ((tubo1==-2))
        {
            libera_jogo(vetor_pilhas, num_tubos); // Libera mem�ria das pilhas e do vetor de ponteiros para pilhas
            system("cls"); // Limpa a tela
            return hist; // Volta para menu
        }

        yellow();
        printf("\nDigite o n�mero do tubo que deseja p�r a cor:\n");
        printf("-> ");
        reset();

        // Recebe input do usu�rio para tubo2
        // Subtrai 1 deste n�mero, pois vetor_pilhas come�a de '0'
        int tubo2 = filtraInteiro() - 1;

        system("cls"); // Limpa a tela

        // Caso usu�rio digite '-1' para desistir do jogo
        if ((tubo2==-2))
        {
            libera_jogo(vetor_pilhas, num_tubos);  // Libera mem�ria das pilhas e do vetor de ponteiros para pilhas
            system("cls"); // Limpa a tela
            return hist; // Volta para menu
        }

        // Caso tubos digitados n�o existam no jogo
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

        // Caso tubos digitados sejam v�lidos
        else
        {
            // Tenta mover bola do tubo1 e inserir no tubo2
            // Retorna 0 caso tubo1 esteja vazio, e n�o faz opera��o
            // Retorna -1 caso tubo2 esteja cheio, e n�o faz opera��o
            // Retorna -2 caso tubos tenham topos diferentes, e n�o faz opera��o
            // Retorna 1 caso opera��o tenha sido um sucesso
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
                printf("Jogada incompat�vel! (Tubos com cores diferentes no topo)\n");
                printf("Por favor, tente novamente.\n\n");
                reset();

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela
                break;

            // Caso opera��o tenha sido um sucesso
            default:
                // Verifica se usu�rio venceu o jogo
                // Retorna 1 se venceu
                // Retorna -1 se ainda n�o venceu
                verif2 = verif_puzzle(vetor_pilhas, num_tubos);
                // Acrescenta +1, no n�mero de movimentos, no hist�rico
                hist.movimentos = hist.movimentos + 1;
                break;
            }

            // Se verif2 for igual a 1, indicando que o usu�rio venceu
            if (verif2==1)
            {
                // Guarda no hist�rico que usu�rio venceu
                hist.venceu=1;

                // Printa jogo
                print_puzzle(vetor_pilhas, num_tubos, hist);
                // Mensagem de sucesso
                green();
                printf("Parab�ns, voc� venceu!\n\n");
                reset();

                // Libera mem�ria das pilhas e do vetor de ponteiros para pilhas
                libera_jogo(vetor_pilhas, num_tubos);

                system("pause"); // Pausa cmd
                system("cls"); // Limpa a tela

                return hist; // Sai da fun��o
            }
        }
    }
}



//////////////////////////////////////
///////////////OPERA�AO///////////////
//////////////////////////////////////

int opera_puzzle(Pilha *pilha1, Pilha *pilha2)
{
    // Verifica se pilha1 est� vazia
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

    // Se pilha2 n�o for vazia
    else if (pilha2->num_bolas != 0)
    {
        // Se ambas as pilhas n�o tiverem seu topo igual
        if (pilha1->primeiro->item != pilha2->primeiro->item)
        {
            return -2;
        }
    }

    // Caso nenhuma das op��es acima tenham ocorrido
    // Retira n� da pilha1 e guarda valor na vari�vel 'item'
    int item = retira_pilha(pilha1);

    // Insere na pilha2 o item retirado da pilha1
    insere_pilha(pilha2, item);

    // Retorna 1 indicando que opera��o foi um sucesso
    return 1;
}



//////////////////////////////////////
///////////VERIFICA PUZZLE////////////
//////////////////////////////////////

int verif_puzzle(Pilha **vetor_pilhas, int num_pilhas)
{
    // Cria um auxiliar para cada pilha existente em vetor_pilhas
    No* aux[num_pilhas];

    // Repete at� passar por todas as pilhas
    for (int x=0; x<num_pilhas; x++)
    {
        // Aponta auxiliar para sua pilha correspondente
        aux[x] = vetor_pilhas[x]->primeiro;
    }


    for(int x=0; x<num_pilhas; x++)
    {
        // Se pilha n�o for vazia
        if (aux[x]!=NULL)
        {
            // Guarda primeiro item da pilha
            int prim_item = aux[x]->item;

            // Repete at� chegar no �ltimo elemento da pilha
            for (int y=0; ; y++)
            {
                // Se elemento atual for igual ao primeiro item da pilha
                if (aux[x]->item == prim_item)
                {
                    // Caso este seja o �ltimo da pilha, mas n�o seja o quarto elemento (Indicando que tubo ainda n�o est� completo)
                    if ((aux[x]->proximo == NULL) && (y<3))
                    {
                        // Retorna -1 indicando que pilha n�o est� completa e que o jogo n�o terminou
                        return -1;
                    }

                    // Se elemento atual seja o �ltimo da pilha e tamb�m seja o quarto elemento
                    else if ((aux[x]->proximo == NULL) && (y==3))
                    {
                        // Vai para pr�xima pilha, indicando que esta est� completa
                        break;
                    }

                    // Vai para pr�ximo elemento, at� achar o final da pilha
                    else
                    {
                        aux[x] = aux[x]->proximo;
                    }
                }

                // Se elemento atual n�o for igual ao primeiro da pilha
                else
                {
                    // Retorna -1 indicando que pilha n�o est� completa e que o jogo n�o terminou
                    return -1;
                }
            }
        }
    }

    // Retorna 1 indicando que o usu�rio venceu o jogo
    return 1;
}



//////////////////////////////////////
////////////LIBERA PUZZLE/////////////
//////////////////////////////////////

void libera_jogo(Pilha **vetor_pilhas, int num_pilhas)
{
    // Repete at� liberar todas as pilhas do vetor_pilhas
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

    // Repete at� passar por todas as pilhas
    for (int x = 0; x<num_pilhas; x++)
    {
        // Aponta auxiliar para sua pilha correspondente
        aux[x] = vetor_pilhas[x]->primeiro;
    }

    // Repete por 4 linhas
    for (int x = 0; x<4; x++)
    {
        int verif = 0;

        // Repete at� chegar na �ltima pilha
        for (int y = 0; y<num_pilhas; y++)
        {
            // Caso pilha atual possua menos bolas do do que 4-x (feito para bolas n�o ficarem sendo sempre printadas a partir do topo do tubo)
            if (vetor_pilhas[y]->num_bolas < 4-x)
            {
                yellow();
                printf("|   |  ");
                reset();
            }

            // Se auxiliar atual n�o for vazio, printa item atual dele
            else if (aux[y]!=NULL)
            {
                // Printa item de auxiliar
                yellow();
                printf("|");
                reset();

                cores_tubo(aux[y]->item); // Fun��o que printa cor correspondente ao n�mero

                yellow();
                printf("|  ");
                reset();
            }

            // Se auxiliar for vazio
            else
            {
                // Printa espa�o em branco
                yellow();
                printf("|   |  ");
                reset();
            }

            if ((x==2) && (y==num_pilhas-1))
            {
                yellow();
                printf("N�mero de jogadas: ");
                reset();
                printf("%i", hist.movimentos);
            }

            // Se j� printou conte�do atual de todas as pilhas, pula para pr�xima linha
            if (y==num_pilhas-1)
            {
                printf("\n");
                verif = 1;
            }
        }

        // Se foi para pr�xima linha
        if (verif==1)
        {
            // Repete at� passar por todas as pilhas
            for (int z = 0; z<num_pilhas; z++)
            {
                // Se auxiliar atual n�o for NULL
                if(aux[z] != NULL)
                {
                    // Feito para atualizar apenas se algum elemento da pilha foi printado anteriormente
                    // (feito para bolas n�o ficarem sendo sempre printadas a partir do topo do tubo)
                    if (vetor_pilhas[z]->num_bolas >= 4-x)
                    {
                        // Auxiliar aponta para pr�ximo da pilha
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

    // Printa numera��o dos tubos
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
    printf("  \e[4;33mEscolha uma das op��es abaixo\n");
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

    printf(" Hist�rico                   ");

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
///////////PRINTA HIST�RICO///////////
//////////////////////////////////////

void print_historico(Historico *vetor_historico, int jogos)
{
    int verif = 0;

    printf("        \e[4;37mHIST�RICO\n");
    reset();

    // Repete at� passar por todas structs em vetor_historico
    for (int x=0; x<jogos; x++)
    {
        yellow();
        printf(" ________________________ \n");
        printf("|                        |\n");
        printf("| N�mero de tubos:   %-2i  |\n", vetor_historico[x].num_tubos); // Printa n�mero de tubos
        printf("| N�mero de jogadas: %-3i |", vetor_historico[x].movimentos); // Printa n�mero de movimentos
        printf("  JOGO %i\n", x+1);
        printf("| Venceu: ");

        // Caso usu�rio tenha vencido esse jogo (vetor_historico[x].venceu = 1)
        if (vetor_historico[x].venceu)
        {
            printf("SIM            |\n");
        }
        // Caso usu�rio tenha perdido esse jogo (vetor_historico[x].venceu = 0)
        else
        {
            printf("N�O            |\n");
        }

        printf("|________________________|\n\n");
        reset();


        verif = 1; // Verificador = 1, indicando que houve pelo menos 1 jogo
    }

    // Caso n�o tenha tido nenhum jogo
    if (verif==0)
    {
        // Mensagem de erro
        red();
        printf("N�o houve nenhum jogo at� agora!\n\n");
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

    printf("                Ball Sort Puzzle � um jogo estrat�gico,\n");
    printf(" onde seu �nico objetivo � deixar todos os tubos com apenas uma cor dentro!\n\n\n");

    printf("                             \e[4;33mCOMO JOGAR:\n\n");
    reset();

    printf(". Escolha um tubo que queira remover uma cor, e a coloque no topo de outro tubo.\n");
    printf(". A regra � que voc� s� pode mover uma cor para cima de outra cor igual.\n");
    printf(". Voc� sempre pode mover uma cor para um tubo vazio.\n");
    printf(". Quanto mais tubos, mais dif�cil o jogo se torna.\n");
    printf(". Cuidado com seus movimentos, voc� pode acabar ficando preso no jogo.\n");
    printf(". N�o se preocupe, caso fique preso, � poss�vel come�ar outro jogo.\n");
    printf(". Para vencer, sempre haver�o dois tubos completamente vazios.\n\n");

    system("pause");
}







