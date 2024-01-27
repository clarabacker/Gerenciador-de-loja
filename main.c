#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cliente {
  char nome[100];
  char sexo;
  int idade;
};
typedef struct cliente cliente;

struct compra {
  cliente clienteInfo;
  int qtdItens;
  float totalCompra;
  char fim[100];
};
typedef struct compra compra;

// Função para cadastrar novas compras
void cadastrarCompras(FILE *arquivo, int qtdCompras, compra *compras);

// Função para ler compras registradas de um arquivo
int lerComprasRegistradas(FILE *arquivo, compra **comprasRegistradas, int *qtdTotalCompras);


int main(void) {

    //OBSERVAÇÃO: Prefixos como 'qtd' indicam quantidades

    // Variáveis para o menu e outras operações
    FILE *arquivo;
    char resposta;
    int opcaoMenu;

    // Variáveis para a opção 1 do menu
    int qtdCompras; // quantidade de compras a serem cadastradas
    compra *compras; // array para armazenar informações das compras a serem cadastradas

    // Variáveis para a opção 2 do menu
    int clienteEncontrado; //indica se um nome de cliente foi encontrado e o seu número de aparições no arquivo
    int qtdComprasRegistradas=0, qtdItensCliente=0;
    char nomeCliente[30], linhas[100];
    compra *comprasCliente, *comprasRegistradas;
    float somaValoresCliente=0, mediaValoresCliente=0;

    // Variáveis para a opção 3 do menu
    float limiteValor=0, valorTotalHomens=0, valorTotalMulheres=0, mediaCompras, valorTotalCompras=0;
    int qtdHomens=0, qtdMulheres=0, comprasComUmItem = 0, qtdTotalItens=0, maiorTamanho, idadeMenor, qtdAcima=0, tam, qtdComprasMaisNovo=0, qtdComprasMaiorNome=0;
    compra *comprasMaisNovo, *comprasMaiorNome;
    char maiorNome[30], maisNovo[30];

    do {
        printf("\033[0;35m----------------------------MENU-PRINCIPAL-----------------------------\033[0m");
        printf("\n1. Cadastrar novas compras");
        printf("\n2. Ver informações de uma compra específica, baseado no nome do cliente");
        printf("\n3. Ver informações de todas as compras");
        printf("\n4. Encerrar o programa");
        printf("\033[0;35m\n-----------------------------------------------------------------------\033[0m");
        printf("\nEscolha uma opção: ");
        scanf("%i", &opcaoMenu);

        // Comando utilizado para limpar a tela no Windows 
        system("cls");

        switch(opcaoMenu) {
            case 1:   
                do {
                    resposta = ' ';
                    printf("Opção 1 escolhida.");
                    printf("\nDigite a quantidade de compras a cadastrar: ");
                    scanf("%i", &qtdCompras);

                    while (qtdCompras <= 0) {
                        printf("\033[1;31mErro: o valor da quantidade de compras deve ser positivo\033[0m");
                        printf("\nDigite a quantidade de compras a cadastrar: ");
                        scanf("%i", &qtdCompras);
                    }

                    compras = (compra*)malloc(sizeof(compra) * qtdCompras);
                    if (compras == NULL) {
                        printf("\033[1;31m\nNão foi possível alocar memória.\n\033[0m");
                        exit(1);
                    }

                    cadastrarCompras(arquivo, qtdCompras, compras);

                    do {
                        printf("\n\nDigite 's' para cadastrar mais compras ou 'v' para voltar ao menu: ");
                        scanf(" %c", &resposta);

                        if (resposta != 's' && resposta != 'v') {
                            printf("\033[1;31mErro: Opção inválida! Tente novamente.\033[0m");
                        }
                    } while (resposta != 's' && resposta != 'v');

                    system("cls");

                    free(compras);
                    compras = NULL;

                } while (resposta=='s');

                break;

            case 2:
                do {
                    resposta = ' ';
                    clienteEncontrado = 0;

                    printf("Opção 2 escolhida.\n");
                    printf("Digite o nome do cliente: ");
                    scanf("%s", nomeCliente);


                    arquivo = fopen("registros.txt", "r");
                    if(arquivo == NULL){
                        printf("\033[1;31m\nNão foi possível abrir o arquivo.\n\033[0m");
                        return 0;
                    }

                    // Leitura do arquivo para contar as compras registradas e encontrar o cliente
                    while(fgets(linhas,sizeof(linhas),arquivo) != NULL){
                        char *token = strtok(linhas, " \t\n");
                        while(token != NULL){
                            if(strcmp(token,"fim")==0){
                                qtdComprasRegistradas++;  
                            } 
                            if(strcmp(token,nomeCliente)==0){
                                clienteEncontrado++;
                            }  
                            token = strtok(NULL, " \t\n");
                        }          
                    }

                    fclose(arquivo);

                    // Verificar se o cliente foi encontrado
                    if(clienteEncontrado == 0) {
                        printf("\033[1;31mErro: nome não encontrado!\033[0m");
                    }
                    else {
                        if (lerComprasRegistradas(arquivo, &comprasRegistradas, &qtdComprasRegistradas) != 0) {
                            return 1;
                        }

                        comprasCliente = (compra *)malloc(clienteEncontrado * sizeof(compra));
                        if(comprasCliente == NULL){
                            printf("\033[1;31m\nNão foi possível alocar memória.\n\033[0m");
                            return 1;
                        }

                        int index=0;
                        qtdItensCliente = 0, somaValoresCliente = 0, mediaValoresCliente = 0;

                        for(int i = 0; i < qtdComprasRegistradas; i++) {
                            if(strcmp(comprasRegistradas[i].clienteInfo.nome,nomeCliente)==0) {
                                comprasCliente[index] = comprasRegistradas[i];
                                qtdItensCliente += comprasRegistradas[i].qtdItens;
                                somaValoresCliente += comprasRegistradas[i].totalCompra;

                                index++;
                            }
                        }

                        mediaValoresCliente = somaValoresCliente / qtdItensCliente; 

                        printf("\033[0;35m\nNúmero de compras encontradas:\033[0m %d\n", clienteEncontrado);
                        for (int i = 0; i < clienteEncontrado; i++) {
                            printf("\033[0;35m\nInformações da compra %d:\033[0m", i + 1);
                            printf("\nQuantidades de itens comprados: %d", comprasCliente[i].qtdItens);
                            printf("\nValor total da compra: R$ %.2f\n", comprasCliente[i].totalCompra);
                        }
                        printf("\033[0;35m\nMédia de valor dos itens comprados pelo cliente:\033[0m %.2f", mediaValoresCliente);

                        free(comprasCliente);
                        comprasCliente = NULL;

                        free(comprasRegistradas);
                        comprasRegistradas = NULL;
                    }

                    do {
                        printf("\n\nDigite 'b' para pesquisar outro nome ou 'v' para voltar ao menu: ");
                        scanf(" %c", &resposta);

                        if(resposta!='b' && resposta!='v') {
                            printf("\033[1;31mErro: Opção inválida! Tente novamente.\033[0m");
                        }
                    } while(resposta !='b' && resposta != 'v');     

                    system("cls");

                } while (resposta=='b');

                break;

            case 3:
                printf("Opção 3 escolhida.\n");

                qtdComprasRegistradas = 0;

                arquivo = fopen("registros.txt", "r");
                if(arquivo == NULL){
                    printf("\033[1;31m\nNão foi possível abrir o arquivo.\n\033[0m");
                    return 0;
                }
                rewind(arquivo);

                // Leitura do arquivo para contar as compras registradas
                while(fgets(linhas,sizeof(linhas),arquivo) != NULL){
                    char *token = strtok(linhas, " \t\n");
                    while(token != NULL){
                        if(strcmp(token,"fim")==0){
                            qtdComprasRegistradas++;   
                        }  
                        token = strtok(NULL, " \t\n");
                    }          
                }
                fclose(arquivo);

                // Ler as compras registradas e alocar memória para armazená-las
                if (lerComprasRegistradas(arquivo, &comprasRegistradas, &qtdComprasRegistradas) != 0) {
                    return 1;
                }

                printf("\nDigite um valor: ");
                scanf("%f", &limiteValor);
                printf("\n");

                for(int i=0; i<qtdComprasRegistradas; i++){
                    maiorTamanho = strlen(comprasRegistradas[0].clienteInfo.nome);
                    strcpy(maiorNome, comprasRegistradas[0].clienteInfo.nome);

                    idadeMenor = comprasRegistradas[0].clienteInfo.idade;
                    strcpy(maisNovo, comprasRegistradas[0].clienteInfo.nome);

                    if(comprasRegistradas[i].totalCompra > limiteValor) {
                        qtdAcima++;
                    }

                    if(comprasRegistradas[i].qtdItens == 1) {
                        comprasComUmItem++;
                    }

                    if (comprasRegistradas[i].clienteInfo.sexo == 'm') {
                        qtdHomens++;
                        valorTotalHomens  += comprasRegistradas[i].totalCompra;
                    }
                    else {
                        qtdMulheres++;
                        valorTotalMulheres += comprasRegistradas[i].totalCompra;
                    }

                    qtdTotalItens += comprasRegistradas[i].qtdItens;
                    valorTotalCompras += comprasRegistradas[i].totalCompra;

                    tam = strlen(comprasRegistradas[i].clienteInfo.nome);
                    if(tam > maiorTamanho) {
                       strcpy(maiorNome, comprasRegistradas[i].clienteInfo.nome);
                    }

                    if(comprasRegistradas[i].clienteInfo.idade < idadeMenor) {
                        strcpy(maisNovo, comprasRegistradas[i].clienteInfo.nome);
                    }
                }

                mediaCompras = valorTotalCompras/qtdComprasRegistradas;

                printf("\033[0;35m\nDados gerais:\n\033[0m");
                printf("Número de compras acima do valor especificado: %d\n", qtdAcima);
                printf("Número de compras com apenas 1 item: %d\n", comprasComUmItem);
                printf("Número de compradores homens: %d\n", qtdHomens);
                printf("Número de compradores mulheres: %d\n", qtdMulheres);
                printf("Valor total comprado pelos homens: %.2f\n", valorTotalHomens );
                printf("Valor total comprado pelas mulheres: %.2f\n", valorTotalMulheres);
                printf("Número total de itens vendidos: %d\n", qtdTotalItens);
                printf("Número total de compras: %d\n", qtdComprasRegistradas);
                printf("Valor total de compras: R$ %.2f\n", valorTotalCompras);
                printf("Valor médio de uma compra: %.2f\n", mediaCompras);


                // Busca de compras do cliente de maior nome e do cliente mais novo
                for(int i = 0; i < qtdComprasRegistradas; i++) {
                    if(strcmp(comprasRegistradas[i].clienteInfo.nome,maisNovo)==0) {
                        qtdComprasMaisNovo++;
                    }
                    if(strcmp(comprasRegistradas[i].clienteInfo.nome,maiorNome)==0) {
                        qtdComprasMaiorNome++;
                    }
                }


                // Cliente de maior nome
                comprasMaiorNome = (compra *)malloc(qtdComprasMaiorNome * sizeof(compra));
                if(comprasMaiorNome== NULL){
                    printf("\033[1;31m\nNão foi possível alocar memória.\n\033[0m");
                    return 1;
                }
                
                int k=0;
                for(int i = 0; i < qtdComprasRegistradas; i++) {
                    if(strcmp(comprasRegistradas[i].clienteInfo.nome,maiorNome)==0) {
                        comprasMaiorNome[k] = comprasRegistradas[i];
                        k++;
                    }
                }

                printf("\033[0;35m\n\nDados do cliente de maior nome:\033[0m\n");
                for (int i = 0; i < qtdComprasMaiorNome; i++) {
                    if (i==0) {
                        printf("\nNome: %s", comprasMaiorNome[i].clienteInfo.nome);
                        printf("\nSexo: %c", comprasMaiorNome[i].clienteInfo.sexo);
                        printf("\nIdade: %i", comprasMaiorNome[i].clienteInfo.idade);
                        printf("\nNúmero de compras: %i\n\n", qtdComprasMaiorNome);
                    }
                    printf("\033[0;36mInformações da compra %d:\033[0m", i + 1);
                    printf("\nQuantidades de itens comprados: %d", comprasMaiorNome[i].qtdItens);
                    printf("\nValor total da compra: R$ %.2f\n\n", comprasMaiorNome[i].totalCompra);
                }


                // Cliente mais novo
                comprasMaisNovo = (compra *)malloc(qtdComprasMaisNovo * sizeof(compra));
                if(comprasMaisNovo == NULL){
                    printf("\033[1;31m\nNão foi possível alocar memória.\n\033[0m");
                    return 1;
                }

                k=0;
                for(int i = 0; i < qtdComprasRegistradas; i++) {
                    if(strcmp(comprasRegistradas[i].clienteInfo.nome,maisNovo)==0) {
                        comprasMaisNovo[k] = comprasRegistradas[i];
                        k++;
                    }
                }

                printf("\033[0;35m\nDados do cliente mais novo:\033[0m\n");
                for (int i = 0; i < qtdComprasMaisNovo; i++) {
                    if (i==0) {
                        printf("\nNome: %s", comprasMaisNovo[i].clienteInfo.nome);
                        printf("\nSexo: %c", comprasMaisNovo[i].clienteInfo.sexo);
                        printf("\nIdade: %i", comprasMaisNovo[i].clienteInfo.idade);
                        printf("\nNúmero de compras: %i\n\n", qtdComprasMaisNovo);
                    }
                    printf("\033[0;36mInformações da compra %d:\033[0m", i + 1);
                    printf("\nQuantidades de itens comprados: %d", comprasMaisNovo[i].qtdItens);
                    printf("\nValor total da compra: R$ %.2f\n\n", comprasMaisNovo[i].totalCompra);
                }

                free(comprasMaiorNome);
                comprasMaiorNome = NULL;

                free(comprasMaisNovo);
                comprasMaisNovo = NULL;

                free(comprasRegistradas);
                comprasRegistradas = NULL;

                do {
                    printf("\nDigite 'v' para voltar ao menu principal ou 'x' para encerrar o programa: ");
                    scanf(" %c", &resposta);

                    if(resposta!='v' && resposta!='x') {
                    printf("\033[1;31mErro: Opção inválida! Tente novamente.\033[0m");
                    }
                } while(resposta!='v' && resposta!='x');


                if(resposta=='x') {
                    system("cls");
                    printf("Opção 'x' escolhida. Encerrando o programa...");
                    break;
                }

                system("cls");

                break;

            case 4:
                printf("Opção 4 escolhida. Encerrando o programa...");
                break;

            default:
                printf("\033[1;31m\nErro: Opção inválida! Tente novamente.\033[0m\n");
        }

    } while(opcaoMenu != 4 && resposta != 'x');

    printf("\nPrograma encerrado.");
    return 0;
}


