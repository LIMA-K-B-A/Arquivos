// sgc.h
#ifndef SGC_H
#define SGC_H

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    char nome[50];
    char senha[20];
    int privilegio; 
} Usuario;

void autenticarComoAdministrador();
void autenticarComoUsuario();

void adicionarProduto();
void listarProdutos();

void adicionarUsuario();
void excluirUsuario();
void listarUsuarios();

void fazerPedido(char nomeUsuario[50]);
void listarPedidos(char nomeUsuario[50]);

void cancelarPedido();
void listarPedidosAdministrador();

#endif // SGC_H