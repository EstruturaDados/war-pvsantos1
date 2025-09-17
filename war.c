#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
};

// Função para exibir o estado atual do mapa
void exibirMapa(struct Territorio territorios[]) {
    printf("\n--- Estado Atual do Mapa ---\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numTropas);
        printf("----------------------------\n");
    }
}

int main() {
    struct Territorio territorios[MAX_TERRITORIOS];

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
    
    return 0;
}
