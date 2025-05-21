#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void generaCajas(int posCajas[3][3], int tam);
int hayCaja(int i, int j, int posCajas[3][3]);
void generaObjetivos(int posObjetivos[3][3], int tam);
int hayObjetivos(int i, int j, int posObjetivos[3][3]);
char **generaTablero(int n);
void imprimeTablero(char **Tablero, int tam);

int main()
{
    srand(time(NULL));
    int tam = 15;
    char **tablero = generaTablero(tam);
    imprimeTablero(tablero, tam);
    return 0;
}

char **generaTablero(int n)
{
    int posCajas[4][3];
    int posObjetivos[4][3];
    generaCajas(posCajas, n);
    generaObjetivos(posObjetivos, n);

    char **tablero = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        tablero[i] = (char *)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++)
        {
            if (i == 1 && j == 1)
            {
                tablero[i][j] = 'P';
            }
            else
            {
                if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
                {
                    tablero[i][j] = '#';
                }
                else
                {
                    if (hayCaja(i, j, posCajas))
                    {
                        tablero[i][j] = 'C';
                    }
                    else
                    {
                        if (hayObjetivos(i, j, posObjetivos))
                        {
                            tablero[i][j] = 'X';
                        }
                        else
                        {
                            tablero[i][j] = ' ';
                        }
                    }
                }
            }
        }
    }
    return tablero;
}

void imprimeTablero(char **tablero, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

void liberarTablero(char **tablero, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(tablero[i]);
    }
    free(tablero);
}

void generaCajas(int posCajas[4][3], int tam)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            posCajas[i][j] = 2 + rand() % (tam - 1);
        }
    }
}

void generaObjetivos(int posObjetivos[4][3], int tam)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            posObjetivos[i][j] = 2 + rand() % (tam - 1);
        }
    }
}

int hayCaja(int i, int j, int posCajas[4][3])
{
    for (int k = 0; k < 3; k++)
    {
        if (i == posCajas[k][0] && j == posCajas[k][1])
        {
            return 1;
        }
    }
    return 0;
}

int hayObjetivos(int i, int j, int posObjetivos[4][3])
{
    for (int k = 0; k < 3; k++)
    {
        if (i == posObjetivos[k][0] && j == posObjetivos[k][1])
        {
            return 1;
        }
    }
    return 0;
}