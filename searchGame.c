#include "game.h"
#include "tree.h"
#include "bfstree.h"
#include "greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    
    game* G = newGame();
    G->grid[0][0] = 1;
    G->grid[0][1] = 2;
    G->grid[0][2] = 5;
    G->grid[1][0] = 0;
    G->grid[1][1] = 4;
    G->grid[1][2] = 8;
    G->grid[2][0] = 3;
    G->grid[2][1] = 6;
    G->grid[2][2] = 7;

    node nd = BFS(G);
    
    node aux = nd;
    while (aux!=NULL){
        printGame(aux->state);
        printf("\n");
        aux = aux->parent;
    }
    
    return 0;
}