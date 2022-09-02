#include "linked_list.h"

#ifndef LIBRARY_H
#define LIBRARY_H
struct song_node **create_library();
void add_song(struct song_node **library, struct song_node *song);

struct song_node *search_song(struct song_node **library, char name[100], char artist[100]);
struct song_node *search_artist(struct song_node **library, char artist[100]);

void print_by_letter(struct song_node **library, char letter);
void print_by_artist(struct song_node **library, char artist[100]);
void print_library(struct song_node **library);
void shuffle(struct song_node **library);

void delete_song(struct song_node**library, struct song_node *song);
void clear_library(struct song_node **library);
#endif