// Desafio monitoria - PC
// Andressa Blaskoski Von Ahnt

#include"library.h"

int main(){
    FILE *file_1 = manipulate_file("cartas.txt", "r");
    FILE *file_2;

    node *list = create_list();
    read_file_and_make_list(list, file_1);

    int opcao;

    while(1){
        printf("\n-----MENU-----\n");
        printf("1. Imprimir colecao de cartas\n");
        printf("2. Adicionar carta na colecao\n");
        printf("3. Remover carta da colecao\n");
        printf("4. Salvar em arquivo.txt\n");
        printf("5. Salvar e Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
        case 1:
            print_list(list);
            break;
        
        case 2:
            insert(list, add_card());
            break;

        case 3:
            remove_card(list);
            break;

        case 4:
            file_2 = manipulate_file("precos.txt", "w");
            write_file(list, file_2);
            break;

        case 5:
            file_2 = manipulate_file("precos.txt", "w");
            write_file(list, file_2);

            if(clear_list(list) == NULL)
                printf("Lista limpa com sucesso!\n");
            else
                printf("Erro ao limpar a lista!\n");

            exit(1);
        }
    }
}