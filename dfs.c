#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

node popForStack(fila f)
{
    /*
        Retorna o último nó da fila, removendo-o da mesma.
    */
    item aux = f->first;
    item newLast = NULL;

    while (aux != f->last)
    {
        newLast = aux;
        aux = aux->next;
    }

    item I = f->last;
    node nd = I->nd;
    f->last = newLast;

    if (f->last == NULL)
    {
        f->first = NULL;
    }

    free(I);
    return nd;
}

node DFS(game *G)
{
    /*
        Depth-First Search (Busca em profundidade).
    */
    // Inicializa primeiro nó com a configuração fornecida do jogo.
    node nd = childNode(NULL, 0);
    copyGame(G, nd->state);
    if (endGame(G))
    {
        return nd;
    }
    printGame(G);
    printf("\n");

    // Inicializa fronteira e conjunto de nós já explorados
    fila frontier = newFila();
    insert(frontier, nd);
    fila explored = newFila();
    insert(explored, nd);

    while (frontier->first != NULL)
    {
        // Armazena último nó em frontier
        node parent = popForStack(frontier);
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
                if (!isIn(explored, child))
                {
                    // Checa se nó filho resolve o problema
                    if (endGame(child->state))
                    {
                        return child;
                    }
                    // Caso contrário, insere nó filho em frontier
                    insert(frontier, child);
                    // Insere em explored
                    insert(explored, child);
                    // Impressão na tela
                    // sleep(1);
                    // printGame(child->state); printf("\n");
                }
                else
                { // para poupar memória
                    delNode(child);
                }
                // Retorna para estado anterior ao movimento
                moveGame(aux, k);
            }
        }
        // Gerenciamento adequado de memória. Não é necessário, mas eu fiz
        delGame(aux);
    }

    return NULL;
}

node DLS(game *G, int L)
{
    /*
        Depth-Limited Search (Busca em profundidade Limitiada).
    */
    // Inicializa primeiro nó com a configuração fornecida do jogo.
    node nd = childNode(NULL, 0);
    copyGame(G, nd->state);
    if (endGame(G))
    {
        return nd;
    }
    printGame(G);
    printf("\n");

    // Inicializa fronteira e conjunto de nós já explorados
    fila frontier = newFila();
    insert(frontier, nd);
    fila explored = newFila();
    insert(explored, nd);

    while (frontier->first != NULL)
    {
        // Armazena último nó em frontier
        node parent = popForStack(frontier);
        // Variável auxiliar
        game *aux = newGame();
        copyGame(parent->state, aux);
        // Cria nós filhos para cada ação possível

        if (parent->pathCost <= L)
        {
            for (int k = 1; k < 9; k++)
            {
                // Checa se movimento é válido
                if (moveGame(aux, k))
                {
                    node child = childNode(parent, k);
                    if (!isIn(explored, child))
                    {
                        // Checa se nó filho resolve o problema
                        if (endGame(child->state))
                        {
                            return child;
                        }
                        // Caso contrário, insere nó filho em frontier
                        insert(frontier, child);
                        // Insere em explored
                        insert(explored, child);
                        // Impressão na tela
                        // sleep(1);
                        // printGame(child->state); printf("\n");
                    }
                    else
                    { // para poupar memória
                        delNode(child);
                    }
                    // Retorna para estado anterior ao movimento
                    moveGame(aux, k);
                }
            }
        }
        // Gerenciamento adequado de memória. Não é necessário, mas eu fiz
        delGame(aux);
    }

    return NULL;
}