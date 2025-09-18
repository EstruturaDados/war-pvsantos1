#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
};

// Função para exibir o estado atual do mapa
void exibirMapa(struct Territorio* territorios) {
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
void batalha(struct Territorio* territorios) {
    int atacante, defensor;
    
    // Escolha do território atacante
    printf("Escolha o território atacante (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &atacante);
    atacante--;  // Ajusta o índice para o array (0 a 4)

    // Escolha do território defensor
    printf("Escolha o território defensor (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &defensor);
    defensor--;  // Ajusta o índice para o array (0 a 4)

    if (atacante == defensor) {
        printf("Não é possível atacar o mesmo território.\n");
        return;
    }

    printf("Simulando batalha entre %s (Atacante) e %s (Defensor)...\n", 
           territorios[atacante].nome, territorios[defensor].nome);
    
    // Gerando dados de batalha aleatórios
    srand(time(NULL));  // Inicializa a semente para números aleatórios
    int ataque = rand() % 6 + 1;   // Gera um número entre 1 e 6
    int defesa = rand() % 6 + 1;   // Gera um número entre 1 e 6

    printf("Resultado da batalha:\n");
    printf("Atacante: %d\n", ataque);
    printf("Defensor: %d\n", defesa);

    // Lógica da batalha
    if (ataque > defesa) {
        printf("O atacante venceu!\n");
        territorios[defensor].numTropas -= 1;  // O defensor perde 1 tropa

        if (territorios[defensor].numTropas <= 0) {
            printf("O território %s foi conquistado!\n", territorios[defensor].nome);
            // O território atacante conquista o território defensor
            strcpy(territorios[defensor].nome, territorios[atacante].nome);
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = territorios[atacante].numTropas;
        }
    } else if (ataque < defesa) {
        printf("O defensor venceu!\n");
    } else {
        printf("Empate! O atacante vence por regra.\n");
        territorios[defensor].numTropas -= 1;  // O defensor perde 1 tropa

        if (territorios[defensor].numTropas <= 0) {
            printf("O território %s foi conquistado pelo atacante!\n", territorios[defensor].nome);
            // O território atacante conquista o território defensor
            strcpy(territorios[defensor].nome, territorios[atacante].nome);
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = territorios[atacante].numTropas;
        }
    }

    printf("----------------------------\n");
}

int main() {
    struct Territorio* territorios = (struct Territorio*)calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Cadastro do Território %d\n", i + 1);
        
        // Leitura do nome do território
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, TAM_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n' da entrada
        
        // Leitura da cor do exército
        printf("Digite a cor do exército dominante: ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0'; // Remove o '\n' da entrada
        
        // Leitura do número de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // Limpa o buffer de entrada
        
        printf("----------------------------\n");
    }

    // Exibição do estado atual do mapa
    exibirMapa(territorios);

    // Fase de ataques
    char continuar;
    do {
        batalha(territorios);
        exibirMapa(territorios);
        
        printf("Deseja continuar a batalha? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // Limpa o buffer de entrada
    } while (continuar == 's' || continuar == 'S');

    // Liberando a memória alocada
    free(territorios);
    
    return 0;
}
