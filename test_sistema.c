/*
 * test_sistema.c
 * Testes automaticos dos modulos de classificacao e de atendimento.
 * Se algum assert falhar, o programa para e mostra a linha do erro.
 */
#include <stdio.h>    /* printf */
#include <string.h>   /* strcmp */
#include <assert.h>   /* assert: para o programa se uma condicao for falsa */
#include "classificacao_senha.h"
#include "registro_atendimento.h"

static Paciente criarPaciente(char genero, int idade, bool gest, bool lact, bool esp, bool ob)
{
    Paciente p = {genero, idade, gest, lact, esp, ob};
    return p;
}

static Senha criarSenha(Categoria c)
{
    Senha s;
    s.categoria = c;
    gerarCodigoSenha(c, s.codigo);
    s.status = AGUARDANDO;
    return s;
}

static void testarClassificacao(void)
{
    /* Normal */
    assert(classificarPaciente(criarPaciente('M', 30, false, false, false, false)) == NORMAL);
    assert(classificarPaciente(criarPaciente('F', 59, false, false, false, false)) == NORMAL);
    assert(classificarPaciente(criarPaciente('M', 64, false, false, false, false)) == NORMAL);

    /* Preferencial */
    assert(classificarPaciente(criarPaciente('F', 25, true,  false, false, false)) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('F', 25, false, true,  false, false)) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('M', 25, false, false, true,  false)) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('M', 25, false, false, false, true )) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('F', 60, false, false, false, false)) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('M', 65, false, false, false, false)) == PREFERENCIAL);
    assert(classificarPaciente(criarPaciente('M', 80, false, false, false, false)) == PREFERENCIAL);

    /* Urgente (idade acima de 80, mesmo sem outra condicao) */
    assert(classificarPaciente(criarPaciente('M', 81, false, false, false, false)) == URGENTE);
    assert(classificarPaciente(criarPaciente('F', 90, true,  false, true,  true )) == URGENTE);

    printf("[OK] classificacao\n");
}

static void testarCodigos(void)
{
    char codigo[TAM_CODIGO];

    reiniciarContadores();
    gerarCodigoSenha(NORMAL, codigo);
    assert(strcmp(codigo, "N001") == 0);
    gerarCodigoSenha(NORMAL, codigo);
    assert(strcmp(codigo, "N002") == 0);
    gerarCodigoSenha(PREFERENCIAL, codigo);
    assert(strcmp(codigo, "P001") == 0);
    gerarCodigoSenha(URGENTE, codigo);
    assert(strcmp(codigo, "U001") == 0);

    printf("[OK] codigos sequenciais\n");
}

static void testarFila(void)
{
    reiniciarContadores();
    reiniciarFila();

    assert(consultarProximaSenha() == -1);      /* fila vazia */
    assert(!chamarPaciente());

    adicionarNaFila(criarSenha(NORMAL));        /* N001 */
    adicionarNaFila(criarSenha(PREFERENCIAL));  /* P001 */
    adicionarNaFila(criarSenha(URGENTE));       /* U001 */
    adicionarNaFila(criarSenha(PREFERENCIAL));  /* P002 */

    /* Ordem esperada: U001, P001, P002, N001 */
    assert(strcmp(obterSenha(consultarProximaSenha()).codigo, "U001") == 0);
    assert(posicaoNaFila(buscarSenha("N001")) == 4);
    assert(buscarSenha("p002") != -1);          /* aceita minuscula */
    assert(buscarSenha("X999") == -1);

    assert(chamarPaciente());
    assert(strcmp(obterSenha(indiceEmAtendimento()).codigo, "U001") == 0);
    assert(!chamarPaciente());                  /* ja ha atendimento */

    assert(finalizarAtendimento());
    assert(totalAtendidos() == 1);
    assert(totalNaFila() == 3);                 /* fila atualizada */
    assert(buscarSenha("U001") == -1);
    assert(!finalizarAtendimento());            /* nao ha atendimento */

    assert(chamarPaciente());
    assert(strcmp(obterSenha(indiceEmAtendimento()).codigo, "P001") == 0);

    printf("[OK] fila e atendimento\n");
}

int main(void)
{
    testarClassificacao();
    testarCodigos();
    testarFila();
    printf("\nTodos os testes passaram!\n");
    return 0;
}
