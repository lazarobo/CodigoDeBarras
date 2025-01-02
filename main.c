#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <locale.h> 
#include "codigo_de_barras.h"

// funcao para validar o código
int valida_codigo(char codigo[]) {
    int digitos[8];
    int soma_impares = 0, soma_pares = 0, soma_total, dgt_vcalc, dgt_v;

    // converter para int
    for (int i = 0; i < 8; i++) {
        digitos[i] = codigo[i] - '0';
    }

    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            soma_impares += digitos[i];
        } else {
            soma_pares += digitos[i];
        }
    }

    //calcular o digito verificador correto
    soma_total = soma_impares * 3 + soma_pares;
    dgt_vcalc = (10 - (soma_total % 10)) % 10;

    //pega o digito fornecido
    dgt_v = digitos[7];

    if (dgt_vcalc == dgt_v) {
        printf("O código de barras é válido.\n");
        return 1;
    } else {
        printf("O código de barras é inválido.\n");
        return 0;
    }
}

//funcao principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char codigo[20]; 
    char binario[100];

    printf("Digite o código de barras EAN-8 (8 dígitos): ");
    scanf("%s", codigo);

    if (strlen(codigo) != 8) {
        printf("Erro: O código deve conter exatamente 8 dígitos.\n");
        return 1;
    }

    for (int i = 0; i < 8; i++) {
        if (!isdigit(codigo[i])) {
            printf("Erro: O código deve conter apenas números.\n");
            return 1;
        }
    }


    if (valida_codigo(codigo) == 1)
    {
        // Gerar o código de barras binário
        gera_codigo_barras(codigo, binario);

        // Exibir o resultado
        printf("Código binário do código de barras: %s\n", binario);
    }
    
    system("pause");
    return 0;
}
