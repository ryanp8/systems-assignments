#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "library.h"
#include "linked_list.h"

struct song_node **create_library() {
    struct song_node **library = malloc(27 * sizeof(struct song_node*));
    int i; 
    for (i = 0; i < 27; i++) {
        library[i] = NULL;
    }
    return library;
}


char library_index(char artist[100]) {
    char first_letter = artist[0];
    if (first_letter < 97) {
        first_letter += 32;
    }

    if (first_letter >= 97 && first_letter <= 122) {
        return first_letter - 97;
    }
    return 26;
}


void add_song(struct song_node **library, struct song_node *song) {
    char index = library_index(song->artist);
    struct song_node *head = library[index];
    head = insert_in_order(head, song);

    library[index] = head;
}


struct song_node *search_song(struct song_node **library, char name[100], char artist[100]) {
    char index = library_index(artist);
    return find_node(library[index], artist, name);
}


struct song_node *search_artist(struct song_node **library, char artist[100]) {
    char index = library_index(artist);
    return find_artist(library[index], artist);
}


void print_by_letter(struct song_node **library, char letter) {
    if (letter < 97) {
        letter += 32;
    }

    if (letter >= 97 && letter <= 122) {
        letter -= 97;
    }
    struct song_node *head = library[letter];

    print_list(head);
}


void print_by_artist(struct song_node **library, char artist[100]) {
    printf("Printing [%s]: ", artist);
    struct song_node *head = search_artist(library, artist);
    printf("[ ");
    while (head && strcmp(head->artist, artist) == 0) {
        print_node(head);
        printf(" ");
        head++;
    }
    printf("]\n");
}


void print_library(struct song_node **library) {
    int i;
    for (i = 0; i < 27; i++) {
        if (library[i]) {
            printf("%c: ", i + 97);  
            print_list(library[i]);
        }
    }
    
}


void shuffle(struct song_node **library) {
    int i;
    for (i = 0; i < 27; i++) {
        int j;
        char num_songs = rand() % 100000 / 100000.0 * list_length(library[i]);
        for (j = 0; j < num_songs; j++) {
            struct song_node *random_song = get_random(library[i]);
            print_node(random_song);
            printf("\n");
        }
    }
    printf("\n");
}


void delete_song(struct song_node **library, struct song_node *song) {
    char index = library_index(song->artist);
    library[index] = remove_song(library[index], song->name, song->artist);
}


void clear_library(struct song_node **library) {
    int i;
    for (i = 0; i < 27; i++) {
        library[i] = free_list(library[i]);
    }
}





