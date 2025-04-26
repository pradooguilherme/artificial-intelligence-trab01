#include "bds.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

node BDS(game *G, game *goal)
{
    node nd = childNode(NULL, 0);
    copyGame(G, nd->state);
    if (endGame(G))
    {
        return nd;
    }
    printGame(G);
    printf("\n");

    node goal_nd = childNode(NULL, 0);
    copyGame(goal, goal_nd->state);

    fila frontier_nd = newFila();
    insert(frontier_nd, nd);
    fila explored_nd = newFila();
    insert(explored_nd, nd);

    fila frontier_goal = newFila();
    insert(frontier_goal, goal_nd);
    fila explored_goal = newFila();
    insert(explored_goal, goal_nd);

    while (frontier_nd->first != NULL && frontier_goal->first != NULL)
    {
        // Armazena último nó em frontier_nd
        node parent = pop(frontier_nd);
        // Variável auxiliar
        game *aux = newGame();
        copyGame(parent->state, aux);
        // Cria nós filhos para cada ação possível
        for (int k = 1; k < 9; k++)
        {
            // Checa se movimento é válido
            if (moveGame(aux, k))
            {
                node child = childNode(parent, k);

                if (isIn(explored_goal, child))
                {
                    insert(explored_nd, child);
                    return getPathFromBDS(child, explored_nd, explored_goal);
                }

                if (!isIn(explored_nd, child))
                {
                    insert(frontier_nd, child);
                    insert(explored_nd, child);
                }
                else
                { // para poupar memória
                    delNode(child);
                }
                // Retorna para estado anterior ao movimento
                moveGame(aux, k);
            }
        }

        parent = pop(frontier_goal);
        // Variável auxiliar
        aux = newGame();
        copyGame(parent->state, aux);
        // Cria nós filhos para cada ação possível
        for (int k = 1; k < 9; k++)
        {
            // Checa se movimento é válido
            if (moveGame(aux, k))
            {
                node child = childNode(parent, k);

                if (isIn(explored_nd, child))
                {
                    insert(explored_goal, child);
                    return getPathFromBDS(child, explored_nd, explored_goal);
                }

                if (!isIn(explored_goal, child))
                {
                    insert(frontier_goal, child);
                    insert(explored_goal, child);
                }
                else
                { // para poupar memória
                    delNode(child);
                }
                moveGame(aux, k);
            }
        }
        // Gerenciamento adequado de memória. Não é necessário, mas eu fiz
        delGame(aux);
    }

    return NULL;
}

node getNode(fila f, node nd)
{
    for (item aux = f->first; aux != NULL; aux = aux->next)
    {
        if (equal(aux->nd->state, nd->state))
            return aux->nd;
    }
    return NULL;
}

node getPathFromBDS(node C, fila nd, fila goal)
{
    node fromGoal = getNode(goal, C);
    node fromNd = getNode(nd, C);

    printf("Caminho do estado comum até o objetivo: \n");

    while(fromGoal != NULL){
        printGame(fromGoal->state);
        printf("\n");
        fromGoal = fromGoal->parent;
    }

    printf("Caminho do estado comum até o estado inicial: \n");

    while(fromNd != NULL){
        printGame(fromNd->state);
        printf("\n");
        fromNd = fromNd->parent;
    }

    return C;
}