// usuario.c
#include <stdio.h>
#include <string.h>
#include "sgc.h"

void autenticarComoUsuario() {
    char nome[50];
    char senha[20];

    printf("Digite seu nome de usuário: ");
    scanf("%s", nome);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    FILE *usuarios = fopen("usuarios.txt", "r");
    if (!usuarios) {
        printf("Não foi possível abrir o arquivo de usuários.\n");
        return;
    }

    Usuario usuario;

    while (fscanf(usuarios, "%s %s %d", usuario.nome, usuario.senha, &usuario.privilegio) != EOF) {
        if (strcmp(usuario.nome, nome) == 0 && strcmp(usuario.senha, senha) == 0) {
            if (usuario.privilegio == 0) {
                int escolha;
                do {
                    printf("\nMenu Usuário Convencional:\n");
                    printf("1. Fazer Pedido\n");
                    printf("2. Listar Produtos\n");
                    printf("3. Listar Meus Pedidos\n");
                    printf("0. Sair\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &escolha);

                    switch (escolha) {
                        case 1:
                            fazerPedido(nome);
                            break;
                        case 2:
                            listarProdutos();
                            break;
                        case 3:
                            listarPedidos(usuario.nome);
                            break;
                        case 0:
                            return;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (escolha != 0);
            } else {
                printf("Você não é um usuário convencional. Faça login como administrador.\n");
            }
            fclose(usuarios);
            return;
        }
    }

    printf("Nome de usuário ou senha incorretos.\n");
    fclose(usuarios);
}

void fazerPedido(char nomeUsuario[50]) {
    FILE *estoque = fopen("estoque.txt", "r");
    if (!estoque) {
        printf("Não foi possível abrir o arquivo de estoque.\n");
        return;
    }

    FILE *pedidos = fopen("pedidos.txt", "a");
    if (!pedidos) {
        printf("Não foi possível abrir o arquivo de pedidos.\n");
        fclose(estoque);
        return;
    }

    char nomeProduto[50];
    int quantidade;

    printf("Digite o nome do produto que deseja pedir: ");
    scanf("%s", nomeProduto);

    Produto produto;

    while (fscanf(estoque, "%s %f %d", produto.nome, &produto.preco, &produto.quantidade) != EOF) {
        if (strcmp(produto.nome, nomeProduto) == 0) {
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);

            if (quantidade > 0 && quantidade <= produto.quantidade) {
                fprintf(pedidos, "%s %d\n", produto.nome, quantidade);
                printf("Pedido realizado com sucesso!\n");
                fclose(estoque);
                fclose(pedidos);
                return;
            } else {
                printf("Quantidade inválida. Tente novamente.\n");
                fclose(estoque);
                fclose(pedidos);
                return;
            }
        }
    }

    printf("Produto não encontrado no estoque.\n");
    fclose(estoque);
    fclose(pedidos);
}

void listarPedidos(char nomeUsuario[50]) {
    FILE *pedidos = fopen("pedidos.txt", "r");
    if (!pedidos) {
        printf("Não foi possível abrir o arquivo de pedidos.\n");
        return;
    }

    Produto produto;
    int quantidade;

    printf("\nMeus Pedidos:\n");
    printf("%-20s%-10s\n", "Nome", "Quantidade");
    while (fscanf(pedidos, "%s %d", produto.nome, &quantidade) != EOF) {
        if (strcmp(produto.nome, nomeUsuario) == 0) {
            printf("%-20s%-10d\n", produto.nome, quantidade);
        }
    }

    fclose(pedidos);
}