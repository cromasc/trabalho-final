// João Marcos de Oliveira Calixto - 12111EEL010

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define DEFAULT 8
#define MAX_LENGTH 256
#define flush while (getchar() != '\n');

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
    int r = 100;
    printf("Bem vindo ao servidor da UFU. Tecle uma das seguintes opções para prosseguir:\n");
    printf("[1] - Visualizar a lista de alunos.\n");
    printf("[2] - Cadastrar um novo aluno.\n");
    printf("[3] - Buscar algum aluno específico.\n");
    printf("[4] - Adicionar matéria para algum aluno.\n");
    printf("[5] - Mostrar pessoas cujo CRA seja maior que 80.\n");
    printf("[0] - Sair do programa.\n");
    printf("\nResposta ----> ");
    scanf("%d", &r); fflush(stdin); setbuf(stdin, NULL);
    
    return r;
}

int nenhum_usuario()
{
    printf("Nenhum usuário cadastrado ainda...\n\nDigite ENTER para voltar ao menu. ");
    if (getchar() == '\n')
    {
        system("clear");
        return menu();
    }
}

int imprime_usuarios(FILE *arq)
{
    aluno aluno; int EOF_ctrl;

    if (arq == NULL) 
    {
        printf("Erro de abertura do arquivo na linha 64.\n");
        exit(-1);
    } 
    else 
    {
        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) 
            {
                printf("Erro na leitura do arquivo na linha 74.\n");
            } 
            else if (EOF_ctrl != 0) 
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
        printf("--------------------------------------------------------------\n");
        printf("Tecle ENTER para sair. ");
        if (getchar() == '\n')
        {
            system("clear");
            return menu();
        }
    }
}

aluno adiciona_materias(aluno aluno, int inicio, int final)
{
    for (int i = inicio; i < final; i++)
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
        } 
        else if (i == 1) 
        {
            printf("\nDigite o nome da segunda matéria: ");
        } 
        else if (i == 2) 
        {
            printf("\nDigite o nome da terceira matéria: ");
        } 
        else if (i == 3) 
        {
            printf("\nDigite o nome da quarta matéria: ");
        } 
        else if (i == 4) 
        {
            printf("\nDigite o nome da quinta matéria: ");
        } 
        else if (i == 5) 
        {
            printf("\nDigite o nome da sexta matéria: ");
        } 
        else if (i == 6) 
        {
            printf("\nDigite o nome da sétima matéria: ");
        } 
        else if (i == 7) 
        {
            printf("\nDigite o nome da oitava matéria: ");
        } 
        else 
        {
            printf("\nDigite o nome da matéria %d", i+1);
        }
        if (i != 0)
        {
            fgets(aluno.notas.materias.nome[i], MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
            aluno.notas.materias.nome[i][strcspn(aluno.notas.materias.nome[i], "\n")] = 0;

            printf("Digite a nota final obtida em %s: ", aluno.notas.materias.nome[i]);
            scanf("%f", &aluno.notas.materias.nota_final[i]); fflush(stdin); setbuf(stdin, NULL);
            
            printf("Digite a porcentagem de frequencia obtida em %s: ", aluno.notas.materias.nome[i]);
            scanf("%d", &aluno.notas.materias.frequencia[i]); fflush(stdin); setbuf(stdin, NULL);
        }
    }
    return aluno;
}

float CRA(aluno aluno)
{
    aluno.notas.cra = 0;
    for (int i = 0; i < aluno.notas.numero_de_materias; i++)
    {
        aluno.notas.cra += (aluno.notas.materias.nota_final[i]*aluno.notas.materias.frequencia[i])/(100*aluno.notas.numero_de_materias);
    }
    return aluno.notas.cra;
}

int verifica_matricula(FILE *arq, char comparador[MAX_LENGTH])
{
    aluno aluno;
    while(!feof(arq))
    {
        fread(&aluno, sizeof(struct aluno), 1, arq);
        if (ferror(arq)) 
        {
            printf("Erro na leitura do arquivo na linha 183.\n");
        } 
        else 
        {
            if (strcmp(aluno.n_matricula, comparador) == 0)
            {
                rewind(arq);
                return 1;
            }
        }
    }
    rewind(arq);
    return 0;
}

