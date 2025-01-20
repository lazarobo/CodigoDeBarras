#ifndef DECODIFICA_BARRAS_H
#define DECODIFICA_BARRAS_H

#include <stdio.h>
#include <string.h>

const char* L_code[] = {
    "0001101", "0011001", "0010011", "0111101", "0100011", 
    "0110001", "0101111", "0111011", "0110111", "0001011"
};

const char* R_code[] = {
    "1110010", "1100110", "1101100", "1000010", "1011100", 
    "1001110", "1010000", "1000100", "1001000", "1110100"
};

//função para decodificar o array
void decodifica_array(const char* array, char* resultado) {
    int pos = 0;
    int res_pos = 0;

    //verifica o marcador inicial
    if (strncmp(array + pos, "101", 3) != 0) {
        printf("Erro: Marcador inicial não encontrado.\n");
        resultado[0] = '\0';
        return;
    }
    pos += 3;

    //decodifica o (L-code)
    for (int i = 0; i < 4; i++) {
        int encontrado = 0;
        for (int j = 0; j < 10; j++) {
            if (strncmp(array + pos, L_code[j], 7) == 0) {
                resultado[res_pos++] = '0' + j;
                pos += 7;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Erro: Código L-code inválido.\n");
            resultado[0] = '\0';
            return;
        }
    }

    //marcador do meio
    if (strncmp(array + pos, "01010", 5) != 0) {
        printf("Erro: Marcador do meio não encontrado.\n");
        resultado[0] = '\0';
        return;
    }
    pos += 5;

    //decodifica o R-code
    for (int i = 0; i < 4; i++) {
        int encontrado = 0;
        for (int j = 0; j < 10; j++) {
            if (strncmp(array + pos, R_code[j], 7) == 0) {
                resultado[res_pos++] = '0' + j;
                pos += 7;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Erro: Código R-code inválido.\n");
            resultado[0] = '\0';
            return;
        }
    }

    //verifica o marcador final
    if (strncmp(array + pos, "101", 3) != 0) {
        printf("Erro: Marcador final não encontrado.\n");
        resultado[0] = '\0';
        return;
    }

    //finaliza a string decodificada
    resultado[res_pos] = '\0';
}

#endif
