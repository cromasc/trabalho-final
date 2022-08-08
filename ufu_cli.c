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
    int r = 4;
    printf("Bem vindo ao servidor da UFU.\nPara visualizar a lista de alunos, tecle 1.\nCadastrar um novo aluno, tecle 2.\nPara sair do programa, tecle 0.\n\nResposta ----> ");
    scanf("%d", &r);
    fflush(stdin); setbuf(stdin, NULL);
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

int cadastro(aluno vetor[], int *index) {
    int i = 0;
    printf("Digite o nome do aluno: ");  fgets(vetor[*index].nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);

    while(vetor[0].nome_completo[i] != '\0') {
        if (vetor[0].nome_completo[i] == '\n') {
            vetor[0].nome_completo[i] = '\0';
            break;
        }
        i++;
    }
    // vetor[*index].nome_completo[strcspn(vetor[*index].nome_completo, "\n")] = 0;

    printf("Digite o número de matrícula: "); fgets(vetor[*index].n_matricula, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
    *index++;
    system("clear");
    return menu();
}

int main() {
    setlocale(LC_ALL,"Portuguese");
    // FILE *arq;

    // arq = fopen("users.txt", "a");

    // if (arq == NULL) {
    //     return 1;
    // }

    int n = 0, choice;
    aluno vet_aluno[n];

    choice = menu();

    while (choice != 0) {
        fflush(stdin); setbuf(stdin, NULL);

        switch (choice) {
        case 0:
            break;
        
        case 1:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            if (n == 0) {
                choice = nenhum_usuario();
            } else {
                choice = print_users(vet_aluno, n);
            }
            break;

        case 2:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            choice = cadastro(vet_aluno, &n);
            break;
        
        default:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);
                
            printf("Opção não válida.\n\nDigite ENTER para voltar ao menu.");
            if (getchar() == '\n') {
                system("clear");
                choice = menu();
            }
            break;
        }
    }
    // fclose(arq);
    return 1;
}