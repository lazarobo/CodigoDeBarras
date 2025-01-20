#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <locale.h> 
#include "codigo_de_barras.h"

#define MIN_X 200 // (largura)
#define MIN_Y 100 // (altura)
#define NOME "arquivo.pbm"
#define ESP 10
#define AREA 2

//estrutura para armazenar os dados da imagem
typedef struct {
    int altura;
    int largura;
    char nome[50];
    int espacamento;
    int area;
} ImagemPBM;

//função para validar o código
int valida_codigo(char codigo[]) {
    int digitos[8];
    int soma_impares = 0, soma_pares = 0, soma_total, dgt_vcalc, dgt_v;

    //converter para inteiro
    for (int i = 0; i < 8; i++) {
        digitos[i] = codigo[i] - '0';
    }

    //dividir pares e ímpares
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            soma_impares += digitos[i];
        } else {
            soma_pares += digitos[i];
        }
    }

    //calcular o dígito verificador correto
    soma_total = soma_impares * 3 + soma_pares;
    dgt_vcalc = (10 - (soma_total % 10)) % 10;

    //pega o dígito fornecido
    dgt_v = digitos[7];

    if (dgt_vcalc == dgt_v) {
        printf("O código de barras é válido.\n");
        return 1;
    } else {
        printf("O código de barras é inválido.\n");
        return 0;
    }
}

//função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char codigo[20]; 
    char binario[100];
    int escolha;
    ImagemPBM imagem = {MIN_Y, MIN_X, NOME, ESP, AREA}; 

    printf("Digite o código de barras EAN-8 (8 dígitos): ");
    scanf("%s", codigo);

    //verificar o tamanho do código digitado

    if (strlen(codigo) != 8) {
        printf("Erro: O código deve conter exatamente 8 dígitos.\n"); 
        return 1;
    }

    //verifica se há caractéres no código
    for (int i = 0; i < 8; i++) {
        if (!isdigit(codigo[i])) {
            printf("Erro: O código deve conter apenas números.\n");
            return 1;
        }
    }

    printf("Deseja informar altura, largura, espaçamento e area da imagem? (1 - Sim, 0 - Não): ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("Informe a altura da imagem: ");
        scanf("%d", &imagem.altura);
        printf("Informe a largura da imagem: ");
        scanf("%d", &imagem.largura);
        printf("Informe o espaçamento da imagem: ");
        scanf("%d", &imagem.espacamento);
        printf("Informe a area da imagem: ");
        scanf("%d", &imagem.area);
    }

    printf("Deseja informar o nome da imagem? (1 - Sim, 0 - Não): ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("Informe o nome da imagem: ");
        scanf("%s", imagem.nome);
        strcat(imagem.nome, ".pbm"); //adiciona .pbm no final do nome da imagem
    }

    if (valida_codigo(codigo) == 1) {
        //gerar o código obviamente
        gera_codigo_barras(codigo, binario);

        //exibir o código, dps tiro isso
        //printf("Código binário do código de barras: %s\n", binario);

        //criar imagem
        salva_imagem_pbm(binario, imagem.nome, imagem.largura, imagem.altura, imagem.espacamento, imagem.area);
    }

    //system("pause");

    printf("Pressione Enter para sair...");
    getchar();
    return 0;
}
