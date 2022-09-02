#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

struct node *make_node(char n[20], int a, struct node *next_node) {
    struct node *p = malloc(sizeof(struct node));
    strncpy(p->name, n, sizeof(p->name));
    p->id = a;
    p->next = next_node;
    return p;
}

void print_node(struct node *p) {
   printf("{ id: %d, name: %s }", p->id, p->name);
}

void print_list(struct node *p) {
    printf("[ ");
    while(p) {
        print_node(p);
        printf(" ");
        p = p->next;
    }
    printf(" ]\n");
}

struct node *insert_front(struct node *p, char n[20], int a) {
    struct node *new_node = make_node(n, a, p);
    return new_node;
}

struct node *remove_node(struct node *front, int id) { 
    
    if (front) {
        if (front->id == id) {
            struct node *temp = front->next;
            free(front);
            return temp;
        }
        front->next = remove_node(front->next, id);
    }

    return front;
}

struct node *free_list(struct node *p) {
    if (p->next) {
        free_list(p->next);
    }
    free(p);    
    return NULL;
}