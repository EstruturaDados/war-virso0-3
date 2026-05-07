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

// ====== FUNÇÃO PRINCIPAL ======

int main() { // Início da função principal
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a hora atual do sistema

    int capacidade; // Declara uma variável inteira para armazenar a capacidade máxima
    printf("Digite o numero maximo de territorios: "); // Exibe uma mensagem pedindo a capacidade máxima
    scanf("%d", &capacidade); // Lê um inteiro do usuário e armazena em capacidade
    limparbuffentrada(); // Limpa o buffer para evitar problemas com próximas leituras

    struct Territorio *territorios = calloc(capacidade, sizeof(struct Territorio)); // Aloca memória para um vetor de territórios

    if (territorios == NULL) { // Verifica se a alocação de memória falhou
        printf("Erro ao alocar memoria.\n"); // Se falhou, exibe mensagem de erro
        return 1; // Retorna 1 indicando erro
    }

    char* missoes[] = { // Declara um array de strings com as missões disponíveis
        "Conquistar 2 territorios", // Primeira missão possível
        "Eliminar todos da cor Verde" // Segunda missão possível
    };

    char* missaojogador = malloc(100); // Aloca 100 bytes para armazenar a missão do jogador
    atribuirmissao(missaojogador, missoes, 2); // Sorteia e atribui uma missão aleatória ao jogador
    exibirmissao(missaojogador); // Exibe a missão para o jogador

    int totalterritorios = 0; // Inicializa contador de territórios cadastrados em zero
    int opcao; // Variável para armazenar a opção escolhida pelo usuário