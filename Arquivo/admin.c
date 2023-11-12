// admin.c
#include <stdio.h>
#include <string.h>
#include "sgc.h"

void autenticarComoAdministrador() {
    char senha[20];
    printf("Digite a senha de administrador: ");
    scanf("%s", senha);

    if (strcmp(senha, "senha123") == 0) {
        printf("Autenticação bem-sucedida como administrador.\n");
    } else {
        printf("Autenticação falhou. Tente novamente.\n");
        return;
    }

    int escolha;
    do {
        printf("\nMenu Administrador:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Adicionar Usuário\n");
        printf("4. Excluir Usuário\n");
        printf("5. Listar Usuários\n");
        printf("6. Cancelar Pedido\n");
        printf("7. Listar Pedidos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                adicionarUsuario();
                break;
            case 4:
                excluirUsuario();
                break;
            case 5:
                listarUsuarios();
                break;
            case 6:
                cancelarPedido();
                break;
            case 7:
                listarPedidosAdministrador();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

void adicionarProduto() {
    FILE *estoque = fopen("estoque.txt", "a");
    if (!estoque) {
        printf("Não foi possível abrir o arquivo de estoque.\n");
        return;
    }

    Produto novoProduto;

    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto.nome);
    printf("Digite o preço do produto: ");
    scanf("%f", &novoProduto.preco);
    printf("Digite a quantidade disponível: ");
    scanf("%d", &novoProduto.quantidade);

    fprintf(estoque, "%s %.2f %d\n", novoProduto.nome, novoProduto.preco, novoProduto.quantidade);

    fclose(estoque);
}

void listarProdutos() {
    FILE *estoque = fopen("estoque.txt", "r");
    if (!estoque) {
        printf("Não foi possível abrir o arquivo de estoque.\n");
        return;
    }

    Produto produto;

    printf("\nLista de Produtos:\n");
    printf("%-20s%-10s%-10s\n", "Nome", "Preço", "Quantidade");
    while (fscanf(estoque, "%s %f %d", produto.nome, &produto.preco, &produto.quantidade) != EOF) {
        printf("%-20s%-10.2f%-10d\n", produto.nome, produto.preco, produto.quantidade);
    }

    fclose(estoque);
}

void adicionarUsuario() {
    FILE *usuarios = fopen("usuarios.txt", "a");
    if (!usuarios) {
        printf("Não foi possível abrir o arquivo de usuários.\n");
        return;
    }

    Usuario novoUsuario;

    printf("Digite o nome do usuário: ");
    scanf("%s", novoUsuario.nome);
    printf("Digite a senha do usuário: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o nível de privilégio (0 para convencional, 1 para administrador): ");
    scanf("%d", &novoUsuario.privilegio);

    fprintf(usuarios, "%s %s %d\n", novoUsuario.nome, novoUsuario.senha, novoUsuario.privilegio);

    fclose(usuarios);
}

void excluirUsuario() {
    char nome[50];
    printf("Digite o nome do usuário a ser excluído: ");
    scanf("%s", nome);

    FILE *usuarios = fopen("usuarios.txt", "r");
    if (!usuarios) {
        printf("Não foi possível abrir o arquivo de usuários.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Não foi possível criar o arquivo temporário.\n");
        fclose(usuarios);
        return;
    }

    Usuario usuario;

    while (fscanf(usuarios, "%s %s %d", usuario.nome, usuario.senha, &usuario.privilegio) != EOF) {
        if (strcmp(usuario.nome, nome) != 0) {
            fprintf(temp, "%s %s %d\n", usuario.nome, usuario.senha, usuario.privilegio);
        }
    }

    fclose(usuarios);
    fclose(temp);

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
}

void listarUsuarios() {
    FILE *usuarios = fopen("usuarios.txt", "r");
    if (!usuarios) {
        printf("Não foi possível abrir o arquivo de usuários.\n");
        return;
    }

    Usuario usuario;

    printf("\nLista de Usuários:\n");
    printf("%-20s%-20s%-10s\n", "Nome", "Senha", "Privilégio");
    while (fscanf(usuarios, "%s %s %d", usuario.nome, usuario.senha, &usuario.privilegio) != EOF) {
        printf("%-20s%-20s%-10d\n", usuario.nome, usuario.senha, usuario.privilegio);
    }

    fclose(usuarios);
}

void cancelarPedido() {
    FILE *pedidos = fopen("pedidos.txt", "r");
    if (!pedidos) {
        printf("Não foi possível abrir o arquivo de pedidos.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Não foi possível criar o arquivo temporário.\n");
        fclose(pedidos);
        return;
    }

    char nome[50];
    printf("Digite o nome do produto do pedido a ser cancelado: ");
    scanf("%s", nome);

    Produto produto;
    int quantidade;

    while (fscanf(pedidos, "%s %d", produto.nome, &quantidade) != EOF) {
        if (strcmp(produto.nome, nome) != 0) {
            fprintf(temp, "%s %d\n", produto.nome, quantidade);
        }
    }

    fclose(pedidos);
    fclose(temp);

    remove("pedidos.txt");
    rename("temp.txt", "pedidos.txt");
}

void listarPedidosAdministrador() {
    FILE *pedidos = fopen("pedidos.txt", "r");
    if (!pedidos) {
        printf("Não foi possível abrir o arquivo de pedidos.\n");
        return;
    }

    Produto produto;
    int quantidade;

    printf("\nLista de Pedidos:\n");
    printf("%-20s%-10s\n", "Nome", "Quantidade");
    while (fscanf(pedidos, "%s %d", produto.nome, &quantidade) != EOF) {
        printf("%-20s%-10d\n", produto.nome, quantidade);
    }

    fclose(pedidos);
}