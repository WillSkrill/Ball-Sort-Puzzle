#include "pilha.h"


//////////////////////////////////////
/////////////DEFINE CORES/////////////
//////////////////////////////////////

void red()
{
  printf("\033[1;31m");
}

void green()
{
  printf("\033[0;32m");
}

void yellow()
{
  printf("\033[1;33m");
}

void reset()
{
  printf("\033[0m");
}

void red2()
{
  printf("\e[1;91m");
}

void cores_tubo(int num)
{
    switch (num)
    {
    case 1:
        printf("\e[41m   ");
        reset();
        break;
    case 2:
        printf("\e[44m   ");
        reset();
        break;
    case 3:
        printf("\e[42m   ");
        reset();
        break;
    case 4:
        printf("\e[43m   ");
        reset();
        break;
    case 5:
        printf("\e[0;106m   ");
        reset();
        break;
    case 6:
        printf("\e[0;100m   ");
        reset();
        break;
    case 7:
        printf("\e[0;107m   ");
        reset();
        break;
    case 8:
        printf("\e[0;104m   ");
        reset();
        break;
    case 9:
        printf("\e[0;101m   ");
        reset();
        break;
    case 10:
        printf("\e[0;105m   ");
        reset();
        break;
    }
}



//////////////////////////////////////
////////////FILTRA INTEIRO////////////
//////////////////////////////////////

int filtraInteiro()
{
    char triagem[100];
    double num_double = 0;
    int inteiro = 0;

    fgets(triagem, sizeof triagem, stdin);

    num_double = strtod(triagem, NULL);

    if ((num_double > 2147483647))
    {
        return -1;
    }

    inteiro = atoi(triagem);
    return inteiro;
}
