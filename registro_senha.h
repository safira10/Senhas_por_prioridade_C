/*
 * registro_senha.h
 * MODULO 1 - Registro de senha (coleta dos dados e emissao da senha).
 */
/* Include guard: impede que este arquivo seja lido duas vezes pelo compilador. */

#ifndef REGISTRO_SENHA_H
#define REGISTRO_SENHA_H

#include "tipos.h"

/* Pergunta ao atendente os dados do paciente (com validacao). */
Paciente coletarDadosPaciente(void);

/* Cria uma senha ja classificada para o paciente (status AGUARDANDO). */
Senha emitirSenha(Paciente paciente);

/* Fluxo completo: coleta dados, emite a senha, coloca na fila e mostra o resultado. */
void registrarSenha(void);

#endif
