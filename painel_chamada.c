/*
 * painel_chamada.c
 * MODULO 4 - Painel de chamada e menu principal.
 */
#include <stdio.h>   /* printf */
#include "painel_chamada.h"
#include "registro_senha.h"
#include "registro_atendimento.h"
#include "classificacao_senha.h"
#include "utils.h"

/* Funcao auxiliar (so  e usada aqui): texto da situacao da senha */
static const char *textoStatus(StatusSenha status)
{
    switch (status) {
        case AGUARDANDO:     return "Aguardando";
        case EM_ATENDIMENTO: return "Em atendimento";
        default:             return "Finalizada";
    }
}

void exibirMenu(void)
{
    printf("\n==============================================\n");
    printf("      SISTEMA DE SENHAS - ATENDIMENTO\n");
    printf("==============================================\n");
    printf(" 1 - Registrar nova senha\n");
    printf(" 2 - Consultar proxima senha a ser chamada\n");
    printf(" 3 - Chamar paciente\n");
    printf(" 4 - Identificar senha do paciente\n");
    printf(" 5 - Ver senha em atendimento\n");
    printf(" 6 - Finalizar atendimento\n");
    printf(" 7 - Listar fila\n");
    printf(" 8 - Painel de chamada\n");
    printf(" 0 - Sair\n");
    printf("==============================================\n");
}

void exibirPainel(void)
{
    int atual   = indiceEmAtendimento();
    int proxima = consultarProximaSenha();
    int total   = totalAguardando() + (atual != -1 ? 1 : 0) + totalAtendidos();
    float percentual = 0.0f;

    if (total > 0) {
        percentual = (float)totalAtendidos() * 100.0f / (float)total;
    }

    printf("\n############# PAINEL DE CHAMADA #############\n");

    if (atual != -1) {
        printf(" EM ATENDIMENTO : %s (%s)\n",
               obterSenha(atual).codigo, nomeCategoria(obterSenha(atual).categoria));
    } else {
        printf(" EM ATENDIMENTO : nenhuma\n");
    }

    if (proxima != -1) {
        printf(" PROXIMA SENHA  : %s (%s)\n",
               obterSenha(proxima).codigo, nomeCategoria(obterSenha(proxima).categoria));
    } else {
        printf(" PROXIMA SENHA  : nenhuma\n");
    }

    printf(" Aguardando     : %d\n", totalAguardando());
    printf(" Atendidos      : %d (%.1f%% do total do dia)\n", totalAtendidos(), percentual);
    printf("#############################################\n");
}

void listarFila(void)
{
    printf("\n--- FILA ATUAL ---\n");

    if (totalNaFila() == 0) {
        printf("Fila vazia.\n");
        return;
    }

    for (int i = 0; i < totalNaFila(); i++) {
        Senha s = obterSenha(i);
        printf("%s | %-12s | %s\n", s.codigo, nomeCategoria(s.categoria), textoStatus(s.status));
    }
}

void identificarSenhaPaciente(void)
{
    char codigo[TAM_CODIGO];

    printf("Digite o codigo da senha (ex.: P001): ");
    lerLinha(codigo, sizeof(codigo));

    int indice = buscarSenha(codigo);
    if (indice == -1) {
        printf("Senha nao encontrada (ela pode ja ter sido finalizada).\n");
        return;
    }

    Senha s = obterSenha(indice);
    printf("Senha %s | Categoria: %s | Situacao: %s\n",
           s.codigo, nomeCategoria(s.categoria), textoStatus(s.status));

    if (s.status == AGUARDANDO) {
        printf("Posicao na ordem de chamada: %d\n", posicaoNaFila(indice));
    }
}

void executarOpcao(int opcao)
{
    int indice;

    switch (opcao) {
        case 1:
            registrarSenha();
            break;

        case 2:
            indice = consultarProximaSenha();
            if (indice == -1) {
                printf("\nNao ha senhas aguardando.\n");
            } else {
                printf("\nProxima senha: %s (%s)\n",
                       obterSenha(indice).codigo,
                       nomeCategoria(obterSenha(indice).categoria));
            }
            break;

        case 3:
            if (chamarPaciente()) {
                indice = indiceEmAtendimento();
                printf("\nCHAMANDO SENHA %s (%s)!\n",
                       obterSenha(indice).codigo,
                       nomeCategoria(obterSenha(indice).categoria));
            } else if (indiceEmAtendimento() != -1) {
                printf("\nJa existe um atendimento em andamento. Finalize-o primeiro.\n");
            } else {
                printf("\nNao ha senhas aguardando.\n");
            }
            break;

        case 4:
            identificarSenhaPaciente();
            break;

        case 5:
            indice = indiceEmAtendimento();
            if (indice == -1) {
                printf("\nNenhum paciente em atendimento.\n");
            } else {
                printf("\nSenha em atendimento: %s (%s)\n",
                       obterSenha(indice).codigo,
                       nomeCategoria(obterSenha(indice).categoria));
            }
            break;

        case 6:
            if (finalizarAtendimento()) {
                printf("\nAtendimento finalizado. Fila atualizada.\n");
            } else {
                printf("\nNao ha atendimento em andamento.\n");
            }
            break;

        case 7:
            listarFila();
            break;

        case 8:
            exibirPainel();
            break;

        case 0:
            printf("\nEncerrando o sistema. Ate logo!\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
    }
}

void iniciarPainel(void)
{
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 8);
        executarOpcao(opcao);
    } while (opcao != 0);
}
