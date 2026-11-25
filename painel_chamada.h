/*
 * painel_chamada.h
 * MODULO 4 - Painel de chamada e menu principal.
 */
/* Include guard: impede que este arquivo seja lido duas vezes pelo compilador. */

#ifndef PAINEL_CHAMADA_H
#define PAINEL_CHAMADA_H

/* Mostra as opcoes do menu. */
void exibirMenu(void);

/* Mostra o painel: senha em atendimento, proxima senha e resumo da fila. */
void exibirPainel(void);

/* Lista todas as senhas da fila. */
void listarFila(void);

/* Pede um codigo e mostra a situacao da senha. */
void identificarSenhaPaciente(void);

/* Executa a acao escolhida no menu. */
void executarOpcao(int opcao);

/* Laco principal do programa (menu ate o usuario escolher sair). */
void iniciarPainel(void);

#endif
