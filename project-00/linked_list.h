#ifndef LINKED_LIST_H
#define LINKED_LIST_H
struct song_node {
    char name[100];
    char artist[100];
    struct song_node *next;
};
int list_length(struct song_node *head);
void print_list(struct song_node *front);
void print_node(struct song_node *node);

struct song_node *create_song_node(char new_name[100], char new_artist[100], struct song_node *next_node);
struct song_node *insert_front(struct song_node *front, char new_name[100], char new_artist[100]);
struct song_node *insert_in_order(struct song_node *front, struct song_node *new);
int songcmp(struct song_node *song1, struct song_node *song2);

struct song_node *find_artist(struct song_node *front, char target_artist[100]);
struct song_node *find_node(struct song_node *front, char target_artist[100], char target_name[100]);
struct song_node *get_random(struct song_node *front);

struct song_node *remove_song(struct song_node *front, char target_name[100], char target_artist[100]);
struct song_node *free_list(struct song_node *front);
#endif