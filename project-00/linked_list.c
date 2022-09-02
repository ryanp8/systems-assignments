#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linked_list.h"


int list_length(struct song_node *front) {
    int len = 0;
    while (front) {
        len++;
        front = front->next;
    }
    return len;
}


void print_node(struct song_node *node) {
    if (node) {
        printf("{ artist: %s, song: %s }", node->artist, node->name);
    }
}


void print_list(struct song_node *front) {
    printf("[ ");
    while (front) {
        print_node(front);
        printf(" ");
        front = front->next;
    }
    printf("]\n");
}


struct song_node *create_song_node(char new_name[100], char new_artist[100], struct song_node *next_node) {
    struct song_node *new = malloc(sizeof(struct song_node));
    strncpy(new->name, new_name, sizeof(new->name));
    strncpy(new->artist, new_artist, sizeof(new->artist));
    new->next = next_node;
    return new;
}


struct song_node *insert_front(struct song_node *front, char new_name[100], char new_artist[100]) {
    struct song_node *new = create_song_node(new_name, new_artist, front);
    return new;
}


struct song_node *insert_in_order(struct song_node *front, struct song_node *new) {
    if (front) {
        // printf("\ncurrent name: %s, new song name: %s, songcmp: %d", front->name, new->name, songcmp(new, front));
        if (songcmp(new, front) > 0) {
            front->next = insert_in_order(front->next, new);
            return front;
        }
        else {
            new->next = front;
            return new;
        }
    }

    return new;
}


struct song_node *find_artist(struct song_node *front, char target_artist[100]) {
    if (!front || strcmp(front->artist, target_artist) == 0) {
        return front;
    }
    return find_artist(front->next, target_artist);
}


struct song_node *find_node(struct song_node *front, char target_artist[100], char target_name[100]) {
    if (!front || (strcmp(front->artist, target_artist) == 0 && strcmp(front->name, target_name) == 0)) {
        return front;
    }
    return find_node(front->next, target_artist, target_name);
}


struct song_node *get_random(struct song_node *front) {
    int length = list_length(front);
    int song_number = (rand() % 100000 / 100000.0 * length);

    int i;
    for (i = 0; i < song_number; i++) {
        front = front->next;
    }   
    return front;
}


struct song_node *remove_song(struct song_node *front, char target_name[100], char target_artist[100]) {
    if (front) {
        if (strcmp(front->name, target_name) == 0 && strcmp(front->artist, target_artist) == 0) {
            struct song_node *tmp = front->next;
            printf("Removing [%s by %s]\n", front->name, front->artist);
            free(front);
            return tmp;
        }
        front->next = remove_song(front->next, target_name, target_artist);
    }
    return front;
}


struct song_node *free_list(struct song_node *front) {
    if (front) {
        struct song_node *tmp = front->next;
        printf("\tfreeing ");
        print_node(front);
        printf("\n");
        free(front);
        free_list(tmp);
    } 
    return NULL;
}


int lowercase_strcmp(char *s1, char *s2) {
    char *s1_heap = malloc(strlen(s1) + 1);
    char *s2_heap = malloc(strlen(s2) + 1);
    strcpy(s1_heap, s1);
    strcpy(s2_heap, s2);

    char *tmp = s1_heap;
    while (*tmp) {
        char current = *s1_heap;
        if (current >= 65 && current <= 90) {
            (*tmp) += 32;
        }
        tmp++;
    }

    tmp = s2_heap;
    while (*tmp) {
        char current = *s2_heap;
        if (current >= 65 && current <= 90) {
            (*tmp) += 32;
        }
        tmp++;
    }

    int res = strcmp(s1_heap, s2_heap);
    free(s1_heap);
    free(s2_heap);

    return res;
}



int songcmp(struct song_node *song1, struct song_node *song2) {
    int artistcmp = lowercase_strcmp(song1->artist, song2->artist);
    if (artistcmp == 0) {
        return lowercase_strcmp(song1->name, song2->name);
    }
    return artistcmp;
}


// int songcmp(char *s1, char *s2) {
//     int s1_total = 0;
//     int s2_total = 0;

//     while (*s1) {
//         char current = *s1;
//         if (current >= 65 && current <= 90) {
//             current += 32;
//         }
//         s1_total += current;
//         s1++;
//     }

//     while (*s2) {
//         char current = *s2;
//         if (current >= 65 && current <= 90) {
//             current += 32;
//         }
//         s2_total += current;
//         s2++;
//     }

//     return s1_total - s2_total;
// }
