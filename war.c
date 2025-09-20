#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

// Definindo a estrutura do território
struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
    int conquistado;  // Variável para indicar se o território foi conquistado
};

// Função para gerar um nome aleatório de território
void gerarNomeTerritorio(char* nome) {
    const char* nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia", "México", "Espanha", "França", "Alemanha", "Japão"};
    int index = rand() % 10;  // Escolhe um nome aleatório
    strcpy(nome, nomes[index]);
}

// Função para gerar uma cor aleatória de exército
void gerarCorExercito(char* corExercito, int i) {
    const char* cores[] = {"Azul", "Vermelho", "Amarelo", "Preto"};
    if (i == 0) {
        strcpy(corExercito, "Verde");  // Força o primeiro território a ser verde
    } else {
        int index = rand() % 4;  // Escolhe uma cor aleatória, exceto verde
        strcpy(corExercito, cores[index]);
    }
}

// Função para inicializar os territórios com valores aleatórios
void inicializarTerritorios(struct Territorio* territorios) {
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        gerarNomeTerritorio(territorios[i].nome);  // Gera nome aleatório
        gerarCorExercito(territorios[i].corExercito, i);  // Gera cor aleatória, forçando o verde para o primeiro
        territorios[i].numTropas = rand() % 6 + 5;  // Gera número aleatório de tropas entre 5 e 10
        territorios[i].conquistado = 0;  // Inicializa como não conquistado
    }
}

// Função para exibir o estado atual do mapa
void exibirMapa(const struct Territorio* territorios) {
    printf("\n--- Estado Atual do Mapa ---\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("----------------------------\n");
    }
}

// Função para simular um ataque entre dois territórios
int batalha(struct Territorio* territorios, int atacante, int defensor) {
    printf("Simulando batalha entre %s (Atacante) e %s (Defensor)...\n", 
           territorios[atacante].nome, territorios[defensor].nome);
    
    // Gerando dados de batalha aleatórios
    srand(time(NULL));  // Inicializa a semente para números aleatórios
    int ataque = rand() % 6 + 1;  // Gera um número entre 1 e 6
    int defesa = rand() % 6 + 1;  // Gera um número entre 1 e 6

    printf("Resultado da batalha:\n");
    printf("Atacante: %d\n", ataque);
    printf("Defensor: %d\n", defesa);

    // Lógica da batalha
    if (ataque > defesa) {
        printf("O atacante venceu!\n");
        territorios[defensor].numTropas -= 1;  // O defensor perde 1 tropa

        if (territorios[defensor].numTropas <= 0) {
            printf("O território %s foi conquistado!\n", territorios[defensor].nome);
            // O atacante conquista o território defensor
            strcpy(territorios[defensor].nome, territorios[atacante].nome);  // Atualiza nome
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);  // Atualiza cor do exército
            territorios[defensor].numTropas = territorios[atacante].numTropas;  // Atualiza número de tropas
            territorios[defensor].conquistado = 1;  // Marca o território como conquistado
            return 1;  // Retorna que o território foi conquistado
        }
    } else if (ataque < defesa) {
        printf("O defensor venceu!\n");
    } else {  // Empate
        printf("Empate! O atacante vence por regra.\n");
        territorios[defensor].numTropas -= 1;  // O defensor perde 1 tropa

        if (territorios[defensor].numTropas <= 0) {
            printf("O território %s foi conquistado pelo atacante!\n", territorios[defensor].nome);
            // O atacante conquista o território defensor
            strcpy(territorios[defensor].nome, territorios[atacante].nome);  // Atualiza nome
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);  // Atualiza cor do exército
            territorios[defensor].numTropas = territorios[atacante].numTropas;  // Atualiza número de tropas
            territorios[defensor].conquistado = 1;  // Marca o território como conquistado
            return 1;  // Retorna que o território foi conquistado
        }
    }

    return 0;  // Retorna que nenhum território foi conquistado
}

// Função para verificar se a missão foi cumprida
int verificarMissao(struct Territorio* territorios, int totalTerritoriosConquistados) {
    int destruirVerde = 1; // Assume que o exército verde foi destruído no início
    int conquistar3Territorios = totalTerritoriosConquistados >= 3;

    printf("\n--- Verificação da Missão ---\n");

    // Verifica se o exército verde ainda existe
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        // Se encontrar qualquer território com a cor "Verde", a condição falha
        if (strcmp(territorios[i].corExercito, "Verde") == 0) {
            destruirVerde = 0;
            printf(">>> O exército Verde ainda existe no território %s!\n", territorios[i].nome);
            break; // Sai do loop assim que encontrar o primeiro
        }
    }
    
    // Lógica corrigida: a missão é cumprida se a primeira condição E a segunda forem verdadeiras
    if (destruirVerde && conquistar3Territorios) {
        printf("Missão cumprida: Você destruiu o exército Verde e conquistou 3 ou mais territórios!\n");
        return 1;  // Missão cumprida
    }

    printf("Missão não cumprida ainda.\n");
    return 0;  // Missão não cumprida
}

int main() {
    struct Territorio* territorios = (struct Territorio*)calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
    int totalTerritoriosConquistados = 0;

    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Inicializa os territórios com nomes, cores e tropas aleatórios
    inicializarTerritorios(territorios);
    
    // Menu interativo
    int escolha;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                int atacante, defensor;
                exibirMapa(territorios);
                printf("Escolha o território atacante (1 a %d): ", MAX_TERRITORIOS);
                scanf("%d", &atacante);
                atacante--;  // Ajusta o índice para o array (0 a 4)

                printf("Escolha o território defensor (1 a %d): ", MAX_TERRITORIOS);
                scanf("%d", &defensor);
                defensor--;  // Ajusta o índice para o array (0 a 4)

                if (atacante != defensor) {
                    int conquistado = batalha(territorios, atacante, defensor);
                    if (conquistado) {
                        totalTerritoriosConquistados++;
                    }
                } else {
                    printf("Não é possível atacar o mesmo território.\n");
                }
                break;
            }
            case 2:
                if(verificarMissao(territorios, totalTerritoriosConquistados)) {
                    // Se a missão for cumprida, encerra o jogo
                    escolha = 0;
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        if(escolha != 0) {
            exibirMapa(territorios);
        }
    } while (escolha != 0);

    // Liberando a memória alocada
    free(territorios);
    
    return 0;
}