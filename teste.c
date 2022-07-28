#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 100

typedef struct aluno
{
    char nome_completo[MAX_LENGTH];
    char n_matricula[MAX_LENGTH];
    struct notas
    {
        float cra;
        struct materias
        {
            char nome[7][MAX_LENGTH];
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
        fflush(stdin); setbuf(stdin, 0);
        if (r1 == 1) {
            system("clear");

            if (n == 0) {
                printf("Nenhum usuário cadastrado ainda...\n\nDigite ENTER para voltar ao menu.");
                if (getchar() == '\n') {
                    system("clear");
                    r1 = menu();
                }
            } else {
                for (int i = 0; i < n; i++) {
                    printf("Nome: %s \nNúmero de matrícula: %s", vet_aluno[i].nome_completo, vet_aluno[i].n_matricula);
                    }
                printf("Digite ENTER para sair.");
                if (getchar() == '\n') {
                    system("clear");
                    r1 = menu();
                }
            }
        } else if (r1 == 2) {
            system("clear");
            fflush(stdin); setbuf(stdin,0);

            printf("Digite o nome do aluno: ");  fgets(vet_aluno[n].nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin,0);
            vet_aluno[n].nome_completo[strcspn(vet_aluno[n].nome_completo, "\n")] = 0;
            
            printf("Digite o número de matrícula: "); fgets(vet_aluno[n].n_matricula, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, 0);
            n += 1;
            system("clear");
            r1 = menu();
        } else {
            system("clear");
            fflush(stdin); setbuf(stdin,0);
            
            printf("Opção não válida.\n\nDigite ENTER para voltar ao menu.");
            if (getchar() == '\n') {
                system("clear");
                r1 = menu();
            }
        }
    }
    system("exit");
}