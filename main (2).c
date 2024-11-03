#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fruta {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

Fruta* listaFrutas[100];
int totalFrutas = 0;

void cadastrarFruta() {
    if (totalFrutas >= 100) {
        printf("Limite de frutas atingido!\n");
        return;
    }

    Fruta* novaFruta = (Fruta*)malloc(sizeof(Fruta));
    
    printf("Código da fruta: ");
    scanf("%d", &novaFruta->codigo);
    
    
    for (int i = 0; i < totalFrutas; i++) {
        if (listaFrutas[i]->codigo == novaFruta->codigo) {
            printf("Código já cadastrado!\n");
            free(novaFruta);
            return;
        }
    }

    printf("Nome da fruta: ");
    scanf("%s", novaFruta->nome);
    printf("Quantidade: ");
    scanf("%d", &novaFruta->quantidade);
    printf("Preço: ");
    scanf("%f", &novaFruta->preco);

    listaFrutas[totalFrutas++] = novaFruta;
    printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas() {
    if (totalFrutas == 0) {
        printf("Nenhuma fruta cadastrada!\n");
        return;
    }
    printf("Frutas cadastradas:\n");
    for (int i = 0; i < totalFrutas; i++) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
            listaFrutas[i]->codigo, listaFrutas[i]->nome, listaFrutas[i]->quantidade, listaFrutas[i]->preco);
    }
}

void buscarFruta() {
    int codigo;
    printf("Digite o código da fruta: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalFrutas; i++) {
        if (listaFrutas[i]->codigo == codigo) {
            printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
                listaFrutas[i]->codigo, listaFrutas[i]->nome, listaFrutas[i]->quantidade, listaFrutas[i]->preco);
            return;
        }
    }
    printf("Fruta não encontrada!\n");
}

void alterarFruta() {
    int codigo;
    printf("Digite o código da fruta que deseja alterar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalFrutas; i++) {
        if (listaFrutas[i]->codigo == codigo) {
            printf("Novo nome da fruta: ");
            scanf("%s", listaFrutas[i]->nome);
            printf("Nova quantidade: ");
            scanf("%d", &listaFrutas[i]->quantidade);
            printf("Novo preço: ");
            scanf("%f", &listaFrutas[i]->preco);
            printf("Fruta alterada com sucesso!\n");
            return;
        }
    }
    printf("Fruta não encontrada!\n");
}

void excluirFruta() {
    int codigo;
    printf("Digite o código da fruta que deseja excluir: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalFrutas; i++) {
        if (listaFrutas[i]->codigo == codigo) {
            if (listaFrutas[i]->quantidade > 0) {
                printf("Não é possível excluir, ainda há estoque!\n");
                return;
            }
            free(listaFrutas[i]);
            for (int j = i; j < totalFrutas - 1; j++) {
                listaFrutas[j] = listaFrutas[j + 1];
            }
            totalFrutas--;
            printf("Fruta excluída com sucesso!\n");
            return;
        }
    }
    printf("Fruta não encontrada!\n");
}

void venderFruta() {
    int codigo, quantidade;
    printf("Digite o código da fruta que deseja vender: ");
    scanf("%d", &codigo);
    printf("Quantidade a vender: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < totalFrutas; i++) {
        if (listaFrutas[i]->codigo == codigo) {
            if (listaFrutas[i]->quantidade >= quantidade) {
                listaFrutas[i]->quantidade -= quantidade;

                
                FILE *file = fopen("vendas.txt", "a");
                if (file) {
                    fprintf(file, "Código: %d, Quantidade: %d, Total: %.2f\n",
                            listaFrutas[i]->codigo, quantidade, listaFrutas[i]->preco * quantidade);
                    fclose(file);
                }

                printf("Venda realizada com sucesso!\n");
                return;
            } else {
                printf("Quantidade em estoque insuficiente!\n");
                return;
            }
        }
    }
    printf("Fruta não encontrada!\n");
}

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Fruta\n");
        printf("2. Listar Frutas\n");
        printf("3. Buscar Fruta\n");
        printf("4. Alterar Fruta\n");
        printf("5. Excluir Fruta\n");
        printf("6. Vender Fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFruta(); break;
            case 2: listarFrutas(); break;
            case 3: buscarFruta(); break;
            case 4: alterarFruta(); break;
            case 5: excluirFruta(); break;
            case 6: venderFruta(); break;
            case 7: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (opcao != 7);
}

int main() {
    menu();
    // Liberar memória antes de sair
    for (int i = 0; i < totalFrutas; i++) {
        free(listaFrutas[i]);
    }
    return 0;
}
