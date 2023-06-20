#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define MAX_NOME 100
#define MAX_DESCRICAO 200

struct Fabricante {
    char marca[MAX_NOME];
    char site[MAX_NOME];
    char telefone[MAX_NOME];
    char uf[3];
};

struct Produto {
    char descricao[MAX_DESCRICAO];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    int fabricanteIndex;
};

void cadastrarFabricantes(Fabricante fabricantes[], int* numFabricantes);
void cadastrarProdutos(Produto produtos[], Fabricante fabricantes[], int* numProdutos, int numFabricantes);
void listarMarcas(Fabricante fabricantes[], int numFabricantes);
void listarProdutos(Produto produtos[], Fabricante fabricantes[], int numProdutos);
void listarProdutosEstado(Produto produtos[], Fabricante fabricantes[], int numProdutos);
void listarProdutosMarca(Produto produtos[], Fabricante fabricantes[], int numProdutos);
void estadoProdutoMaisCaro(Produto produtos[], Fabricante fabricantes[], int numProdutos);
void fabricanteProdutoMaisBarato(Produto produtos[], Fabricante fabricantes[], int numProdutos);
void ordenarProdutosPorValor(Produto produtos[], int numProdutos);
void ordenarProdutosPorLucro(Produto produtos[], int numProdutos);
void ordenarProdutosPorPercentualLucro(Produto produtos[], int numProdutos);
void ordenarProdutosPorNome(Produto produtos[], int numProdutos);
void ordenarMarcasPorNomeDecrescente(Fabricante fabricantes[], int numFabricantes);

int le_valida_opcao() {
    int num;

    while (true) {
        if (scanf("%d", &num) == 1) {
            getchar(); 
            return num;
        }
        getchar(); 
        printf("Opcao invalida, Digite um numero inteiro valido.\n");
    }
}

void menu(Produto produtos[], Fabricante fabricantes[], int numProdutos, int numFabricantes) {
    int opcao;

    do {
        printf("\n===== Menu =====\n");
        printf("[1] Listar todas as marcas\n");
        printf("[2] Listar todos os produtos\n");
        printf("[3] Listar os produtos de um determinado estado\n");
        printf("[4] Listar os produtos de uma determinada marca\n");
        printf("[5] Apresentar os estados onde esta registrado o produto mais caro\n");
        printf("[6] Apresentar os fabricantes onde esta registrado o produto mais barato\n");
        printf("[7] Listar todos os produtos em ordem crescente de valor\n");
        printf("[8] Listar todos os produtos em ordem crescente de maior \"valor do lucro\"\n");
        printf("[9] Listar todos os produtos em ordem crescente de maior \"percentual de lucro\"\n");
        printf("[A] Listar todos os produtos em ordem alfabética crescente A-Z\n");
        printf("[Z] Listar todas as marcas em ordem alfabética decrescente Z-A\n");
        printf("[0] Sair do programa\n");

        opcao = le_valida_opcao();

        switch (opcao) {
            case 1:
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 2:
                listarProdutos(produtos, fabricantes, numProdutos);
                break;
            case 3:
                listarProdutosEstado(produtos, fabricantes, numProdutos);
                break;
            case 4:
                listarProdutosMarca(produtos, fabricantes, numProdutos);
                break;
            case 5:
                estadoProdutoMaisCaro(produtos, fabricantes, numProdutos);
                break;
            case 6:
                fabricanteProdutoMaisBarato(produtos, fabricantes, numProdutos);
                break;
            case 7:
                ordenarProdutosPorValor(produtos, numProdutos);
                listarProdutos(produtos, fabricantes, numProdutos);
                break;
            case 8:
                ordenarProdutosPorLucro(produtos, numProdutos);
                listarProdutos(produtos, fabricantes, numProdutos);
                break;
            case 9:
                ordenarProdutosPorPercentualLucro(produtos, numProdutos);
                listarProdutos(produtos, fabricantes, numProdutos);
                break;
            case 'A':
            case 'a':
                ordenarProdutosPorNome(produtos, numProdutos);
                listarProdutos(produtos, fabricantes, numProdutos);
                break;
            case 'Z':
            case 'z':
                ordenarMarcasPorNomeDecrescente(fabricantes, numFabricantes);
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida, Digite um numero valido.\n");
        }
    } while (opcao != 0);
}

