#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct node {
    int id;
    char name[20];
    struct node *next;
};
struct node *make_node(char n[20], int a, struct node *next_node);
void print_node(struct node *p);
void print_list(struct node *p);
struct node *insert_front(struct node *p, char n[20], int a);
struct node *remove_node(struct node *front, int id);
struct node *free_list(struct node* p);
#endif