#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void generaCajas(int posCajas[3][3],int tam);
int hayCaja(int i, int j, int posCajas[3][3]);
int main() {
    int n = 10;
    int posCajas[3][3];
    srand(time(NULL)); 
    generaCajas(posCajas,n);

    for(int i =0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==0 || i==n-1 || j==0 || j==n-1){
                printf("# ");
            }else{
                if(hayCaja(i,j,posCajas)){
                    printf("C ");
                }else{
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}

void generaCajas(int posCajas[3][3],int tam){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            posCajas[i][j]=rand()%(tam-1);
        }
    }
}

int hayCaja(int i, int j, int posCajas[3][3]){
    for(int k = 0; k < 3; k++){
        if(i == posCajas[k][0] && j == posCajas[k][1]){
            return 1;
        }
    }
    return 0;
}