void cadastrarFabricantes(Fabricante fabricantes[], int* numFabricantes) {
    if (*numFabricantes >= MAX_FABRICANTES) {
        printf("Limite de fabricantes atingido.\n");
        return;
    }

   Fabricante novoFabricante;

printf("===== Cadastro de Fabricantes =====\n");

printf("Marca: ");
fgets(novoFabricante.marca, MAX_NOME, stdin);

printf("Site: ");
fgets(novoFabricante.site, MAX_NOME, stdin);

printf("Telefone: ");
fgets(novoFabricante.telefone, MAX_NOME, stdin);

printf("UF: ");
fgets(novoFabricante.uf, 3, stdin);

fabricantes[*numFabricantes] = novoFabricante;
(*numFabricantes)++;

printf("Fabricante cadastrado com sucesso.\n");
}

void cadastrarProdutos(Produto produtos[], Fabricante fabricantes[], int* numProdutos, int numFabricantes) {
if (*numProdutos >= MAX_PRODUTOS) {
printf("Limite de produtos atingido.\n");
return;
}
Produto novoProduto;

printf("===== Cadastro de Produtos =====\n");

printf("Descricao: ");
fgets(novoProduto.descricao, MAX_DESCRICAO, stdin);

printf("Peso: ");
scanf("%f", &novoProduto.peso);

printf("Valor de Compra: ");
scanf("%f", &novoProduto.valorCompra);

printf("Valor de Venda: ");
scanf("%f", &novoProduto.valorVenda);

novoProduto.valorLucro = novoProduto.valorVenda - novoProduto.valorCompra;
novoProduto.percentualLucro = (novoProduto.valorLucro / novoProduto.valorCompra) * 100;

printf("Fabricantes Disponiveis:\n");
listarMarcas(fabricantes, numFabricantes);

printf("Indice do Fabricante: ");
int fabricanteIndex = le_valida_opcao();

if (fabricanteIndex >= 0 && fabricanteIndex < numFabricantes) {
    novoProduto.fabricanteIndex = fabricanteIndex;
    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;
    printf("Produto cadastrado com sucesso.\n");
} else {
    printf("Indice do fabricante invalido.\n");
}
}

void listarMarcas(Fabricante fabricantes[], int numFabricantes) {
printf("===== Marcas Disponiveis =====\n");
for (int i = 0; i < numFabricantes; i++) {
printf("[%d] %s\n", i, fabricantes[i].marca);
}
}

void listarProdutos(Produto produtos[], Fabricante fabricantes[], int numProdutos) {
printf("===== Produtos Cadastrados =====\n");
for (int i = 0; i < numProdutos; i++) {
Produto produto = produtos[i];
Fabricante fabricante = fabricantes[produto.fabricanteIndex];
printf("Descricao: %s", produto.descricao);
printf("Peso: %.2f\n", produto.peso);
printf("Valor de Compra: %.2f\n", produto.valorCompra);
printf("Valor de Venda: %.2f\n", produto.valorVenda);
printf("Valor do Lucro: %.2f\n", produto.valorLucro);
printf("Percentual de Lucro: %.2f%%\n", produto.percentualLucro);
printf("Fabricante: %s", fabricante.marca);
printf("==============================\n");
}
}

void listarProdutosEstado(Produto produtos[], Fabricante fabricantes[], int numProdutos) {
char uf[3];
printf("Digite o estado (UF): ");
fgets(uf, 3, stdin);
printf("===== Produtos do Estado %s =====\n", uf);
bool encontrou = false;

for (int i = 0; i < numProdutos; i++) {
    Produto produto = produtos[i];
    Fabricante fabricante = fabricantes[produto.fabricanteIndex];

    if (strcmp(fabricante.uf, uf) == 0) {
        encontrou = true;
        printf("Descricao: %s", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de Compra: %.2f\n", produto.valorCompra);
        printf("Valor de Venda: %.2f\n", produto.valorVenda);
        printf("Valor do Lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de Lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s", fabricante.marca);
        printf("==============================\n");
    }
}

if (!encontrou) {
    printf("Nenhum produto encontrado para o estado %s.\n", uf);
}
}

void listarProdutosMarca(Produto produtos[], Fabricante fabricantes[], int numProdutos) {
char marca[MAX_NOME];
printf("Digite a marca: ");
fgets(marca, MAX_NOME, stdin);
printf("===== Produtos da Marca %s =====\n", marca);
bool encontrou = false;

for (int i = 0; i < numProdutos; i++) {
    Produto produto = produtos[i];
    Fabricante fabricante = fabricantes[produto.fabricanteIndex];

    if (strcmp(fabricante.marca, marca) == 0) {
        encontrou = true;
        printf("Descricao: %s", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de Compra: %.2f\n", produto.valorCompra);
        printf("Valor de Venda: %.2f\n", produto.valorVenda);
        printf("Valor do Lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de Lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s", fabricante.marca);
        printf("==============================\n");
    }
}

if (!encontrou) {
    printf("Nenhum produto encontrado para a marca %s.\n", marca);
}
}

void estadoProdutoMaisCaro(Produto produtos[], Fabricante fabricantes[], int numProdutos) {
float maiorValor = 0;
char estadoMaisCaro[3];
bool encontrou = false;
for (int i = 0; i < numProdutos; i++) {
    Produto produto = produtos[i];
    Fabricante fabricante = fabricantes[produto.fabricanteIndex];

    if (produto.valorVenda > maiorValor) {
        maiorValor = produto.valorVenda;
        strcpy(estadoMaisCaro, fabricante.uf);
        encontrou = true;
    }
}

if (encontrou) {
    printf("O(s) estado(s) onde esta registrado o produto mais caro eh(sao): %s\n", estadoMaisCaro);
} else {
    printf("Nenhum produto cadastrado.\n");
}
}

void fabricanteProdutoMaisBarato(Produto produtos[], Fabricante fabricantes[], int numProdutos) {
float menorValor = produtos[0].valorVenda;
bool encontrou = false;
for (int i = 1; i < numProdutos; i++) {
    Produto produto = produtos[i];

    if (produto.valorVenda < menorValor) {
        menorValor = produto.valorVenda;
        encontrou = true;
    }
}

if (encontrou) {
    printf("O(s) fabricante(s) onde esta registrado o produto mais barato eh(sao):\n");

    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteIndex];

        if (produto.valorVenda == menorValor) {
            printf("Marca: %s", fabricante.marca);
        }
    }
} else {
    printf("Nenhum produto cadastrado.\n");
}
}

