#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

void limparBuffer();
void removerQuebraLinha(char *str);
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        printf("\n=== INVENTARIO DE SOBREVIVENCIA ===\n");
        printf("Slots Ocupados: %d/%d\n", totalItens, MAX_ITENS);
        printf("1. Coletar Item (Inserir)\n");
        printf("2. Descartar Item (Remover)\n");
        printf("3. Abrir Mochila (Listar)\n");
        printf("4. Procurar Item (Buscar)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n[!] A mochila esta cheia! Descarte algo antes.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Novo Item ---\n");
    printf("Nome (ex: Erva Verde): ");
    fgets(novoItem.nome, TAM_NOME, stdin);
    removerQuebraLinha(novoItem.nome);

    printf("Tipo (ex: Cura, Municao): ");
    fgets(novoItem.tipo, TAM_TIPO, stdin);
    removerQuebraLinha(novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("[+] Item adicionado ao slot %d.\n", totalItens);
}

void listarItens() {
    if (totalItens == 0) {
        printf("\n[i] A mochila esta vazia.\n");
        return;
    }

    printf("\n--- Conteudo da Mochila ---\n");
    printf("%-5s %-20s %-15s %-10s\n", "Slot", "Nome", "Tipo", "Qtd");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("#%-4d %-20s %-15s %-10d\n", 
            i + 1, 
            mochila[i].nome, 
            mochila[i].tipo, 
            mochila[i].quantidade
        );
    }
}

void buscarItem() {
    char nomeBusca[TAM_NOME];
    int encontrado = 0;

    printf("\nQual item deseja procurar? ");
    fgets(nomeBusca, TAM_NOME, stdin);
    removerQuebraLinha(nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[!] ITEM ENCONTRADO NO SLOT %d:\n", i + 1);
            printf("Nome: %s | Tipo: %s | Qtd: %d\n", 
                mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("\n[x] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

void removerItem() {
    char nomeRemover[TAM_NOME];
    int indiceRemover = -1;

    if (totalItens == 0) {
        printf("\n[i] Nada para remover.\n");
        return;
    }

    listarItens(); 
    printf("\nDigite o nome do item para descartar: ");
    fgets(nomeRemover, TAM_NOME, stdin);
    removerQuebraLinha(nomeRemover);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indiceRemover = i;
            break; 
        }
    }

    if (indiceRemover != -1) {
        for (int i = indiceRemover; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        totalItens--; 
        printf("[-] Item descartado com sucesso.\n");
    } else {
        printf("[x] Item nao encontrado.\n");
    }
}