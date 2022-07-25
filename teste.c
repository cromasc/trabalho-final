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
            char nome[7][50];
            int nota[7];
            int frequencia[7];
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
            system("clear");
            fflush(stdin);
            setbuf(stdin,0);
            if (n == 0) {
                printf("Nenhum usuário cadastrado ainda...\n\nDigite ENTER para voltar ao menu: ");
                if (getchar() == " ") {
                        r1 = menu();
                    }
            }else {
                for (int i = 0; i < n; i++) {
                    printf("Nome: %s \nNúmero de matrícula: %d", vet_aluno[i].nome, vet_aluno[i].n_matricula);
                    printf("Digite ENTER para sair: ");
                    if (getchar() == "") {
                        r1 = menu();
                    }
                }
            }
        } else if (r1 == 2) {
            break;
        }
    }
    system(exit);
}