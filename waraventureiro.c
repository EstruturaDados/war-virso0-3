#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct Territorio { 
    char nome[30]; // campo para o nome do territorio, um array de caracteres
    char cor[10]; // campo para a cor do territorio, um array de caracteres
    int tropas; // campo para o número de tropas no territorio, um inteiro
}; //criado a estrutura do território, contendo nome, cor e número de tropas

void limparbufferentrada() {  // define uma função para limpar o buffer de entrada do teclado
    int c;                    // Declara uma variável inteira para armazenar caracteres lidos
    while ((c = getchar()) != '\n' && c != EOF);  // Lê caracteres até encontrar nova linha ou fim de arquivo, limpando o buffer
}

void atacar(struct Territorio* territorios, int total, int atk, int def) { //define a função de ataque, que recebe um array de territórios, o total de territórios, e os índices do território atacante e defensor
    struct Territorio* atacante = &territorios[atk];  // cria um ponteiro para o território atacante, apontando para o elemento do array de territórios correspondente ao índice do atacante
    struct Territorio* defensor = &territorios[def]; // cria um ponteiro para o território defensor, apontando para o elemento do array de territórios correspondente ao índice do defensor

    int dadoAtk = rand() % 6+1; // gera um número aleatório entre 1 e 6 para o ataque, simulando o lançamento de um dado
    int dadoDef=rand() % 6+1; // gera um número aleatório entre 1 e 6 para a defesa, simulando o lançamento de um dado

    printf("\n --- ATAQUE ---\n"); // imprime um cabeçalho para a seção de ataque
    printf("Atacante(%s) rolou %d\n", atacante -> nome, dadoAtk); // imprime o nome do território atacante e o resultado do dado de ataque
    printf("Defensor(%s) rolou %d\n", defensor ->nome, dadoDef); // imprime o nome do território defensor e o resultado do dado de defesa

    if (dadoAtk > dadoDef){ // compara os resultados dos dados para determinar o vencedor do ataque
        printf("VITORIA DO ATACANTE! O Defensor perdeu 1 tropa"); // se o ataque for bem-sucedido, imprime uma mensagem indicando a vitória do atacante e a perda de uma tropa pelo defensor

        defensor ->tropas --; // decrementa o número de tropas do território defensor em 1

        if(defensor-> tropas <= 0) { // verifica se o território defensor ficou sem tropas após a perda
            printf("Territorio Conquistado!\n"); // se o território defensor for conquistado (sem tropas restantes), imprime uma mensagem indicando a conquista do território
            
            strcpy(defensor->cor, atacante->cor); // copia a cor do território atacante para o território defensor, indicando que o defensor agora pertence ao atacante
            defensor->tropas = atacante->tropas / 2; // o número de tropas transferidas para o território conquistado é a metade do número de tropas do atacante, e o número de tropas do atacante é reduzido pela metade
            atacante -> tropas /= 2; // divide o número de tropas do atacante por 2, reduzindo-o pela metade após a conquista do território defensor
        }
    } else {
        printf("defensor venceu\n"); // se o defensor vencer o ataque, imprime uma mensagem indicando a vitória do defensor e a perda de uma tropa pelo atacante
        atacante->tropas -=1; // decrementa o número de tropas do território atacante em 1, indicando a perda de uma tropa pelo atacante
        }

        printf("\n--- ESTADO ATUAL ---\n"); // imprime um cabeçalho para a seção de estado atual dos territórios
        for (int i=0; i < total; i++) { // loop para percorrer todos os territórios e imprimir suas informações atuais após o ataque
            printf("[%d] %s / Cor: %s / %d\n", // imprime o índice do território, seu nome, cor e número de tropas
            i, // índice do território no array
            territorios[i].nome, // nome do território
            territorios[i].cor, // cor do território
            territorios[i].tropas); // número de tropas no território
        }
}


