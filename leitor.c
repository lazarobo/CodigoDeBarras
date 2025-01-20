#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodifica_barras.h"

//função para verificar se o arquivo é PBM válido
int verifica_pbm(FILE *arquivo) {
    char tipo[3];
    fscanf(arquivo, "%2s", tipo);
    if (strcmp(tipo, "P1") != 0) {
        printf("Erro: O arquivo não é um PBM válido.\n");
        return 0;
    } else {
        printf("Arquivo ok!\n");
        return 1;
    }
}

//função para carregar e processar o arquivo PBM
void processa_pbm(const char *nome_arquivo) {

    char tipo[3];
    int largura, altura;
    int *linha_codigo = NULL;
    int encontrou = 0;

    //abrir o arquivo para validação
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    //verifica se o arquivo é um PBM válido
    if (!verifica_pbm(arquivo)) {
        fclose(arquivo);
        return;
    }

    //reposicionar o ponteiro do arquivo para ler o cabeçalho novamente
    rewind(arquivo);

    //ler o cabeçalho do PBM
    fscanf(arquivo, "%2s", tipo);
    fscanf(arquivo, "%d %d", &largura, &altura);

    //alocar matriz para armazenar os dados da imagem
    int **matriz = (int **)malloc(altura * sizeof(int *));
    for (int i = 0; i < altura; i++) {
        matriz[i] = (int *)malloc(largura * sizeof(int));
    }

    //ler os dados da imagem linha por linha
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    fclose(arquivo);

    //procurar o primeiro "1" e pegar a linha correspondente
    for (int i = 0; i < altura && !encontrou; i++) {
        for (int j = 0; j < largura; j++) {
            if (matriz[i][j] == 1) {
                linha_codigo = (int *)malloc(largura * sizeof(int));
                for (int k = 0; k < largura; k++) {
                    linha_codigo[k] = matriz[i][k];
                }
                encontrou = 1;
                break;
            }
        }
    }

    //verificar se uma linha foi encontrada
    if (linha_codigo) {
        printf("Linha encontrada:\n");
        for (int i = 0; i < largura; i++) {
            printf("%d ", linha_codigo[i]);
        }
        printf("\n");

        //converter a linha de int para char
        char *linha_char = (char *)malloc((largura + 1) * sizeof(char));
        for (int i = 0; i < largura; i++) {
            linha_char[i] = linha_codigo[i] + '0'; //conversao
        }
        linha_char[largura] = '\0'; //terminar a string

        //decodificar a linha e exibir o resultado
        char codigo_decodificado[10];
        decodifica_array(linha_char, codigo_decodificado);
        printf("Código decodificado: %s\n", codigo_decodificado);

        free(linha_char);
        free(linha_codigo);
    } else {
        printf("Nenhum '1' encontrado na matriz.\n");
    }

    //liberar memória alocada para a matriz
    for (int i = 0; i < altura; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    char nome_arquivo[50];

    printf("Digite o nome do arquivo PBM: ");
    scanf("%s", nome_arquivo);

    processa_pbm(nome_arquivo);

    return 0;
}