int cadastro()
{
    FILE *arq = fopen("users", "a+"); aluno aluno; char comparador[MAX_LENGTH];

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo na linha 204.\n");
        exit(-1);
    } 
    else 
    {
        printf("Digite o nome do aluno: "); 
        fgets(aluno.nome_completo, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        aluno.nome_completo[strcspn(aluno.nome_completo, "\n")] = 0;

        do
        {
            printf("Digite o número de matrícula: "); 
            fgets(comparador, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
            comparador[strcspn(comparador, "\n")] = 0;

            if (!verifica_matricula(arq, comparador))
            {
                strcpy(aluno.n_matricula, comparador);
            }
            else
            {
                system("clear");
                printf("Número de matrícula já existente...\n");
            }
            rewind(arq);

        } 
        while (verifica_matricula(arq, comparador));

        while (TRUE)
        {
            printf("Digite o número de matérias que deseja guardar: ");
            scanf("%d", &aluno.notas.numero_de_materias); fflush(stdin); setbuf(stdin, NULL);
            if (aluno.notas.numero_de_materias > 0)
            {
                break;
            }
            else
            {
                system("clear");
                printf("Número inválido, digite novamente...\n\n");
            }
        }

        aluno = adiciona_materias(aluno, 0, aluno.notas.numero_de_materias);
        aluno.notas.cra = CRA(aluno);

        fwrite(&aluno, sizeof(struct aluno), 1, arq);
        fclose(arq);
    }
    system("clear");
    return menu();
}

int busca(FILE *arq) 
{
    aluno aluno; int EOF_ctrl; char comparador[MAX_LENGTH]; int n = 0;

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo na linha 264.\n");
        exit(-1);
    } 
    else 
    {
        printf("Digite o número de matrícula que deseja encontrar: ");
        fgets(comparador, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        comparador[strcspn(comparador, "\n")] = 0;

        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) 
            {
                printf("Erro na leitura do arquivo na linha 278.\n");
            } 
            else if (!strcmp(aluno.n_matricula, comparador) && EOF_ctrl != 0)
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
                printf("--------------------------------------------------------------\n");
                n = TRUE;
                break;
            }
        }
        if (!n)
        {
            printf("Nenhum usuário encontrado.\n\n");
        }

        printf("[1] - Procurar outro usuário.\n");
        printf("[ENTER 2x] - Voltar ao menu. ");

        char c = getchar(); flush;
        if (c == '\n')
        {
            system("clear"); setbuf(stdin, NULL);
            return menu();
        } 
        else if (c == '1')
        {
            system("clear"); setbuf(stdin, NULL);
            return 3;
        }
    }
}

