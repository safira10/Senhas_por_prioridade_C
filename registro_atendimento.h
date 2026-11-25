/*
 * registro_atendimento.h
 * MODULO 3 - Registro de atendimento (fila, chamada e finalizacao).
 */

/* Include guard: impede que este arquivo seja lido duas vezes pelo compilador. */
#ifndef REGISTRO_ATENDIMENTO_H
#define REGISTRO_ATENDIMENTO_H

#include "tipos.h"   /* Senha, StatusSenha, MAX_FILA */

/* Coloca uma senha no fim da fila. Devolve false se a fila estiver cheia. */
bool adicionarNaFila(Senha senha);

/* Posicao (indice) da proxima senha a ser chamada, ou -1 se nao houver.
 * Ordem: URGENTE, depois PREFERENCIAL, depois NORMAL (por ordem de chegada). */
int consultarProximaSenha(void);

/* Registra a chamada: a proxima senha passa a EM_ATENDIMENTO.
 * Devolve false se a fila estiver vazia ou se ja houver atendimento em andamento. */
bool chamarPaciente(void);

/* Procura uma senha pelo codigo (ex.: "P001"). Devolve o indice ou -1. */
int buscarSenha(const char *codigo);

/* Indice da senha em atendimento, ou -1 se nenhuma. */
int indiceEmAtendimento(void);

/* Finaliza o atendimento atual e atualiza a fila. Devolve false se nao havia atendimento. */
bool finalizarAtendimento(void);

/* Remove da fila as senhas ja finalizadas. */
void atualizarFila(void);

/* Quantas senhas aguardam chamada. */
int totalAguardando(void);

/* Quantidade de senhas guardadas na fila (aguardando + em atendimento). */
int totalNaFila(void);

/* Quantos atendimentos ja foram finalizados. */
int totalAtendidos(void);

/* Posicao do paciente na ordem de chamada (1 = sera o proximo). 0 se nao esta aguardando. */
int posicaoNaFila(int indice);

/* Devolve uma copia da senha que esta na posicao indice da fila.
 * Se o indice for invalido, devolve uma senha vazia (codigo ""). */
Senha obterSenha(int indice);

/* Esvazia a fila e zera os contadores (usado nos testes). */
void reiniciarFila(void);

#endif /* REGISTRO_ATENDIMENTO_H */
