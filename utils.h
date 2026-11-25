/*
 * utils.h
 * Funcoes auxiliares de entrada de dados COM validacao.
 */
/* Include guard: impede que este arquivo seja lido duas vezes pelo compilador. */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* Le uma linha do teclado de forma segura (usa fgets). */
void lerLinha(char *destino, int tamanho);

/* Pede um inteiro ate o usuario digitar um valor entre min e max. */
int lerInteiro(const char *mensagem, int min, int max);

/* Pede S ou N e devolve true para sim e false para nao. */
bool lerSimNao(const char *mensagem);

/* Pede o genero ate o usuario digitar F ou M. Devolve 'F' ou 'M'. */
char lerGenero(void);

#endif
