#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


int main() {

    struct node *head = NULL;
    
    head = insert_front(head, "Chandler", 0);
    head = insert_front(head, "Joey", 1);
    head = insert_front(head, "Monica", 2);
    head = insert_front(head, "Ross", 3);
    head = insert_front(head, "Rachel", 4);
    head = insert_front(head, "Phoebe", 5);

    printf("List:\n");
    print_list(head);
    printf("\n");

    head = remove_node(head, 3);
    printf("List with id 3 removed:\n");
    print_list(head);
    printf("\n");


    head = remove_node(head, 5);
    printf("List with id 5 removed:\n");
    print_list(head);
    printf("\n");

    head = remove_node(head, 27);
    printf("List with id 27 removed:\n");
    print_list(head);
    printf("\n");


    head = free_list(head);
    printf("List after freeing:\n");
    print_list(head);


    return 0;
}