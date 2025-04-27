#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

stack newStack()
{
    stack s = malloc(sizeof(Stack));
    assert(s);
    s->top = NULL;
    return s;
}

void push(stack s, node newNode)
{
    stackItem I = malloc(sizeof(struct StackItem));
    assert(I);
    I->nd = newNode;
    I->next = s->top;
    s->top = I;
}

node popStack(stack s)
{
    if (s->top == NULL)
    {
        return NULL;
    }
    stackItem I = s->top;
    node nd = I->nd;
    s->top = I->next;
    free(I);
    return nd;
}

bool isInStack(stack s, node nd)
{
    for (stackItem aux = s->top; aux != NULL; aux = aux->next)
    {
        if (equal(aux->nd->state, nd->state))
        {
            return true;
        }
    }
    return false;
}

bool isEmptyStack(stack s)
{
    return (s->top == NULL);
}

void freeStack(stack s)
{
    while (!isEmptyStack(s))
    {
        popStack(s);
    }
    free(s);
}

node DFS(game *G)
{
    /*
        Depth-First Search (Busca em profundidade).
    */
    node nd = childNode(NULL, 0);
    copyGame(G, nd->state);
    if (endGame(G))
    {
        return nd;
    }
    printGame(G);
    printf("\n");

    // Inicializa fronteira e conjunto de nós já explorados
    stack frontier = newStack();
    push(frontier, nd);
    stack explored = newStack();
    push(explored, nd);

    while (!isEmptyStack(frontier))
    {
        node parent = popStack(frontier);
        game *aux = newGame();
        copyGame(parent->state, aux);

        for (int k = 1; k < 9; k++)
        {
            if (moveGame(aux, k))
            {
                node child = childNode(parent, k);
                if (!isInStack(explored, child))
                {
                    if (endGame(child->state))
                    {
                        return child;
                    }
                    push(frontier, child);
                    push(explored, child);
                }
                else
                {
                    delNode(child);
                }
                moveGame(aux, k);
            }
        }
        delGame(aux);
    }

    return NULL;
}


node DLS(game *G, int L)
{
    /*
        Depth-Limited Search (Busca em profundidade limitada).
    */
    node nd = childNode(NULL, 0);
    copyGame(G, nd->state);
    if (endGame(G))
    {
        return nd;
    }
    printGame(G);
    printf("\n");

    // Inicializa fronteira e conjunto de nós já explorados
    stack frontier = newStack();
    push(frontier, nd);
    stack explored = newStack();
    push(explored, nd);

    while (!isEmptyStack(frontier))
    {
        node parent = popStack(frontier);
        game *aux = newGame();
        copyGame(parent->state, aux);

        if (parent->pathCost <= L)
        {
            for (int k = 1; k < 9; k++)
            {
                if (moveGame(aux, k))
                {
                    node child = childNode(parent, k);
                    if (!isInStack(explored, child))
                    {
                        if (endGame(child->state))
                        {
                            return child;
                        }
                        push(frontier, child);
                        push(explored, child);
                    }
                    else
                    {
                        delNode(child);
                    }
                    moveGame(aux, k);
                }
            }
        }
        delGame(aux);
    }

    return NULL;
}
