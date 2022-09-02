#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linked_list.h"
#include "library.h"



int main() {

    srand(time(NULL));

    struct song_node *head = NULL;
    head = insert_in_order(head, create_song_node("Perfect", "Ed Sheeran", NULL));
    head = insert_in_order(head, create_song_node("Beautiful People", "Ed Sheeran", NULL));
    head = insert_in_order(head, create_song_node("Photograph", "Ed Sheeran", NULL));
    head = insert_in_order(head, create_song_node("Castle on the Hill", "Ed Sheeran", NULL));
    head = insert_in_order(head, create_song_node("Yellow", "Coldplay", NULL));
    head = insert_in_order(head, create_song_node("good 4 u", "Olivia Rodrigo", NULL));
    head = insert_in_order(head, create_song_node("We Are Young", "Fun", NULL));
    head = insert_in_order(head, create_song_node("Some Nights", "Fun", NULL));
    head = insert_in_order(head, create_song_node("Style", "Taylor Swift", NULL));
    head = insert_in_order(head, create_song_node("Shake if Off", "Taylor Swift", NULL));
    head = insert_in_order(head, create_song_node("22", "Taylor Swift", NULL));
    head = insert_in_order(head, create_song_node("Summer", "Calvin Harris", NULL));


    printf("LINKED LIST TESTS\n");
    printf("===============================\n\n");

    printf("Testing print_list\n");
    print_list(head);

    printf("===============================\n\n");
    printf("Testing print_node: ");
    print_node(head);
    printf("\n");

    printf("===============================\n\n");
    printf("Testing find_node:\n");
    printf("Looking for [Perfect by Ed Sheeran]: ");
    print_node(find_node(head, "Ed Sheeran", "Perfect"));
    printf("\n");

    printf("Looking for [Style by Taylor Swift]: ");
    print_node(find_node(head, "Taylor Swift", "Style"));
    printf("\n");

    printf("===============================\n\n");
    printf("Testing find_artist:\n");
    printf("Looking for Coldplay: ");
    print_node(find_artist(head, "Coldplay"));

    printf("\nLooking for Fun: ");
    print_node(find_artist(head, "Fun"));
    printf("\n");

    printf("===============================\n\n");
    printf("Testing songcmp:\n");
    struct song_node *song1 = create_song_node("Perfect", "Ed Sheeran", NULL);
    struct song_node *song2 = create_song_node("Perfect", "Ed Sheeran", NULL);
    
    printf("Comparing [Perfect by Ed Sheeran] to [Perfect by Ed Sheeran]\n");
    printf("\t%d\n", songcmp(song1, song2));

    printf("Comparing [Perfect by Ed Sheeran] to [Photograph by Ed Sheeran]\n");
    strncpy(song2->name, "Photograph", sizeof(song2->name));
    printf("\t%d\n", songcmp(song1, song2));

    printf("Comparing [good 4 u by Olivia Rodrigo] to [Yellow by Coldplay]\n");
    strncpy(song1->name, "good 4 u", sizeof(song1->name));
    strncpy(song2->name, "Yellow", sizeof(song2->name));
    strncpy(song1->artist, "Olivia Rodrigo", sizeof(song1->artist));
    strncpy(song2->artist, "Coldplay", sizeof(song2->artist));

    printf("\t%d\n", songcmp(song1, song2));

    printf("===============================\n\n");
    printf("Testing random:\n");
    print_node(get_random(head));
    printf("\n");
    print_node(get_random(head));
    printf("\n");
    print_node(get_random(head));
    printf("\n");

    printf("===============================\n\n");
    printf("Testing remove:\n");
    head = remove_song(head, "Photograph", "Ed Sheeran");
    print_list(head);

    head = remove_song(head, "We Are Young", "Fun");
    print_list(head);

    printf("===============================\n\n");
    printf("Testing free_list:\n");
    head = free_list(head);
    printf("List after freeing: ");
    print_list(head);

    printf("===============================\n\n");
    printf("Testing insert_front: \n");
    head = insert_front(head,"Perfect", "Ed Sheeran");
    head = insert_front(head,"Beautiful People", "Ed Sheeran");
    head = insert_front(head,"Photograph", "Ed Sheeran");
    head = insert_front(head,"Castle on the Hill", "Ed Sheeran");
    head = insert_front(head,"Yellow", "Coldplay");
    head = insert_front(head,"good 4 u", "Olivia Rodrigo");
    head = insert_front(head,"We Are Young", "Fun");
    head = insert_front(head,"Some Nights", "Fun");
    head = insert_front(head,"Style", "Taylor Swift");
    head = insert_front(head,"Shake if Off", "Taylor Swift");
    head = insert_front(head,"22", "Taylor Swift");
    head = insert_front(head,"Summer", "Calvin Harris");
    print_list(head);

    printf("===============================\n\n");
    printf("MUSIC LIBRARY TESTS\n");
    struct song_node **library = create_library();

    printf("===============================\n\n");
    printf("Testing print_by_letter:\n");
    print_by_letter(library, 't');

    printf("===============================\n\n");
    printf("Testing print_library:\n");
    print_library(library);

    add_song(library, create_song_node("Perfect", "Ed Sheeran", NULL));
    add_song(library, create_song_node("Beautiful People", "Ed Sheeran", NULL));
    add_song(library, create_song_node("Photograph", "Ed Sheeran", NULL));
    add_song(library, create_song_node("Castle on the Hill", "Ed Sheeran", NULL));
    add_song(library, create_song_node("We Are Young", "Fun", NULL));
    add_song(library, create_song_node("Some Nights", "Fun", NULL));
    add_song(library, create_song_node("good 4 u", "Olivia Rodrigo", NULL));
    add_song(library, create_song_node("Yellow", "Coldplay", NULL));
    add_song(library, create_song_node("Style", "Taylor Swift", NULL));
    add_song(library, create_song_node("Shake it Off", "Taylor Swift", NULL));
    add_song(library, create_song_node("22", "Taylor Swift", NULL));
    add_song(library, create_song_node("Summer", "Calvin Harris", NULL));


    printf("===============================\n\n");
    printf("Testing print_by_letter:\n");
    print_by_letter(library, 'e');
    print_by_letter(library, 't');

    printf("===============================\n\n");
    printf("Testing print_library:\n");
    print_library(library);

    printf("===============================\n\n");
    printf("Testing print_by_artist:\n");
    printf("Expect empty: ");
    print_by_artist(library, "Bruno Mars");
    print_by_artist(library, "Calvin Harris");

    printf("===============================\n\n");
    printf("Testing search_song:\n");

    struct song_node *result = search_song(library, "Perfect", "Ed Sheeran");
    printf("Searching for [Perfect by Ed Sheeran]: ");
    print_node(result);
    printf("\n");

    result = search_song(library, "Style", "Taylor Swift");
    printf("Searching for [Style by Taylor Swift]: ");
    print_node(result);
    printf("\n");

    printf("===============================\n\n");
    printf("Testing search_artist:\n");
    printf("Looking for Ed Sheeran: ");
    result = search_artist(library, "Ed Sheeran");
    print_list(result);

    printf("Looking for Fun: ");
    result = search_artist(library, "Fun");
    print_list(result);

    printf("Looking for Coldplay: ");
    result = search_artist(library, "Coldplay");
    print_list(result);

    printf("===============================\n\n");
    printf("Testing shuffle:\n");
    shuffle(library);

    printf("===============================\n\n");
    printf("Testing delete_song:\n");
    struct song_node *to_delete = create_song_node("22", "Taylor Swift", NULL);
    delete_song(library, to_delete);
    print_library(library);

    printf("===============================\n\n");
    printf("Testing clear_library:\n");
    clear_library(library);
    printf("Library after clear:\n");
    print_library(library);

    printf("===============================\n\n");
    printf("Adding songs to empty library:\n");
    add_song(library, create_song_node("Hot N Cold", "Katy Perry", NULL));
    add_song(library, create_song_node("Uptown Funk", "Bruno Mars", NULL));
    print_library(library);
    
    printf("\n");
    return 0;
}