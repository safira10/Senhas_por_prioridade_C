/*
 * classificacao_senha.c
 * MODULO 2 - Classificacao de senha (Normal, Preferencial, Urgente).
 */
#include <stdio.h>
#include "classificacao_senha.h"

/* Um contador para cada categoria: indice 0=NORMAL, 1=PREFERENCIAL, 2=URGENTE */
static int contadores[3] = {0, 0, 0};

bool temCondicaoPrioritaria(Paciente p)
{
    /* Condicoes de saude / situacao */
    if (p.gestante || p.lactante || p.necessidadeEspecial || p.obeso) {
        return true;
    }

    /* Idade: mulheres 60+ e homens 65+ */
    if (p.genero == 'F' && p.idade >= 60) {
        return true;
    } else if (p.genero == 'M' && p.idade >= 65) {
        return true;
    }

    return false;
}

Categoria classificarPaciente(Paciente p)
{
    if (p.idade > 80) {                 /* urgente: acima de 80 anos */
        return URGENTE;
    } else if (temCondicaoPrioritaria(p)) {
        return PREFERENCIAL;
    } else {
        return NORMAL;
    }
}

char prefixoCategoria(Categoria categoria)
{
    switch (categoria) {
        case URGENTE:      return 'U';
        case PREFERENCIAL: return 'P';
        default:           return 'N';
    }
}

const char *nomeCategoria(Categoria categoria)
{
    switch (categoria) {
        case URGENTE:      return "URGENTE";
        case PREFERENCIAL: return "PREFERENCIAL";
        default:           return "NORMAL";
    }
}

void gerarCodigoSenha(Categoria categoria, char *codigo)
{
    contadores[categoria]++;
    snprintf(codigo, TAM_CODIGO, "%c%03d",
             prefixoCategoria(categoria), contadores[categoria]);
}

void reiniciarContadores(void)
{
    for (int i = 0; i < 3; i++) {
        contadores[i] = 0;
    }
}
