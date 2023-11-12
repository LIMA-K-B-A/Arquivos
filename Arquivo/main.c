// main.c
#include <stdio.h>
#include "sgc.h"

int main() {
    int privilegio;
    printf("Bem-vindo ao Sistema de Gestão Comercial!\n");
    printf("Por favor, selecione o seu nível de privilégio:\n");
    printf("1. Administrador\n");
    printf("2. Usuário Convencional\n");
    printf("Escolha uma opção: ");
    scanf("%d", &privilegio);

    if (privilegio == 1) {
        autenticarComoAdministrador();
    } else if (privilegio == 2) {
        autenticarComoUsuario();
    } else {
        printf("Opção inválida. Saindo do programa.\n");
    }

    return 0;
}

