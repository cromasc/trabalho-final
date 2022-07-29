#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 256

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

int nenhum_usuario() {
    printf("Nenhum usuário cadastrado ainda...\n\nDigite ENTER para voltar ao menu.");
    if (getchar() == '\n') {
        system("clear");
        return menu();
    }
}

int print_users(aluno vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nome: %s \nNúmero de matrícula: %s", vetor[i].nome_completo, vetor[i].n_matricula);
        }
    printf("Digite ENTER para sair.");
    if (getchar() == '\n') {
        system("clear");
        return menu();
    }
}

int cadastro(aluno vetor[], int index) {
    printf("Digite o nome do aluno: ");  fgets(vetor[index].nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);

    vetor[index].nome_completo[strcspn(vetor[index].nome_completo, "\n")] = 0;

    printf("Digite o número de matrícula: "); fgets(vetor[index].n_matricula, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
    system("clear");
    return menu();
}

void main() {
    FILE *arq;

    arq = fopen("users.txt", "a");

    if (arq == NULL) {
        system("exit");
    }

    int n = 0, choice;
    aluno vet_aluno[n];

    choice = menu();

    while (choice != 3) {
        fflush(stdin); setbuf(stdin, NULL);

        if (choice == 1) {
            system("clear");

            if (n == 0) {
                choice = nenhum_usuario();
            } else {
                choice = print_users(vet_aluno, n);
            }

        } else if (choice == 2) {
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            choice = cadastro(vet_aluno, n);
            n += 1;

        } else {
            system("clear"); fflush(stdin); setbuf(stdin, NULL);
            
            printf("Opção não válida.\n\nDigite ENTER para voltar ao menu.");
            if (getchar() == '\n') {
                system("clear");
                choice = menu();
            }
        }
    }
    fclose(arq);
    system("exit");
}