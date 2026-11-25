/*
 * tipos.h
 * Tipos de dados e constantes compartilhados por todos os modulos.
 */

/* INCLUDE GUARD (protecao contra inclusao repetida):
 * Varios arquivos .c incluem este .h. Sem protecao, o compilador leria as
 * definicoes duas vezes e daria erro de "redefinicao". O #ifndef verifica se
 * TIPOS_H ainda nao existe; se nao existir, o #define cria e o conteudo e lido
 * uma unica vez. Nas proximas inclusoes, TIPOS_H ja existe e o conteudo e pulado. */


#ifndef TIPOS_H
#define TIPOS_H

#include <stdbool.h> /* TIPO BOOL, COM OS VALORES TRUE E FALSE */

#define TAM_CODIGO 8   /* Ex.: "N001" + '\0' */  
#define MAX_FILA   100 /* Quantidade maxima de senhas na fila */

/* Categorias de atendimento (a ordem define a prioridade: maior = mais urgente) */
typedef enum { /* ENUM (enumeracao): conjunto de nomes que representam valores inteiros. */
    NORMAL = 0,
    PREFERENCIAL = 1,
    URGENTE = 2
} Categoria;

/* Situacao de uma senha dentro da fila */
typedef enum {
    AGUARDANDO,
    EM_ATENDIMENTO,
    FINALIZADA
} StatusSenha;

/* Dados informados pelo atendente sobre o paciente */
typedef struct {
    char genero;               /* 'F' ou 'M' */
    int  idade;
    bool gestante;   /* true ou false */
    bool lactante;  /* true ou false */
    bool necessidadeEspecial;   /* true ou false */
    bool obeso;  /* true ou false */
} Paciente;

/* Senha emitida para o paciente */
typedef struct {
    char        codigo[TAM_CODIGO]; /* N001, P001, U001... */
    Categoria   categoria;
    StatusSenha status;
} Senha;

#endif  /* TIPOS_H: fecha o #ifndef do include guard */
