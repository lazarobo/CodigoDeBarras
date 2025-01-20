#ifndef CODIGO_BARRAS_H
#define CODIGO_BARRAS_H

#include <string.h>
#include <stdio.h>

//L-code e R-code
const char* L_code[] = {
    "0001101", "0011001", "0010011", "0111101", "0100011", 
    "0110001", "0101111", "0111011", "0110111", "0001011"
};

const char* R_code[] = {
    "1110010", "1100110", "1101100", "1000010", "1011100", 
    "1001110", "1010000", "1000100", "1001000", "1110100"
};

//função para gerar código binário para a imagem PBM
void gera_codigo_barras(char* codigo, char binario[100]) {
    int pos = 0;

    //marcador inicial
    strcpy(&binario[pos], "101");
    pos += 3; //comprimento do marcador inicial/final

    // Gera os 4 primeiros dígitos (L-code)
    for (int i = 0; i < 4; i++) {
        const char* seq = L_code[codigo[i] - '0'];
        strcpy(&binario[pos], seq);
        pos += 7; // Comprimento de cada dígito
    }

    //marcador do meio
    strcpy(&binario[pos], "01010");
    pos += 5; //comprimento do marcador do meio

    //gera os 4 últimos dígitos (R-code)
    for (int i = 4; i < 8; i++) {
        const char* seq = R_code[codigo[i] - '0'];
        strcpy(&binario[pos], seq);
        pos += 7; //comprimento de cada dígito
    }

    //marcador final
    strcpy(&binario[pos], "101");
    pos += 3; //comprimento do marcador inicial/final

    binario[pos] = '\0';
}

void salva_imagem_pbm(const char* binario, const char* nome_arquivo, int largura, int altura, int espacos, int pixels_por_area) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo %s\n", nome_arquivo);
        return;
    }

    int binario_tamanho = strlen(binario);
    int largura_codigo = binario_tamanho * pixels_por_area;
    int altura_codigo = altura - 2 * espacos;

    if (largura_codigo + 2 * espacos > largura || altura_codigo <= 0) {
        fprintf(stderr, "Erro: Dimensões inválidas para espaçamento ou código.\n");
        fclose(arquivo);
        return;
    }

    //cabeçalho do arquivo PBM
    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "%d %d\n", largura, altura);

    //gera a imagem PBM
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            if (linha >= espacos && linha < espacos + altura_codigo &&
                coluna >= espacos && coluna < espacos + largura_codigo) {
                int binario_pos = (coluna - espacos) / pixels_por_area;
                fputc(binario[binario_pos], arquivo);
            } else {
                fputc('0', arquivo);
            }
            if (coluna < largura - 1) fputc(' ', arquivo);
        }
        fputc('\n', arquivo);
    }

    fclose(arquivo);
    printf("Arquivo PBM '%s' criado com sucesso!\n", nome_arquivo);
}

#endif
