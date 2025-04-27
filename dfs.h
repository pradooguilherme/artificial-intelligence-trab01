#include "tree.h"

struct StackItem {
    node nd;
    struct StackItem* next;
};

typedef struct StackItem* stackItem;

typedef struct {
    stackItem top;
} Stack;

typedef Stack* stack;

stack newStack();
void push(stack s, node newNode);
node popStack(stack s);
bool isInStack(stack s, node nd);
bool isEmptyStack(stack s);
void freeStack(stack s);

node DFS(game *G);
node DLS(game *G, int L);