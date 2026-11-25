/*
 * classificacao_senha.h
 * MODULO 2 - Classificacao de senha (Normal, Preferencial, Urgente).
 */
/* Include guard: impede que este arquivo seja lido duas vezes pelo compilador. */
#ifndef CLASSIFICACAO_SENHA_H
#define CLASSIFICACAO_SENHA_H

#include "tipos.h"

/* true se o paciente tem alguma condicao de prioridade (preferencial). */
bool temCondicaoPrioritaria(Paciente p);

/* Decide a categoria: URGENTE (idade > 80), PREFERENCIAL ou NORMAL. */
Categoria classificarPaciente(Paciente p);

/* Letra da categoria: 'N', 'P' ou 'U'. */
char prefixoCategoria(Categoria categoria);

/* Nome da categoria para exibir na tela. */
const char *nomeCategoria(Categoria categoria);

/* Gera o proximo codigo sequencial da categoria (N001, P001, U001...). */
void gerarCodigoSenha(Categoria categoria, char *codigo);

/* Zera os contadores de senha (usado nos testes). */
void reiniciarContadores(void);

#endif
