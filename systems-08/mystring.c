#include <stdio.h>
#include "mystring.h"

int mystrlen( char *s ) {
    int len = 0;
    while (*s) {
        len++;
        s++;
    }
    return len;
}

char *mystrncpy( char *dest, char *source, int n ) {
    int i = 0;
    int source_length = 0;
    int j;
    while (source[j]) {
        source_length++;
        j++;
    }

    while(i < n) {
        if (i < source_length) {
            dest[i] = source[i];
        }
        else {
            dest[i] = '\0';
        }
        i++;
    }
    return dest;
}


char *mystrchr( char *s, char c ) {

    while (*s) {
        if (*s == c) {
            return s;
        }
        s++;
    } 
    if (c == 0) {
        return s;
    }

    return 0;
}

char *mystrcat( char *dest, char *source) { 
    int dest_pos = 0;

    while(dest[dest_pos]) {
        dest_pos++;
    }  
    int source_pos = 0;
    while(source[source_pos]) {
        dest[dest_pos] = source[source_pos];
        dest_pos++;
        source_pos++;
    }

    return dest;
}

int mystrcmp( char *s1, char *s2 ) {
    int s1_total = 0;
    int s2_total = 0;
    while (*s1) {
        s1_total += *s1;
        s1++;
    }
    while (*s2) {
        s2_total += *s2;
        s2++;
    }

    return s1_total - s2_total;
}

