#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

typedef struct{
    char **tablero;
    int filas;
    int columnas;
    int jugadorX;
    int jugadorY;
    int cajasRestantes;
} Mapa;

extern int mover_jugador(Mapa *m, int dx, int dy);

void generaCajas(int posCajas[4][2], int tam);
int hayCaja(int i, int j, int posCajas[4][2]);
void generaObjetivos(int posObjetivos[4][2], int tam);
int hayObjetivos(int i, int j, int posObjetivos[4][2]);
char **generaTablero(int n, int *jugadorX, int *jugadorY, int *cajasRestantes);
void imprimeTablero(char **tablero, int tam);
void liberarTablero(char **tablero, int n);

int main()
{
    srand(time(NULL));
    int tam = 15;
    Mapa mapa;
    mapa.filas = tam;
    mapa.columnas = tam;
    mapa.tablero = generaTablero(tam, &mapa.jugadorX, &mapa.jugadorY, &mapa.cajasRestantes);

    char tecla;
    int dx, dy;
    do{
        system("cls");
        printf("\nUsa WASD para moverte, y Q para salir\n\n");
        imprimeTablero(mapa.tablero, tam);

        tecla = _getch();
        dx = 0;
        dy = 0;
        switch (tecla){
            case 'w': dy = -1; break;
            case 's': dy = 1; break;
            case 'a': dx = -1; break;
            case 'd': dx = 1; break;
        }

        if (dx != 0 || dy != 0){
            mover_jugador(&mapa, dx, dy);
        }
    }while (tecla != 'q' && tecla != 'Q');

    liberarTablero(mapa.tablero, tam);
    return 0;
}

char **generaTablero(int n, int *jugadorX, int *jugadorY, int *cajasRestantes)
{
    int posCajas[4][2];
    int posObjetivos[4][2];
    generaCajas(posCajas, n);
    generaObjetivos(posObjetivos, n);
    *cajasRestantes = 3;

    char **tablero = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        tablero[i] = (char *)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++)
        {
            if (i == 1 && j == 1)
            {
                tablero[i][j] = 'P';
                *jugadorX = j;
                *jugadorY = i;
            } else if (i == 0 || i == n - 1 || j == 0 || j == n-1){
                tablero[i][j] = '#';
            } else if (hayCaja(i, j, posCajas)){
                tablero[i][j] = 'C';
            } else if (hayObjetivos(i, j, posObjetivos)){
                tablero[i][j] = 'X';
            } else{
                tablero[i][j] = ' ';
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

void generaCajas(int posCajas[4][2], int tam)
{
    for (int i = 0; i < 3; i++)
    {
        int x, y;
        do
        {
            y = 2 + rand() % (tam - 4);
            x = 2 + rand() % (tam - 4);
        }while (hayCaja(y, x, posCajas));
        posCajas[i][0] = y;
        posCajas[i][1] = x;
    }
}

void generaObjetivos(int posObjetivos[4][2], int tam)
{
    for (int i = 0; i < 3; i++)
    {
        int x, y;
        do
        {
            y = 1 + rand() % (tam - 2);
            x = 1 + rand() % (tam - 2);
        }while (hayObjetivos(y, x, posObjetivos));
        posObjetivos[i][0] = y;
        posObjetivos[i][1] = x;
    }
}

int hayCaja(int i, int j, int posCajas[4][2])
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

int hayObjetivos(int i, int j, int posObjetivos[4][2])
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