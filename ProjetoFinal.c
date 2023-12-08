#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 typedef struct{
    char data[12];
    char status; 
}Presenca;


 typedef struct{
    char nome[50];
    int matricula;
    char data_nascimento[12];
    Presenca presencas[75]; 
    int quantidade_presencas; 
}Aluno;


Aluno ler_dados_aluno() {
    Aluno aluno;

    printf("\nDigite o nome do aluno: ");
    scanf("%s", aluno.nome);

    printf("Digite a matricula do aluno: ");
    scanf("%d", &aluno.matricula);

    printf("Digite a data de nascimento do aluno (DD/MM/AAAA): ");
    scanf("%s", aluno.data_nascimento);

    aluno.quantidade_presencas = 0; 

    return aluno;
}

Aluno* inserir_alunos(int quantidade_alunos, int posicao) {
    Aluno *alunos = (Aluno *)malloc(quantidade_alunos * sizeof(Aluno));
    if (alunos == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
    alunos[posicao] = ler_dados_aluno();
    


    return alunos;
}

void listar_alunos(Aluno *alunos, int posicao) {
    printf("\nLista de Alunos:\n");
    for (int i = 0; i < posicao; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Matricula: %d\n", alunos[i].matricula);
        printf("Data de Nascimento: %s\n", alunos[i].data_nascimento);

        printf("Presencas:\n");
        for (int j = 0; j < alunos[i].quantidade_presencas; j++) {
            printf("Data: %s | Status: %c\n", alunos[i].presencas[j].data, alunos[i].presencas[j].status);
        }

        printf("\n");
    }
}

void buscar_aluno(Aluno *alunos, int quantidade_alunos, int matricula) {
    for (int i = 0; i < quantidade_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("\nAluno encontrado:\n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Data de Nascimento: %s\n", alunos[i].data_nascimento);

            printf("Presencas:\n");
            for (int j = 0; j < alunos[i].quantidade_presencas; j++) {
                printf("Data: %s | Status: %c\n", alunos[i].presencas[j].data, alunos[i].presencas[j].status);
            }

            return; 
        }
    }

    printf("\nAluno com matracula %d nao encontrado.\n", matricula);
}

void alterar_dado_aluno(Aluno *alunos, int quantidade_alunos, int matricula) {
    for (int i = 0; i < quantidade_alunos; i++) {
        if (alunos[i].matricula == matricula) {
            int opcao;
            printf("\nEscolha o dado a ser alterado:\n");
            printf("1. Nome\n");
            printf("2. Matricula\n");
            printf("3. Data de Nascimento\n");
            printf("Digite o numero da opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", alunos[i].nome);
                    break;
                case 2:
                    printf("Digite a nova matricula: ");
                    scanf("%d", &alunos[i].matricula);
                    break;
                case 3:
                    printf("Digite a nova data de nascimento (DD/MM/AAAA): ");
                    scanf("%s", alunos[i].data_nascimento);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }

            printf("\nDado alterado com sucesso.\n");
            return; 
        }
    }

    printf("\nAluno com matricula %d nao encontrado.\n", matricula);
}

Aluno* remover_aluno(Aluno *alunos, int *posicao, int matricula) {
    for (int i = 0; i < *posicao; i++) {
        if (alunos[i].matricula == matricula) {
            for (int j = i; j < *posicao - 1; j++) {
                alunos[j] = alunos[j + 1];
            }

            (*posicao)--;

            printf("\nAluno removido com sucesso.\n");
            return alunos;
        }
    }

    printf("\nAluno com matricula %d nao encontrado.\n", matricula);
    return alunos;
}

