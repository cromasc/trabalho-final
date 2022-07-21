#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct aluno
{
    char nome[100];
    int n_matricula;
    struct notas
    {
        int cra;
        struct materias
        {
            char nome[50];
            int nota;
            int frequencia;
        } materias;
    } notas;
    
} aluno;

int menu() {
    int r;
    printf("Bem vindo ao servidor da UFA.\nPara visualizar a lista de alunos, tecle 1.\nCadastrar um novo aluno, tecle 2.\nPara sair do programa, tecle 3.\n\nResposta ----> ");
    scanf("%d", &r);
    return r;
}

void main() {
    int n = 0, r1;
    aluno vet_aluno[n];

    r1 = menu();

    while (r1 != 3) {
        if (r1 == 1) {
            if (n == 0) {
                printf("Nenhum usuário cadastrado ainda...");
                r1 = menu();
            }else {
                for (int i = 0; i < n; i++) {
                    puts(vet_aluno[i].nome);
                }
            }
        } else if (r1 == 2) {

        }
    }
    system(exit);
}