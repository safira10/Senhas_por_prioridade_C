/*
 * registro_atendimento.c
 * MODULO 3 - Registro de atendimento (fila, chamada e finalizacao).
 */
#include <string.h>   /* strcmp (comparar codigos de senha) */
#include <ctype.h>    /* toupper (aceitar "p001" e "P001") */
#include "registro_atendimento.h"

/* ESTRUTURA DE ARMAZENAMENTO: a fila e um vetor (array) de senhas.
 * "static" faz essas variaveis existirem somente neste arquivo: os outros
 * modulos nao mexem nelas diretamente e usam as funcoes do .h. */
static Senha fila[MAX_FILA];
static int total = 0;      /* quantas senhas existem no vetor */
static int atendidos = 0;  /* quantos atendimentos foram concluidos */

bool adicionarNaFila(Senha senha)
{
    if (total >= MAX_FILA) {
        return false;
    }
    fila[total] = senha;
    total++;
    return true;
}

int consultarProximaSenha(void)
{
    /* Percorre da categoria mais urgente para a menos urgente */
    for (int cat = URGENTE; cat >= NORMAL; cat--) {
        for (int i = 0; i < total; i++) {
            if (fila[i].status == AGUARDANDO && (int)fila[i].categoria == cat) {
                return i;   /* primeiro que chegou nessa categoria */
            }
        }
    }
    return -1;
}

int indiceEmAtendimento(void)
{
    for (int i = 0; i < total; i++) {
        if (fila[i].status == EM_ATENDIMENTO) {
            return i;
        }
    }
    return -1;
}

bool chamarPaciente(void)
{
    if (indiceEmAtendimento() != -1) {
        return false;               /* ja existe um paciente sendo atendido */
    }

    int proxima = consultarProximaSenha();
    if (proxima == -1) {
        return false;               /* fila vazia */
    }

    fila[proxima].status = EM_ATENDIMENTO;
    return true;
}

int buscarSenha(const char *codigo)
{
    char busca[TAM_CODIGO];

    /* Converte para maiuscula para aceitar "p001" e "P001" */
    int i = 0;
    while (codigo[i] != '\0' && i < TAM_CODIGO - 1) {
        busca[i] = (char)toupper((unsigned char)codigo[i]);
        i++;
    }
    busca[i] = '\0';

    for (int j = 0; j < total; j++) {
        if (strcmp(fila[j].codigo, busca) == 0) {
            return j;
        }
    }
    return -1;
}

bool finalizarAtendimento(void)
{
    int atual = indiceEmAtendimento();
    if (atual == -1) {
        return false;
    }

    fila[atual].status = FINALIZADA;
    atendidos++;
    atualizarFila();                /* tira a senha finalizada da fila */
    return true;
}

void atualizarFila(void)
{
    int j = 0;                      /* proxima posicao livre */
    for (int i = 0; i < total; i++) {
        if (fila[i].status != FINALIZADA) {
            fila[j] = fila[i];      /* "puxa" a senha para frente */
            j++;
        }
    }
    total = j;
}

int totalAguardando(void)
{
    int contador = 0;
    for (int i = 0; i < total; i++) {
        if (fila[i].status == AGUARDANDO) {
            contador++;
        }
    }
    return contador;
}

int totalNaFila(void)
{
    return total;
}

int totalAtendidos(void)
{
    return atendidos;
}

int posicaoNaFila(int indice)
{
    if (indice < 0 || indice >= total || fila[indice].status != AGUARDANDO) {
        return 0;
    }

    int posicao = 1;
    for (int i = 0; i < total; i++) {
        if (i == indice || fila[i].status != AGUARDANDO) {
            continue;
        }
        /* Quem tem categoria maior, ou mesma categoria e chegou antes, passa na frente */
        if (fila[i].categoria > fila[indice].categoria ||
            (fila[i].categoria == fila[indice].categoria && i < indice)) {
            posicao++;
        }
    }
    return posicao;
}

Senha obterSenha(int indice)
{
    /* Senha "vazia", devolvida se o indice for invalido */
    Senha vazia = {"", NORMAL, FINALIZADA};

    if (indice < 0 || indice >= total) {
        return vazia;
    }
    return fila[indice];    /* devolve uma copia da senha */
}

void reiniciarFila(void)
{
    total = 0;
    atendidos = 0;
}
