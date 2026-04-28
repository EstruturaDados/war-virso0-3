#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5 // define o número máximo de territórios que podem ser cadastrados

struct Territorio { 
    char nome[30]; // campo para o nome do territorio, um array de caracteres
    char cor[10]; // campo para a cor do territorio, um array de caracteres
    int tropas; // campo para o número de tropas no territorio, um inteiro
}; //criado a estrutura do território, contendo nome, cor e número de tropas

void limparbufferentrada() {  // define uma função para limpar o buffer de entrada do teclado
    int c;                    // Declara uma variável inteira para armazenar caracteres lidos
    while ((c = getchar()) != '\n' && c != EOF);  // Lê caracteres até encontrar nova linha ou fim de arquivo, limpando o buffer
}

int main() {
    struct Territorio territorios[MAX_TERRITORIOS]; // declara um array de estruturas Territorio para armazenar até MAX_TERRITORIOS territórios
    int totalterritorios = 0; // inicializa o contador de territórios cadastrados com 0
    int opcao; // declara uma variável para armazenar a opção escolhida pelo usuário

    do {
        printf("\nMenu War:\n"); // imprime o cabeçalho do menu
        printf("1.Cadastrar Territorio\n"); // imprime a opção 1 para cadastrar um novo território
        printf("2.Listar Territorios\n"); // imprime a opção 2 para listar os territórios cadastrados
        printf("3.Sair\n"); // imprime a opção 3 para sair do programa
        printf("Escolha uma opcao: "); // solicita ao usuário que escolha uma opção
        scanf("%d", &opcao); // lê a opção escolhida pelo usuário
        limparbufferentrada(); // chama a função para limpar o buffer após ler a opção

        switch (opcao) { // Inicia uma estrutura switch baseada na opção escolhida
            case 1: // Caso a opção seja 1, cadastra um novo território
            printf("\nCadastro de Novo Territorio\n"); // Imprime o cabeçalho do cadastro de território
            if (totalterritorios < MAX_TERRITORIOS) { // Verifica se ainda há espaço para cadastrar mais territórios
                printf("Digite o nome do territorio:"); // Solicita o nome do território
                fgets(territorios[totalterritorios].nome,30,stdin); // Lê o nome do território usando fgets
                territorios[totalterritorios].nome[strcspn(territorios[totalterritorios].nome,"\n")] = '\0'; // Remove o caractere de nova linha do final da string

                printf("Digite a cor do territorio:"); // Solicita a cor do território
                fgets(territorios[totalterritorios].cor,10,stdin); // Lê a cor do território usando fgets
                territorios[totalterritorios].cor[strcspn(territorios[totalterritorios].cor,"\n")] = '\0'; // Remove o caractere de nova linha do final da string

                printf("Digite o numero de tropas:"); // Solicita o número de tropas no território
                scanf("%d", &territorios[totalterritorios].tropas); // Lê o número de tropas como inteiro
                limparbufferentrada(); // Limpa o buffer após ler o número de tropas
                
                totalterritorios++; // Incrementa o contador de territórios cadastrados
            } else { // Caso contrário, informa que a capacidade máxima de territórios foi atingida
                printf("Capacidade maxima de territorios atingida.\n"); // Informa que não há mais espaço para cadastrar territórios
            }
            break; // Sai do case 1

            case 2:
            if (totalterritorios > 0) { // Caso a opção seja 2, verifica se há territórios cadastrados para listar
                printf("\nLista de Territorios:\n"); // Imprime o cabeçalho da lista de territórios
                for (int i = 0; i < totalterritorios; i++){ // Loop para percorrer os territórios cadastrados e imprimir suas informações
                    printf("\nTerritorio %d:\n", i + 1); // Imprime o número do território na lista (i + 1 para começar a contagem a partir de 1)
                    printf("Nome: %s\n", territorios[i].nome); // Imprime o nome do território
                    printf("Cor: %s\n", territorios[i].cor); // Imprime a cor do território
                    printf("Tropas: %d\n", territorios[i].tropas); // Imprime o número de tropas no território
                }
            } else { // Caso contrário, informa que nenhum território foi cadastrado
                printf("Nenhum territorio cadastrado.\n");
            }
            break; // Sai do case 2

            case 3: // Caso a opção seja 3, informa que o programa está saindo
            printf("Saindo do programa...\n");
            break;

            default: // Caso a opção seja inválida, informa o usuário e solicita que tente novamente
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3); // O loop continua enquanto a opção escolhida pelo usuário não for 3 (sair do programa)

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
};