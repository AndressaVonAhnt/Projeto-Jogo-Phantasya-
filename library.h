#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct{
    int type, power, rarity;
    float price;
    char name[30];
}card;

typedef struct node{
    card content;
    struct node *next;
}node;

node *allocate_node();
node *create_list();
void insert (node *list, card x);
void print_list(node * list);
FILE *manipulate_file(const char *name_file, const char *mode);
void read_file_and_make_list(node * list, FILE *file);
card add_card();
void remove_card(node * list);
card calculate_price(card x);
void write_file(node * list, FILE *file);
node *clear_list(node * list);