void ordenarProdutosPorValor(Produto produtos[], int numProdutos) {
for (int i = 0; i < numProdutos - 1; i++) {
for (int j = 0; j < numProdutos - i - 1; j++) {
if (produtos[j].valorVenda > produtos[j + 1].valorVenda) {
Produto temp = produtos[j];
produtos[j] = produtos[j + 1];
produtos[j + 1] = temp;
}
}
}
}

void ordenarProdutosPorLucro(Produto produtos[], int numProdutos) {
for (int i = 0; i < numProdutos - 1; i++) {
for (int j = 0; j < numProdutos - i - 1; j++) {
if (produtos[j].valorLucro > produtos[j + 1].valorLucro) {
Produto temp = produtos[j];
produtos[j] = produtos[j + 1];
produtos[j + 1] = temp;
}
}
}
}

void ordenarProdutosPorPercentualLucro(Produto produtos[], int numProdutos) {
for (int i = 0; i < numProdutos - 1; i++) {
for (int j = 0; j < numProdutos - i - 1; j++) {
if (produtos[j].percentualLucro > produtos[j + 1].percentualLucro) {
Produto temp = produtos[j];
produtos[j] = produtos[j + 1];
produtos[j + 1] = temp;
}
}
}
}

void ordenarProdutosPorNome(Produto produtos[], int numProdutos) {
    int i, j;
    Produto temp;

    for (i = 0; i < numProdutos - 1; i++) {
        for (j = 0; j < numProdutos - i - 1; j++) {
            if (strcmp(produtos[j].descricao, produtos[j + 1].descricao) > 0) {
                
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

void ordenarMarcasPorNomeDecrescente(Fabricante fabricantes[], int numFabricantes) {
    int i, j;
    Fabricante temp;

    for (i = 0; i < numFabricantes - 1; i++) {
        for (j = 0; j < numFabricantes - i - 1; j++) {
            if (strcmp(fabricantes[j].marca, fabricantes[j + 1].marca) < 0) {
               
                temp = fabricantes[j];
                fabricantes[j] = fabricantes[j + 1];
                fabricantes[j + 1] = temp;
            }
        }
    }
}

int main() {
Produto produtos[MAX_PRODUTOS];
Fabricante fabricantes[MAX_FABRICANTES];
int numProdutos = 0;
int numFabricantes = 0;
int opcao;

do {
    printf("\n===== Menu =====\n");
    printf("[1] Cadastrar Fabricantes\n");
    printf("[2] Cadastrar Produtos\n");
    printf("[3] Acessar Menu Principal\n");
    printf("[0] Sair do programa\n");

    opcao = le_valida_opcao();

    switch (opcao) {
        case 1:
            cadastrarFabricantes(fabricantes, &numFabricantes);
            break;
        case 2:
            cadastrarProdutos(produtos, fabricantes, &numProdutos, numFabricantes);
            break;
        case 3:
            menu(produtos, fabricantes, numProdutos, numFabricantes);
            break;
        case 0:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opcao invalida, Digite um numero valido.\n");
    }
} while (opcao != 0);

return 0;
}
