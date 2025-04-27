#include "bfstree.h"

void BDS(game *G, game *goal, int *pathSize);
node getNode(fila f, node nd);
void getPathFromBDS(node C, fila nd, fila goal, int *pathSize);