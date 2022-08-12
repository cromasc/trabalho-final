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

int menu()
{
    int r = 4;
    printf("Bem vindo ao servidor da UFU.\nPara visualizar a lista de alunos, tecle 1.\nCadastrar um novo aluno, tecle 2.\nPara sair do programa, tecle 0.\n\nResposta ----> ");
    scanf("%d", &r); fflush(stdin); setbuf(stdin, NULL);
    
    return r;
}

int nenhum_usuario()
{
    printf("Nenhum usuário cadastrado ainda...\n\nDigite ENTER para voltar ao menu.");
    if (getchar() == '\n')
    {
        system("clear");
        return menu();
    }
}

int imprime_usuarios(FILE *arq)
{
    aluno aluno; int EOF_ctrl;

    strcpy(aluno.n_matricula, "default");
    strcpy(aluno.nome_completo, "default");

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo");
        system("exit");
    } else {
        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) {
                printf("Erro na leitura do arquivo");
            } else {
                if (EOF_ctrl != 0) {
                    printf("Nome: %s\n", aluno.nome_completo);
                    printf("Número de matrícula: %s\n", aluno.n_matricula);
                }
            }
        }
        printf("Digite ENTER para sair.");
        if (getchar() == '\n')
        {
            system("clear");
            return menu();
        }
    }
}

int cadastro()
{
    FILE *arq = fopen("users.txt", "a"); aluno aluno;

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo");
        system("exit");
    } else {
        printf("Digite o nome do aluno: "); 
        fgets(aluno.nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        aluno.nome_completo[strcspn(aluno.nome_completo, "\n")] = 0;

        printf("Digite o número de matrícula: "); 
        fgets(aluno.n_matricula, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);

        fwrite(&aluno, sizeof(struct aluno), 1, arq);
    } fclose(arq);

    system("clear");
    return menu();
    
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int choice; aluno aluno;

    choice = menu();
    while (choice != 0)
    {
        fflush(stdin);setbuf(stdin, NULL);
        
        switch (choice)
        {
        case 0:
            break;

        case 1:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            FILE *arq = fopen("users.txt", "r");
            if (arq == NULL) {
                choice = nenhum_usuario();
            } else {
                choice = imprime_usuarios(arq);
                fclose(arq);
            }
            break;
            
        case 2:
            system("clear"); fflush(stdin);setbuf(stdin, NULL);
            
            choice = cadastro();
            break;

        default:
            system("clear"); fflush(stdin);setbuf(stdin, NULL);
            
            printf("Opção não válida.\n\nDigite ENTER para voltar ao menu.");
            if (getchar() == '\n')
            {
                system("clear");
                choice = menu();
            }
            break;
        }
    }
    return 1;
}