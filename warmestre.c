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

    do { // Início do loop do menu principal
        exibirmenu(); // Exibe as opções do menu
        scanf("%d", &opcao); // Lê a opção do usuário
        limparbuffentrada(); // Limpa o buffer de entrada

        switch (opcao) { // Inicia a estrutura condicional múltipla

        case 1: // Se o usuário escolher a opção 1 (Cadastrar Território)
            cadastrarterritorio(territorios, &totalterritorios, capacidade); // Chama a função de cadastro
            break; // Sai do switch

        case 2: // Se o usuário escolher a opção 2 (Atacar)
            if (totalterritorios < 2) { // Verifica se há pelo menos 2 territórios cadastrados
                printf("Precisa de pelo menos 2 territorios\n"); // Se não, exibe mensagem
            } else { // Se sim, permite o ataque
                int atk, def; // Declara variáveis para os índices do atacante e defensor

                listarterritorios(territorios, totalterritorios); // Mostra o mapa com todos os territórios

                printf("Indice atacante: "); // Pede o índice do território atacante
                scanf("%d", &atk); // Lê o índice do atacante

                printf("Indice defensor: "); // Pede o índice do território defensor
                scanf("%d", &def); // Lê o índice do defensor
                limparbuffentrada(); // Limpa o buffer de entrada

                if (atk < 0 || atk >= totalterritorios || // Verifica se o índice do atacante é válido
                    def < 0 || def >= totalterritorios || // Verifica se o índice do defensor é válido
                    atk == def) { // Verifica se atacante e defensor são diferentes
                    printf("Indices invalidos\n"); // Se inválido, exibe mensagem de erro
                    break; // Sai do case 2
                }

                atacar(territorios, atk, def); // Realiza o ataque entre os dois territórios

                listarterritorios(territorios, totalterritorios); // Mostra o mapa atualizado após o ataque

                char corJogador[10]; // Declara array para armazenar a cor do "jogador" (quem atacou)
                strcpy(corJogador, territorios[atk].cor); // Copia a cor do atacante para a variável corJogador

                if (verificarMissao(missaojogador, territorios, totalterritorios, corJogador)) { // Verifica se a missão foi cumprida
                    printf("\n🏆 PARABENS! VOCE CUMPRIU SUA MISSAO!\n"); // Se cumpriu, exibe mensagem de vitória
                    opcao = 3; // Define opcao como 3 para sair do loop
                }
            }
            break; // Sai do case 2

        case 3: // Se o usuário escolher a opção 3 (Sair)
            printf("Saindo do programa...\n"); // Exibe mensagem de encerramento
            break; // Sai do switch

        default: // Se escolher qualquer outra opção
            printf("Opcao invalida.\n"); // Exibe mensagem de erro
        }

    } while (opcao != 3); // Continua o loop enquanto opcao for diferente de 3

    liberarmemoria(territorios); // Libera a memória alocada para o vetor de territórios
    free(missaojogador); // Libera a memória alocada para a string da missão

    return 0; // Retorna 0 indicando que o programa terminou com sucesso
}

// ====== DEFINIÇÃO DAS FUNÇÕES ======

void limparbuffentrada() { // Função que limpa o buffer de entrada
    int c; // Declara variável inteira para armazenar caracteres lidos
    while ((c = getchar()) != '\n' && c != EOF); // Lê caracteres até encontrar nova linha ou fim de arquivo
} // Fim da função

void exibirmenu() { // Função que exibe o menu do jogo
    printf("\nMenu:\n"); // Exibe o título "Menu:"
    printf("1. Cadastrar Territorio\n"); // Exibe opção 1
    printf("2. Atacar\n"); // Exibe opção 2
    printf("3. Sair\n"); // Exibe opção 3
    printf("Escolha: "); // Pede para o usuário escolher
} // Fim da função

void cadastrarterritorio(struct Territorio* territorios, int* totalterritorios, int capacidade) { // Função para cadastrar um novo território
    // Parâmetros: ponteiro para o vetor de territórios, ponteiro para a quantidade total, capacidade máxima

    if (*totalterritorios >= capacidade) { // Verifica se já atingiu a capacidade máxima
        printf("Capacidade maxima atingida\n"); // Se sim, exibe mensagem
        return; // Encerra a função sem cadastrar
    }

    printf("Nome: "); // Pede o nome do novo território
    fgets(territorios[*totalterritorios].nome, 30, stdin); // Lê até 30 caracteres do nome
    territorios[*totalterritorios].nome[strcspn(territorios[*totalterritorios].nome, "\n")] = '\0'; // Remove o '\n' do final

    printf("Cor: "); // Pede a cor do novo território
    fgets(territorios[*totalterritorios].cor, 10, stdin); // Lê até 10 caracteres da cor
    territorios[*totalterritorios].cor[strcspn(territorios[*totalterritorios].cor, "\n")] = '\0'; // Remove o '\n' do final

    printf("Tropas: "); // Pede o número de tropas
    scanf("%d", &territorios[*totalterritorios].tropas); // Lê e armazena a quantidade de tropas
    limparbuffentrada(); // Limpa o buffer após scanf

    (*totalterritorios)++; // Incrementa o contador de territórios cadastrados
} // Fim da função


void listarterritorios(struct Territorio* territorios, int totalterritorios) { // Função que lista todos os territórios

    if (totalterritorios == 0) { // Verifica se há algum território cadastrado
        printf("Nenhum territorio cadastrado\n"); // Se não, exibe mensagem
        return; // Encerra a função
    }

    printf("\n--- MAPA ---\n"); // Exibe cabeçalho do mapa
    for (int i = 0; i < totalterritorios; i++) { // Loop para cada território cadastrado
        printf("[%d] %s | %s | %d tropas\n", // Exibe: índice, nome, cor e tropas
               i, // Índice do território
               territorios[i].nome, // Nome do território
               territorios[i].cor, // Cor do território
               territorios[i].tropas); // Quantidade de tropas
    } // Fim do loop
} // Fim da função
