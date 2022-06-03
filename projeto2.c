/*
   {
    // If there's no path between
    // node u and v, simply return
    // an empty array
    if (Next[u][v] == -1)
        return {};

    // Storing the path in a vector
    vector<int> path = { u };
    while (u != v) {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}
 */

#include <stdio.h>
#include <stdlib.h>

#define nV 4

#define INF 9999999

void printMatrix(int matrix[][nV]);
void floydWarshall(int graph[][nV], int path[nV][nV])
{
   int matrix[nV][nV], i, j, k;

   for (i = 0; i < nV; i++)
      for (j = 0; j < nV; j++)
         matrix[i][j] = graph[i][j];

   for (k = 0; k < nV; k++)
   {
      for (i = 0; i < nV; i++)
      {
         for (j = 0; j < nV; j++)
         {

            if (matrix[i][k] + matrix[k][j] < matrix[i][j])
            {
               matrix[i][j] = matrix[i][k] + matrix[k][j];
               path[i][j] = path[k][j] + 1;
            }
         }
      }
   }
   system("clear");
   printf("\t\t Matriz de custos para cada rota\n");
   printMatrix(matrix);
   printf("\n");
   printf("\t\t Matriz de antecessores para cada menor caminho\n");
   printMatrix(path);
}

void printMatrix(int matrix[][nV])
{
   for (int i = 0; i < nV; i++)
   {
      for (int j = 0; j < nV; j++)
      {
         if (matrix[i][j] == INF)
            printf("%4s", "INF");
         else
            printf("%4d", matrix[i][j]);
      }
      printf("\n");
   }
}

int createGraph(int matrix[nV][nV])
{
   int origem, destino, custo;
   int path[nV][nV];

   printf("Entre com as Arestas:\n");
   do
   {
      do
      {
         printf("Origem da aresta (entre 1 e %d ou '0' para sair): ", nV);
         scanf("%d", &origem);
      } while (origem < 0 || origem > nV);

      if (origem)
      {
         do
         {
            printf("Destino da aresta (entre 1 e %d, menos %d): ", nV, origem);
            scanf("%d", &destino);
         } while (destino < 1 || destino > nV || destino == origem);

         do
         {
            printf("Custo (positivo) da aresta do vertice %d para o vertice %d: ",
                   origem, destino);
            scanf("%d", &custo);
         } while (custo < 0);
         if (origem != 0 && destino != 0)
         {
            matrix[origem - 1][destino - 1] = custo;
         }
      }

   } while (origem);

   for (int i = 0; i < nV; i++)
   {
      for (int j = 0; j < nV; j++)
      {
         if (i != j)
         {
            path[i][j] = i;
         }
         else
         {
            path[i][j] = -1;
         }
      }
   }

   floydWarshall(matrix, path);
}

int initializerGraph(int matrix[nV][nV])
{

   for (int i = 0; i < nV; i++)
   {
      for (int j = 0; j < nV; j++)
      {
         if (i == j)
         {
            matrix[i][j] = 0;
         }
         else
         {
            matrix[i][j] = INF;
         }
      }
   }

   createGraph(matrix);
}

int main()
{
   int graph[nV][nV];
   initializerGraph(graph);
   // printf("\n");
   // floydWarshall(graph);
}
