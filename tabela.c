#include <stdio.h>

typedef struct {
    double tempo;
    int passos;
} Execucao;

int main() {
    Execucao experimentos[10][10];

    // Exemplo: preenchendo alguns dados fictícios
    for (int exp = 0; exp < 10; exp++) {
        for (int exec = 0; exec < 5; exec++) {
            experimentos[exp][exec].tempo = 0.1 * (exp + 1) + 0.01 * exec;  // só exemplo
            experimentos[exp][exec].passos = 20 + exp + exec;
        }
    }

    // Gerar arquivo CSV
    FILE *fp = fopen("resultados.csv", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(fp, "Experimento,Execucao,Tempo,Passos\n");
    for (int exp = 0; exp < 10; exp++) {
        for (int exec = 0; exec < 5; exec++) {
            fprintf(fp, "%d,%d,%.6f,%d\n", exp+1, exec+1, experimentos[exp][exec].tempo, experimentos[exp][exec].passos);
        }
    }

    fclose(fp);
    printf("Arquivo resultados.csv criado com sucesso!\n");

    return 0;
}
