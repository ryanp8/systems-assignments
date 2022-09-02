#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct person {
    char name[20];
    int age;
};

void print_person(struct person *);
struct person * make_person(char n[20], int a);


int main() {

    srand(time(NULL));
    struct person *p = make_person("Ryan", rand() % 100);
    print_person(p);

    free(p);
    return 0;
}


struct person * make_person(char n[20], int a) {
    struct person *p = malloc(sizeof(struct person));
    int i;
    for (i = 0; i < 20; i++) {
        p->name[i] = n[i];
    }
    p->age = a;
    return p;
}


void print_person(struct person *p) {
    printf("name: %s\n", p->name);
    printf("age: %d\n", p->age);
}