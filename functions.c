#include"library.h"

FILE *manipulate_file(const char *name_file, const char *mode){
    FILE *file;
    if((file = fopen(name_file, mode)) == NULL) {
        printf("Arquivo indisponivel!\n");
        exit(1);
    }
    return file;
}

void read_file_and_make_list(node * list, FILE *file){
    card x;
    while (fscanf(file, "%d %d %d %s", &x.type, &x.power, &x.rarity, x.name) != EOF)
        insert(list, calculate_price(x));
    
    fclose(file);
}

node *allocate_node(){
    node *new_node;

	if((new_node = (node *) malloc(sizeof(node))) == NULL){
        printf("Nao foi possivel alocar a memoria");
        exit(1);
    }
    return new_node;
}

node *create_list(){
    node *start;
    start = allocate_node();
	start->next = NULL;
	return start;
}

void insert (node *list, card x){
    node *aux,*new = allocate_node();

    for (aux = list; aux->next != NULL; aux = aux->next);
    
    new->content = x;
    new->next = aux->next;
    aux->next = new;
}

card add_card(){
    card x;
    getchar();
    printf("Nome: ");
    if(fgets(x.name, 30, stdin) != NULL)
        x.name[strlen(x.name)-1] = '\0';

    strlwr(x.name);
    x.name[0]=toupper(x.name[0]);

    printf("Tipo: ");
    scanf("%d", &x.type);
    
    while (x.type < 0 || x.type >3){
        printf("O tipo deve ser entre 0 e 3. Digite novamente: ");
        scanf("%d", &x.type);
    }
    
    printf("Poder: ");
    scanf("%d", &x.power);
    
    printf("Raridade: ");
    scanf("%d", &x.rarity);

    while (x.rarity < 1 || x.rarity >5){
        printf("A raridade deve ser entre 1 e 5. Digite novamente: ");
        scanf("%d", &x.rarity);
    }

    return calculate_price(x);
}

void remove_card(node * list){
    char name[30];
    node *p, *q;
    p = list;
    q = list->next;

    getchar();
    printf("Digite o nome da carta que voce quer remover: ");
    if(fgets(name, 30, stdin) != NULL)
        name[strlen(name)-1] = '\0';

    strlwr(name);
    name[0] = toupper(name[0]);

    while ((q != NULL) && (strcmp(q->content.name, name))!= 0) {
		p = q;
		q = q->next;
	}

	if (q != NULL) {
		p->next = q->next;
		free(q);
        printf("Carta removida!\n");
	}else{
        printf("Nao foi possivel encontrar a carta!\n");
    }
}

void print_list(node * list){
	node *aux;
    int i=1;

	for(aux = list->next; aux!=NULL; aux = aux->next){
        printf("\n(%d) %s\nTipo: %d\nPoder: %d\nRaridade: %d\nPreco: R$%.2f\n", i, aux->content.name, aux->content.type, aux->content.power, aux->content.rarity, aux ->content.price);
        i++;
    }
    printf("\n");
}

void write_file(node * list, FILE *file){
	node *aux;
    int i=1;

	for(aux = list->next; aux!=NULL; aux = aux->next){
        fprintf(file, "\n(%d) %s\nTipo: %d\nPoder: %d\nRaridade: %d\nPreco: R$%.2f\n", i, aux->content.name, aux->content.type, aux->content.power, aux->content.rarity, aux ->content.price);
        i++;
    }

    fclose(file);
    printf("Precos.txt salvo!\n");
}

card calculate_price(card x){
    if(x.rarity <= 3)
        x.price = ((float)x.power/10)*(float)x.rarity;
    else if(x.rarity == 4)
            x.price = ((float)x.power/10)*((float)x.rarity*10);
        else
            x.price = ((float)x.power/2.5)*((float)x.rarity*10);
    
    return x;
}

node *clear_list(node * list){
    node *aux;

    while(list != NULL){
        aux = list;
        list = list->next;
        free(aux);
    }

    free(list);
    return NULL;
}