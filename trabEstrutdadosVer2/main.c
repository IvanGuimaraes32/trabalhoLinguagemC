#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALUNOS 10
#define NUM_NOTAS 3
#define TAM_NOME 100
#define MEDIA_APROVACAO 7.0f

typedef struct {
    char nome[TAM_NOME];
    int matricula;
    float notas[NUM_NOTAS];
    float media;
} Aluno;

void limparBufferEntrada();
void cadastrarAlunos(Aluno *alunos, int *quantidade);
void calcularMedias(Aluno *alunos, int quantidade);
float calcularMediaTurma(Aluno *alunos, int quantidade);
void exibirRelatorio(Aluno *alunos, int quantidade);
void exibirDadosAluno(const Aluno *aluno);
void exibirEstatisticasTurma(Aluno *alunos, int quantidade);

int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidade_alunos = 0;
    printf("Seja bem vindo ao sistema da TechEdu\n");
    printf("\nCadastro de alunos (limite: %d alunos)\n", MAX_ALUNOS);
    cadastrarAlunos(alunos, &quantidade_alunos);

    if (quantidade_alunos > 0) {
        calcularMedias(alunos, quantidade_alunos);
        exibirRelatorio(alunos, quantidade_alunos);
    } else {
        printf("\nNenhum aluno cadastrado. Encerrando o programa.\n");
    }

    return 0;
}
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void cadastrarAlunos(Aluno *alunos, int *quantidade) {
    int num_a_cadastrar;

    printf("\nQuantos alunos deseja cadastrar? ");
    if (scanf("%d", &num_a_cadastrar) != 1 || num_a_cadastrar <= 0) {
        printf("Numero invalido. Utilize um valor de 1 a 10. Nenhum aluno sera cadastrado.\n");
        limparBufferEntrada();
        *quantidade = 0;
        return;
    }
    limparBufferEntrada();

    if (num_a_cadastrar > MAX_ALUNOS) {
        printf("Numero excede o maximo permitido. Cadastrando %d alunos.\n", MAX_ALUNOS);
        num_a_cadastrar = MAX_ALUNOS;
    }

    *quantidade = num_a_cadastrar;

    for (int i = 0; i < *quantidade; i++) {
        printf("\nAluno %d\n", i + 1);

        printf("Nome: ");
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = 0;

        printf("Matricula: ");
        while (scanf("%d", &alunos[i].matricula) != 1) {
            printf("Matricula invalida. Digite um numero de matricula padrao da TechEdu: ");
            limparBufferEntrada();
        }
        limparBufferEntrada();

        for (int j = 0; j < NUM_NOTAS; j++) {
            do {
                printf("Nota %d (0.0 a 10.0): ", j + 1);
                if (scanf("%f", &alunos[i].notas[j]) != 1) {
                    printf("Nota invalida. Digite corretamente.\n");
                    limparBufferEntrada();
                    alunos[i].notas[j] = -1;
                } else if (alunos[i].notas[j] < 0.0f || alunos[i].notas[j] > 10.0f) {
                    printf("Nota fora do intervalo permitido. Digite entre 0.0 e 10.0.\n");
                    alunos[i].notas[j] = -1;
                }
                limparBufferEntrada();
            } while (alunos[i].notas[j] < 0.0f || alunos[i].notas[j] > 10.0f);
        }

        alunos[i].media = 0;
    }
}
void calcularMedias(Aluno *alunos, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        float soma_notas = 0;
        for (int j = 0; j < NUM_NOTAS; j++) {
            soma_notas += alunos[i].notas[j];
        }
        alunos[i].media = soma_notas / NUM_NOTAS;
    }
}
float calcularMediaTurma(Aluno *alunos, int quantidade) {
    if (quantidade == 0) return 0.0f;

    float soma_medias = 0;
    for (int i = 0; i < quantidade; i++) {
        soma_medias += alunos[i].media;
    }
    return soma_medias / quantidade;
}
void exibirDadosAluno(const Aluno *aluno) {
    printf("Aluno: %s (Matricula: %d)\n", aluno->nome, aluno->matricula);
    printf("  Notas: ");
    for (int j = 0; j < NUM_NOTAS; j++) {
        printf("%.2f ", aluno->notas[j]);
    }
    printf("\n  Media: %.2f\n", aluno->media);
}
void exibirEstatisticasTurma(Aluno *alunos, int quantidade) {
    float maior_media = alunos[0].media;
    float menor_media = alunos[0].media;
    char nome_maior[TAM_NOME];
    char nome_menor[TAM_NOME];
    strcpy(nome_maior, alunos[0].nome);
    strcpy(nome_menor, alunos[0].nome);

    int aprovados = (alunos[0].media >= MEDIA_APROVACAO) ? 1 : 0;

    for (int i = 1; i < quantidade; i++) {
        if (alunos[i].media > maior_media) {
            maior_media = alunos[i].media;
            strcpy(nome_maior, alunos[i].nome);
        }
        if (alunos[i].media < menor_media) {
            menor_media = alunos[i].media;
            strcpy(nome_menor, alunos[i].nome);
        }
        if (alunos[i].media >= MEDIA_APROVACAO) {
            aprovados++;
        }
    }

    printf("\nEstatisticas da Turma\n");
    printf("Maior media: %.2f (Aluno: %s)\n", maior_media, nome_maior);
    printf("Menor media: %.2f (Aluno: %s)\n", menor_media, nome_menor);
    printf("Media geral da turma: %.2f\n", calcularMediaTurma(alunos, quantidade));
    printf("Aprovados (media >= %.1f): %d de %d\n", MEDIA_APROVACAO, aprovados, quantidade);
}
void exibirRelatorio(Aluno *alunos, int quantidade) {
    printf("\n Relatorio da Turma\n");
    for (int i = 0; i < quantidade; i++) {
        exibirDadosAluno(&alunos[i]);
    }
    exibirEstatisticasTurma(alunos, quantidade);
}
