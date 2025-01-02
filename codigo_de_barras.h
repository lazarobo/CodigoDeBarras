//arquivo destinado a fazer o codigo de barras

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

// Função para gerar o array binário do código de barras
void gera_codigo_barras(char* codigo, char binario[100]) {
    int i, pos = 0;

    strcpy(&binario[pos], "101");
    pos += 3;

    // Gerar o binário com base nos 4 primeiros dígitos (L-code)
    for (i = 0; i < 4; i++) {
        const char* seq = L_code[codigo[i] - '0'];
        strcpy(&binario[pos], seq);
        pos += 7;
    }

    // Adicionar o marcador do meio
    strcpy(&binario[pos], "01010");
    pos += 5;

    // Gerar o binário com base nos 4 últimos dígitos (R-code)
    for (i = 4; i < 8; i++) {
        const char* seq = R_code[codigo[i] - '0'];
        strcpy(&binario[pos], seq);
        pos += 7;
    }

    // Adicionar o marcador de final
    strcpy(&binario[pos], "101");
    pos += 3;

    binario[pos] = '\0'; // Finalizar a string binária
}

#endif // CODIGO_BARRAS_H
