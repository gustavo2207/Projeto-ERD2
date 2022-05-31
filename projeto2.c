#include <stdio.h>
#include <stdlib.h>

//-------------------------
#define MAXN 5
#define INFINITO 999999999
//-------------------------

#define min(x, y) (((x) < (y)) ? (x) : (y))

int main(){
    int n, m, q;
    int mapa[MAXN][MAXN];
    int distancia[MAXN][MAXN];

    scanf("%d %d %d", &n, &m, &q);

    // inicializaremos a matriz para infinito em todas as casas
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            mapa[i][j] = INFINITO;

    for(int i = 1;i <= m;i++){

        int x, y, tempo;
        scanf("%d %d %d", &x, &y, &tempo);

        // colocamos como recebendo esse valor mínimo para o caso
        // dois voos entre as mesmas cidades
        mapa[x][y] = min(mapa[x][y], tempo);
        mapa[y][x] = min(mapa[y][x], tempo);
    }

    // inicializamos as distâncias
    for(int i = 1;i <= n;i++)
    for(int j = 1;j <= n;j++)
        distancia[i][j] = mapa[i][j];

    // Algoritmo de Floyd-Warshall
    for(int k = 1;k <= n;k++)
    for(int i = 1;i <= n;i++)
    for(int j = 1;j <= n;j++)
        distancia[i][j] = min(distancia[i][j], distancia[i][k] + distancia[k][j]);

    for(int i = 1;i <= q;i++){
        int S, E;
        scanf("%d %d", &S, &E); // lemos a pergunta
        printf("%d\n", distancia[S][E]); // imprimimos a resposta
    }

    return 0;
}
