/*
 * registro_senha.c
 * MODULO 1 - Registro de senha (coleta dos dados e emissao da senha).
 */
#include <stdio.h>
#include "registro_senha.h"
#include "classificacao_senha.h"
#include "registro_atendimento.h"
#include "utils.h"

Paciente coletarDadosPaciente(void)
{
    Paciente p;

    printf("\n--- REGISTRO DE SENHA ---\n");
    p.genero = lerGenero();
    p.idade  = lerInteiro("Idade do paciente (0 a 120): ", 0, 120);

    /* Gestante e lactante so fazem sentido para o genero feminino */
    if (p.genero == 'F') {
        p.gestante = lerSimNao("Paciente esta gestante?");
        p.lactante = lerSimNao("Paciente e lactante?");
    } else {
        p.gestante = false;
        p.lactante = false;
    }

    p.necessidadeEspecial = lerSimNao("Possui necessidade especial?");
    p.obeso               = lerSimNao("Possui condicao de obesidade?");

    return p;
}

Senha emitirSenha(Paciente paciente)
{
    Senha senha;

    senha.categoria = classificarPaciente(paciente);   /* modulo 2 decide */
    gerarCodigoSenha(senha.categoria, senha.codigo);   /* N001, P001, U001... */
    senha.status = AGUARDANDO;

    return senha;
}

void registrarSenha(void)
{
    Paciente paciente = coletarDadosPaciente();
    Senha senha = emitirSenha(paciente);

    if (adicionarNaFila(senha)) {
        printf("\n>>> Senha emitida: %s (%s)\n", senha.codigo, nomeCategoria(senha.categoria));
        printf(">>> Pacientes aguardando: %d\n", totalAguardando());
    } else {
        printf("\nFila cheia! Nao foi possivel emitir a senha.\n");
    }
}
