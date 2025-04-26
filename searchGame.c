#include "game.h"
#include "tree.h"
#include "bfstree.h"
#include "greedy.h"
#include "bds.h"
#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

int main()
{
    struct timeval start, end;
    long seconds, micros;

    game *goal = newGame();
    goal->grid[0][0] = 0;
    goal->grid[0][1] = 1;
    goal->grid[0][2] = 2;
    goal->grid[1][0] = 3;
    goal->grid[1][1] = 4;
    goal->grid[1][2] = 5;
    goal->grid[2][0] = 6;
    goal->grid[2][1] = 7;
    goal->grid[2][2] = 8;

    game *G = newGame();
    G->grid[0][0] = 1;
    G->grid[0][1] = 2;
    G->grid[0][2] = 5;
    G->grid[1][0] = 3;
    G->grid[1][1] = 0;
    G->grid[1][2] = 4;
    G->grid[2][0] = 6;
    G->grid[2][1] = 7;
    G->grid[2][2] = 8;

    int ans;

    printf(
        "Escolha uma busca para resolver o problema de 8-puzzle.\n"
        "[1] Depth-First Search\n"
        "[2] Depth-Limited Search\n"
        "[3] Breadth-First Search\n"
        "[4] Bidirectional Search\n");

    scanf(" %d", &ans);

    node nd = NULL;

    switch (ans)
    {
    case 1:
        gettimeofday(&start, NULL);
        nd = DFS(G);
        gettimeofday(&end, NULL);
        break;
    case 2:
        int lim;
        printf("Ok. Insira um limite: ");
        scanf(" %d", &lim);
        printf("\n");
        gettimeofday(&start, NULL);
        nd = DLS(G, lim);
        gettimeofday(&end, NULL);
        break;
    case 3:
        gettimeofday(&start, NULL);
        nd = BFS(G);
        gettimeofday(&end, NULL);
        break;
    case 4:
        gettimeofday(&start, NULL);
        BDS(G, goal);
        gettimeofday(&end, NULL);
        break;
    }

    int pathSize = 0;

    while (nd != NULL)
    {
        printGame(nd->state);
        printf("\n");
        pathSize++;
        nd = nd->parent;
    }

    seconds = end.tv_sec - start.tv_sec;
    micros = end.tv_usec - start.tv_usec;

    if (micros < 0)
    { // Ajusta se deu negativo
        seconds--;
        micros += 1000000;
    }

    printf("Tempo de execução: %ld segundos e %ld microssegundos\n", seconds, micros);
    printf("Número de passos: %d\n", pathSize);

    return 0;
}