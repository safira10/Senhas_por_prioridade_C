/*
 * utils.c
 * Funcoes auxiliares de entrada de dados COM validacao.
 */
#include <stdio.h>    /* printf, fgets, getchar */
#include <stdlib.h>   /* atoi (texto -> numero) e exit */
#include <string.h>   /* strlen (tamanho do texto) */
#include <ctype.h>    /* toupper (letra maiuscula) e isdigit (e um digito?) */
#include "utils.h"

void lerLinha(char *destino, int tamanho)
{
    if (fgets(destino, tamanho, stdin) == NULL) {
        /* Fim da entrada (Ctrl+D / arquivo acabou): encerra com seguranca */
        printf("\nEntrada encerrada.\n");
        exit(0);
    }

    size_t n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';          /* remove o Enter */
    } else {
        int c;                          /* linha maior que o buffer: descarta o resto */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

/* Funcao auxiliar (so usada aqui): true se o texto tem de 1 a 9 caracteres
 * e todos sao digitos (0 a 9). O limite de 9 evita numero grande demais. */
static bool soTemDigitos(const char *texto)
{
    int tamanho = (int)strlen(texto);

    if (tamanho == 0 || tamanho > 9) {
        return false;
    }

    for (int i = 0; i < tamanho; i++) {
        if (!isdigit((unsigned char)texto[i])) {
            return false;
        }
    }
    return true;
}

int lerInteiro(const char *mensagem, int min, int max)
{
    char buffer[32];
    int valor;

    while (true) {
        printf("%s", mensagem);
        lerLinha(buffer, sizeof(buffer));

        /* so converte para numero se o texto for composto apenas de digitos */
        if (soTemDigitos(buffer)) {
            valor = atoi(buffer);
            if (valor >= min && valor <= max) {
                return valor;
            }
        }
        printf("Valor invalido! Digite um numero entre %d e %d.\n", min, max);
    }
}

bool lerSimNao(const char *mensagem)
{
    char buffer[8];

    while (true) {
        printf("%s (S/N): ", mensagem);
        lerLinha(buffer, sizeof(buffer));

        if (strlen(buffer) == 1) {
            char c = (char)toupper((unsigned char)buffer[0]);
            if (c == 'S') {
                return true;
            } else if (c == 'N') {
                return false;
            }
        }
        printf("Resposta invalida! Digite S ou N.\n");
    }
}

char lerGenero(void)
{
    char buffer[8];

    while (true) {
        printf("Genero do paciente (F/M): ");
        lerLinha(buffer, sizeof(buffer));

        if (strlen(buffer) == 1) {
            char c = (char)toupper((unsigned char)buffer[0]);
            if (c == 'F' || c == 'M') {
                return c;
            }
        }
        printf("Genero invalido! Digite F ou M.\n");
    }
}