void marcar_presenca(Aluno *alunos, int posicao, const char *data, int i) {
    char status;
  //  for (int i = 0; i < posicao; i++) { 
      //  if (alunos[i].matricula == matricula) {
        printf("\nO aluno %s esta presente? (Presente = P, Ausente = A)", alunos[i].nome);
        scanf(" %c", &status);
          if (alunos[i].quantidade_presencas < 75) { 
                strcpy(alunos[i].presencas[alunos[i].quantidade_presencas].data, data);
                alunos[i].presencas[alunos[i].quantidade_presencas].status = status;
                alunos[i].quantidade_presencas++;

                printf("\nChamada marcada com sucesso para o aluno %s na data %s.\n", alunos[i].nome, data);
            } else {
                printf("\nO aluno %s atingiu o limite maximo de registros de presenca.\n", alunos[i].nome);
            }

            return; 
        
    }



void salvar_chamada_em_arquivo(const char *data, Aluno *alunos, int quantidade_alunos) {
    FILE *arquivo;
    char nome_arquivo[20]; 

    sprintf(nome_arquivo, "%s.txt", data);

    arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fprintf(arquivo, "Chamada na data: %s\n\n", data);
    for (int i = 0; i < quantidade_alunos; i++) {
        fprintf(arquivo, "Aluno %d - Nome: %s | Matrícula: %d | Status: %c\n", i + 1, alunos[i].nome, alunos[i].matricula,
                (alunos[i].quantidade_presencas > 0 && alunos[i].presencas[alunos[i].quantidade_presencas - 1].status == 'P') ? 'P' : 'A');
    }

    fclose(arquivo);

    printf("\nChamada salva com sucesso no arquivo %s.\n", nome_arquivo);
}

void exibir_menu() {
    printf("\nMenu:\n");
    printf("1. Inserir Alunos\n");
    printf("2. Listar Alunos\n");
    printf("3. Buscar Aluno\n");
    printf("4. Editar Aluno\n");
    printf("5. Remover Aluno\n");
    printf("6. Realizar Chamada\n");
    printf("7. Salvar a Chamada\n");
    printf("8. Sair\n");
    printf("Escolha uma opcao (1-8): ");
}

int main() {
    int quantidade_alunos=0;
    int posicao=0;
    int opcao;
    int i = 0;

    printf("\nDigite a quantidade de alunos: ");
    scanf("%d", &quantidade_alunos);

    Aluno *alunos = (Aluno *)malloc(quantidade_alunos * sizeof(Aluno));
    printf("%d", quantidade_alunos);


    do {
        exibir_menu();

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            //    quantidade_alunos++;
                
                while(i!=quantidade_alunos){
                    alunos[posicao] = ler_dados_aluno();
                    i++;
                    posicao++;
                    
                }
                break;
            case 2:
                listar_alunos(alunos, posicao);
                break;
            case 3:
                {
                    int matricula_para_buscar;
                    printf("\nDigite a matricula do aluno que deseja buscar: ");
                    scanf("%d", &matricula_para_buscar);
                    buscar_aluno(alunos, posicao, matricula_para_buscar);
                }
                break;
            case 4:
                {
                    int matricula_para_alterar;
                    printf("\nDigite a matricula do aluno que deseja editar: ");
                    scanf("%d", &matricula_para_alterar);
                    alterar_dado_aluno(alunos, posicao, matricula_para_alterar);
                }
                break;
            case 5:
                {
                    int matricula_para_remover;
                    printf("\nDigite a matricula do aluno que deseja remover: ");
                    scanf("%d", &matricula_para_remover);
                    alunos = remover_aluno(alunos, &posicao, matricula_para_remover);
                }
                break;
            case 6:
                {
                    char data[12];
                    printf("Digite a data (DD/MM/AAAA): ");
                    scanf("%s", data);

                    for (int i = 0; i<posicao; i++){
                        marcar_presenca(alunos, posicao, data, i);
                    }
                }
                break;
            case 7:
                {
                    char data[12];
                    printf("\nDigite a data para salvar a chamada (DD_MM_AAAA): ");
                    scanf("%s", data);
                    salvar_chamada_em_arquivo(data, alunos, posicao);
                }
                break;
            case 8:
                printf("\nPrograma encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 8);

    free(alunos);

    return 0;
}