void cadastrarCompras(FILE *arquivo, int qtdCompras, compra *compras) {
    for (int i = 0; i < qtdCompras; i++) {
          printf("\033[0;35m\n\nCompra %i:\033[0m\n", i + 1);

          do {
            printf("Digite o nome do cliente: ");
            scanf("%s", compras[i].clienteInfo.nome);

            if (strlen(compras[i].clienteInfo.nome) < 3) {
              printf("\033[1;31mErro: o nome do cliente deve possuir 3 ou mais letras! Tente novamente.\n\n\033[0m");
              continue;
            }
          } while (strlen(compras[i].clienteInfo.nome) < 3);

          do {
            printf("Digite o sexo do cliente ('f' ou 'm'): ");
            scanf(" %c", &compras[i].clienteInfo.sexo);

            if (compras[i].clienteInfo.sexo != 'm' &&
                compras[i].clienteInfo.sexo != 'f') {
              printf(
                  "\033[1;31mErro: sexo inválido! Tente novamente.\n\n\033[0m");
            }
          } while (compras[i].clienteInfo.sexo != 'm' &&
                   compras[i].clienteInfo.sexo != 'f');

          do {
            printf("Digite a idade do cliente: ");
            scanf("%i", &compras[i].clienteInfo.idade);

            if (compras[i].clienteInfo.idade < 0) {
              printf("\033[1;31mErro: a idade não pode ser um número negativo.\n\n\033[0m");
            }
          } while (compras[i].clienteInfo.idade < 0);

          do {
            printf("Digite a quantidade de itens da compra: ");
            scanf("%i", &compras[i].qtdItens);

            if (compras[i].qtdItens <= 0) {
              printf("\033[1;31mErro: o número de itens deve ser positivo! Tente novamente.\n\n\033[0m");
            }
          } while (compras[i].qtdItens <= 0);

          do {
            printf("Digite o valor total da compra: ");
            scanf("%f", &compras[i].totalCompra);

            if (compras[i].totalCompra <= 0) {
              printf("\033[1;31mErro: o valor total da compra deve ser positivo! Tente novamente.\n\n\033[0m");
            }
          } while (compras[i].totalCompra <= 0);

          arquivo = fopen("registros.txt", "a");
          if (arquivo == NULL) {
            printf("\033[1;31m\nNão foi possível abrir o arquivo.\n\033[0m");
            exit(1); 
          }
          rewind(arquivo);

          printf("\033[1;32m\nCadastrado com sucesso!\033[0m\n");

          fprintf(arquivo, "%s\n", compras[i].clienteInfo.nome);
          fprintf(arquivo, "%c\n", compras[i].clienteInfo.sexo);
          fprintf(arquivo, "%d\n", compras[i].clienteInfo.idade);
          fprintf(arquivo, "%i\n", compras[i].qtdItens);
          fprintf(arquivo, "%.2f\n", compras[i].totalCompra);
          fprintf(arquivo, "fim\n\n");

          fclose(arquivo);
        }
}


int lerComprasRegistradas(FILE *arquivo, compra **comprasRegistradas, int *qtdComprasRegistradas) {
    *comprasRegistradas = (compra *)malloc((*qtdComprasRegistradas) * sizeof(compra));
    if (*comprasRegistradas == NULL) {
        printf("\033[1;31m\nNão foi possível alocar memória.\n\033[0m");
        return 1;
    }

    arquivo = fopen("registros.txt", "r");
    if(arquivo == NULL){
        printf("\033[1;31m\nNão foi possível abrir o arquivo.\n\033[0m");
        return 1;
    }
    rewind(arquivo);

    int i = 0;

    // Ler cada linha do arquivo e armazenar as informações formatadas na estrutura comprasRegistradas, continuando até atingir o final do arquivo
    while (fscanf(arquivo, "%s %c %d %d %f %s", (*comprasRegistradas)[i].clienteInfo.nome, &(*comprasRegistradas)[i].clienteInfo.sexo, &(*comprasRegistradas)[i].clienteInfo.idade, &(*comprasRegistradas)[i].qtdItens, &(*comprasRegistradas)[i].totalCompra, (*comprasRegistradas)[i].fim) != EOF) {
        i++;
    }
    fclose(arquivo);

    return 0;
}