int adiciona(FILE *arq)
{
    aluno aluno; int EOF_ctrl; char comparador[MAX_LENGTH]; int n = 0; int novas_materias;

    if (arq == NULL) 
    {
        printf("Erro na abertura do arquivo na linha 327.\n");
        exit(-1);
    } 
    else 
    {
        printf("Digite o número de matrícula que deseja adicionar matérias: ");
        fgets(comparador, MAX_LENGTH, stdin); fflush(stdin); setbuf(stdin, NULL);
        comparador[strcspn(comparador, "\n")] = 0;

        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) 
            {
                printf("Erro na leitura do arquivo na linha 341.\n");
            } 
            else if (!strcmp(aluno.n_matricula, comparador) && EOF_ctrl != 0)
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
                printf("--------------------------------------------------------------\n");
                n = TRUE;
                break;
            }
        }

        if (n)
        {
            while (n)
            {
                printf("\nDigite quantas matérias deseja adicionar: ");
                scanf("%d", &novas_materias); fflush(stdin); setbuf(stdin, NULL);

                if (novas_materias > 0)
                {
                    break;
                }
                else
                {
                    system("clear");
                    printf("Número inválido, digite novamente...\n\n");
                }
            }

            aluno = adiciona_materias(aluno, aluno.notas.numero_de_materias, aluno.notas.numero_de_materias+novas_materias);
            aluno.notas.numero_de_materias += novas_materias;
            aluno.notas.cra = CRA(aluno);

            FILE *temp = fopen("temp", "w");

            fwrite(&aluno, sizeof(struct aluno), 1, temp);
            rewind(arq);

            while (!feof(arq))
            {
                EOF_ctrl = fread(&aluno, sizeof(aluno), 1, arq);
                if (strcmp(aluno.n_matricula, comparador) != 0 && EOF_ctrl != 0)
                {
                    fwrite(&aluno, sizeof(struct aluno), 1, temp);
                }
            }

            fclose(temp);
            fclose(arq);

            remove("users");
            rename("temp", "users");

            printf("\n--------------------------------------------------------------\n");
            printf("[1] - Adicionar mais matérias.\n");
            printf("[ENTER 2x] - Voltar ao menu. ");
        }
        else
        {
            printf("Nenhum usuário encontrado.\n\n");
            fclose(arq);
            printf("[1] - Procurar outro usuário.\n");
            printf("[ENTER 2x] - Voltar ao menu. ");
        }

        char c = getchar(); flush;
        if (c == '\n')
        {
            system("clear"); setbuf(stdin, NULL);
            return menu();
        } 
        else if (c == '1')
        {
            system("clear"); setbuf(stdin, NULL);
            return 4;
        }
    }
}

int maior_q_80(FILE* arq)
{
    aluno aluno; int EOF_ctrl;

    if (arq == NULL) 
    {
        printf("Erro de abertura do arquivo na linha 437.\n");
        exit(-1);
    } 
    else 
    {
        while(!feof(arq))
        {
            EOF_ctrl = fread(&aluno, sizeof(struct aluno), 1, arq);
            if (ferror(arq)) 
            {
                printf("Erro na leitura do arquivo na linha 447.\n");
            } 
            else if (EOF_ctrl != 0 && aluno.notas.cra >= 80) 
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
        printf("--------------------------------------------------------------\n");
        printf("Tecle ENTER para sair. ");
        if (getchar() == '\n')
        {
            system("clear");
            return menu();
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int escolha; aluno aluno; FILE *arq; int teste = FALSE;

    arq = fopen("test", "r");
    if (arq != NULL)
    {
        rename("test", "users");
        fclose(arq);
        teste = TRUE;
    }

    escolha = menu();
    while (escolha != 0)
    {
        fflush(stdin); setbuf(stdin, NULL);
        
        switch (escolha)
        {
        case 0:
            break;

        case 1:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            arq = fopen("users", "r");
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
            system("clear"); fflush(stdin); setbuf(stdin, NULL);
            
            escolha = cadastro();
            break;

        case 3:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            arq = fopen("users", "r");
            if (arq == NULL) 
            {
                escolha = nenhum_usuario();
            } 
            else 
            {
                escolha = busca(arq);
                fclose(arq);
            }
            break;

        case 4:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            arq = fopen("users", "r");
            if (arq == NULL) 
            {
                escolha = nenhum_usuario();
            } 
            else 
            {
                escolha = adiciona(arq);
            }
            break;

        case 5:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);

            arq = fopen("users", "r");
            if (arq == NULL) 
            {
                escolha = nenhum_usuario();
            } 
            else 
            {
                escolha = maior_q_80(arq);
                fclose(arq);
            }
            break;

        default:
            system("clear"); fflush(stdin); setbuf(stdin, NULL);
            
            printf("Opção não válida.\n\nTecle ENTER para voltar ao menu.");
            if (getchar() == '\n')
            {
                system("clear");
                escolha = menu();
            }
            break;
        }
    }
    if (teste == TRUE) {rename("users", "test");}
    return 0;
}