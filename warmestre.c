// ====== INCLUDES - BIBLIOTECAS UTILIZADAS ======

#include <stdio.h> // biblioteca padrão de entrada e saída (printf, scanf)
#include <stdlib.h> // biblioteca de funções utilitárias (calloc, malloc, free)
#include <string.h> // biblioteca para manipulação de strings (strcpy, strcmp, strcspn)
#include <time.h> // biblioteca para funções de tempo (time para gerar números aleatórios)

// ====== DEFINIÇÃO DA ESTRUTURA ======

struct Territorio { // Define uma estrutura chamada Territorio com três campos
    char nome[30]; // Array de 30 caracteres para armazenar o nome do território
    char cor[10]; // Array de 10 caracteres para armazenar a cor do território
    int tropas; // Inteiro para armazenar a quantidade de tropas no território
}; // Fim da definição da estrutura

// ====== DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES ======

void limparbuffentrada(); // protótipo: função para limpar o buffer de entrada
void exibirmenu(); // protótipo: função para exibir o menu do jogo
void cadastrarterritorio(struct Territorio* territorios, int* totalterritorios, int capacidade); // protótipo: cadastra um novo território
void listarterritorios(struct Territorio* territorios, int totalterritorios); // protótipo: lista todos os territórios cadastrados
void atacar(struct Territorio* territorios, int atk, int def); // protótipo: realiza um ataque entre dois territórios
void liberarmemoria(struct Territorio* territorios); // protótipo: libera a memória alocada

void atribuirmissao(char* destino, char* missoes[], int totalmissoes); // protótipo: atribui uma missão aleatória
void exibirmissao(char* missao); // protótipo: exibe a missão atual do jogador
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador); // protótipo: verifica se a missão foi cumprida
