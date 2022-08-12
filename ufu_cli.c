#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 256
#define DEFAULT 8

typedef struct aluno
{
    char nome_completo[MAX_LENGTH];
    char n_matricula[MAX_LENGTH];
    struct notas
    {
        float cra;
        int numero_de_materias;
        struct materias
        {
            char nome[DEFAULT][MAX_LENGTH];
            float nota_final[DEFAULT];
            int frequencia[DEFAULT];
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
    } 
    else 
    {
        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) 
            {
                printf("Erro na leitura do arquivo");
            } 
            else 
            {
                if (EOF_ctrl != 0) 
                {
                    printf("--------------------------------------------------------------\n");
                    printf("%s -> ", aluno.nome_completo);
                    printf("%s\n\n", aluno.n_matricula);

                    for (int i = 0; i < aluno.notas.numero_de_materias; i++)
                    {
                        printf("%s: ", aluno.notas.materias.nome[i]);
                        printf("nota final: %.1f, ", aluno.notas.materias.nota_final[i]);
                        printf("Frequência de %d%%\n", aluno.notas.materias.frequencia[i]);

                    }
                    printf("\nCRA = %.2f\n", aluno.notas.cra);
                }
            }
        }
        printf("--------------------------------------------------------------\n");
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
    aluno.notas.cra = 0;

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo");
        system("exit");
    } 
    else 
    {
        printf("Digite o nome do aluno: "); 
        fgets(aluno.nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        aluno.nome_completo[strcspn(aluno.nome_completo, "\n")] = 0;

        printf("Digite o número de matrícula: "); 
        fgets(aluno.n_matricula, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        aluno.n_matricula[strcspn(aluno.n_matricula, "\n")] = 0;

        printf("Digite o número de matérias que deseja guardar: ");
        scanf("%d", &aluno.notas.numero_de_materias); fflush(stdin); setbuf(stdin, NULL);

        for (int i = 0; i < aluno.notas.numero_de_materias; i++)
        {
            if (i == 0) 
            {
                printf("\nDigite o nome da primeira matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s \n(exemplo: 65): ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra = (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 1) 
            {
                printf("\nDigite o nome da segunda matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 2) 
            {
                printf("\nDigite o nome da terceira matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 3) 
            {
                printf("\nDigite o nome da quarta matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 4) 
            {
                printf("\nDigite o nome da quinta matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 5) 
            {
                printf("\nDigite o nome da sexta matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 6) 
            {
                printf("\nDigite o nome da sétima matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else if (i == 7) 
            {
                printf("\nDigite o nome da oitava matéria: ");
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            } 
            else 
            {
                printf("\nDigite o nome da matéria %d", i+1);
                fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
                aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

                printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);

                printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
                scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);

                aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
            }
        }

        fwrite(&aluno, sizeof(struct aluno), 1, arq);
        fclose(arq);
    }

    system("clear");
    return menu();
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int escolha; aluno aluno;

    escolha = menu();
    while (escolha != 0)
    {
        fflush(stdin);setbuf(stdin, NULL);
        
        switch (escolha)
        {
        case 0:
            break;

        case 1:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            FILE *arq = fopen("users.txt", "r");
            if (arq == NULL) 
            {
                escolha = nenhum_usuario();
            } 
            else 
            {
                escolha = imprime_usuarios(arq);
                fclose(arq);
            }
            break;
            
        case 2:
            system("clear"); fflush(stdin);setbuf(stdin, NULL);
            
            escolha = cadastro();
            break;

        default:
            system("clear"); fflush(stdin);setbuf(stdin, NULL);
            
            printf("Opção não válida.\n\nDigite ENTER para voltar ao menu.");
            if (getchar() == '\n')
            {
                system("clear");
                escolha = menu();
            }
            break;
        }
    }
    return 0;
}