int main() { // função principal do programa, onde a execução começa
    srand(time(NULL)); // inicializa a semente para a geração de números aleatórios usando o tempo atual, garantindo que os resultados dos dados sejam diferentes a cada execução do programa

    int capacidade; // declara uma variável inteira para armazenar a capacidade máxima de territórios que o usuário deseja cadastrar
    printf("Digite o numero maximo de territorios: "); // solicita ao usuário que digite o número máximo de territórios que deseja cadastrar
    scanf("%d", &capacidade); // lê a capacidade máxima de territórios como um inteiro e armazena na variável 'capacidade'
    limparbufferentrada(); // chama a função para limpar o buffer de entrada após ler a capacidade, garantindo que não haja caracteres residuais que possam interferir nas próximas entradas do usuário

    struct Territorio* territorios = malloc(capacidade * sizeof(struct Territorio)); // aloca dinamicamente um array de estruturas 'Territorio' com o tamanho definido pela capacidade máxima de territórios, usando malloc para reservar a memória necessária
    if (territorios == NULL){ // verifica se a alocação de memória foi bem-sucedida, verificando se o ponteiro 'territorios' é NULL
        printf("Erro ao alocar memoria.\n"); // se a alocação falhar, imprime uma mensagem de erro e retorna 1 para indicar que o programa terminou com um erro
        return 1; // retorna 1 para indicar que o programa terminou com um erro devido à falha na alocação de memória
    }

    int totalterritorios = 0; // declara e inicializa uma variável inteira para contar o total de territórios cadastrados, começando em 0
    int opcao; // declara uma variável para armazenar a opção escolhida pelo usuário

    do {
        printf("\nMenu War:\n"); // imprime o cabeçalho do menu
        printf("1.Cadastrar Territorio\n"); // imprime a opção 1 para cadastrar um novo território
        printf("2.Listar Territorios\n"); // imprime a opção 2 para listar os territórios cadastrados
        printf("3.Jogar\n"); // imprime a opção 3 para começar o jogo
        printf("4.Sair\n"); // imprime a opção 4 para sair do programa
        printf("Escolha uma opcao: "); // solicita ao usuário que escolha uma opção
        scanf("%d", &opcao); // lê a opção escolhida pelo usuário
        limparbufferentrada(); // chama a função para limpar o buffer após ler a opção

        switch (opcao) { // Inicia uma estrutura switch baseada na opção escolhida
            case 1: // Caso a opção seja 1, cadastra um novo território
            printf("\nCadastro de Novo Territorio\n"); // Imprime o cabeçalho do cadastro de território
            if (totalterritorios < capacidade) { // Verifica se ainda há espaço para cadastrar mais territórios
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

            case 3:{ // Caso a opção seja 3, inicia a fase de ataque entre os territórios cadastrados
                if (totalterritorios < 2) { // verifica se há pelo menos 2 territórios cadastrados para realizar um ataque, caso contrário, informa que é necessário ter pelo menos 2 territórios
                    printf("\nPrecisa de pelo menos 2 territorios.\n"); // Informa que é necessário ter pelo menos 2 territórios para realizar um ataque
                    break; // Sai do case 3 se não houver territórios suficientes para o ataque
                }

                int atk, def; // Declara variáveis para armazenar os índices do território atacante e defensor escolhidos pelo usuário

                printf("\nEscolha o territorio atacante: "); //solicita ao usuário que escolha o território atacante, exibindo uma mensagem de prompt
                scanf("%d", &atk); // Lê o índice do território atacante escolhido pelo usuário e armazena na variável 'atk'

                printf("\nEscolha o territorio defensor: "); // solicita ao usuário que escolha o território defensor, exibindo uma mensagem de prompt
                scanf("%d", &def); // lê o índice do território defensor escolhido pelo usuário e armazena na variável 'def'
                limparbufferentrada(); // limpa o buffer após ler os índices do atacante e defensor para garantir que não haja caracteres residuais que possam interferir nas próximas entradas do usuário

                if (atk < 0 || atk >= totalterritorios || // verifica se os índices do território atacante e defensor são válidos, ou seja, se estão dentro do intervalo de territórios cadastrados
                    def < 0 || def >= totalterritorios) { // Se os índices forem inválidos, informa o usuário e sai do case 3
                    printf("\nIndices invalidos.\n"); //informa que os índices são inválidos
                    break; // Sai do case 3 se os índices forem inválidos
                }

                if (atk == def) { // verifica se o território atacante e defensor são o mesmo, o que não é permitido, e informa o usuário sobre a impossibilidade de atacar a si mesmo
                    printf("\nNao pode atacar a si mesmo.\n"); // informa que não é possível atacar a si mesmo
                    break; // sai do case 3 se o usuário tentar atacar a si mesmo, garantindo que o ataque seja realizado entre territórios diferentes
                }

                atacar(territorios, totalterritorios, atk, def); // chama a função de ataque, passando o array de territórios, o total de territórios cadastrados, e os índices do território atacante e defensor escolhidos pelo usuário para realizar o ataque e atualizar o estado dos territórios envolvidos
                break; // sai do case 3 após realizar o ataque
            }
            
            case 4: // Caso a opção seja 4, informa que o programa está saindo
            printf("Saindo do programa...\n");
            break;

            default: // Caso a opção seja inválida, informa o usuário e solicita que tente novamente
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4); // O loop continua enquanto a opção escolhida pelo usuário não for 3 (sair do programa)

    free(territorios); // Libera a memória alocada para o array de territórios, garantindo que não haja vazamento de memória após o término do programa

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
};