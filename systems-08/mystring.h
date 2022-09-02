#ifndef MYSTRING_H
#define MYSTRING_H
int mystrlen( char *s );
char *mystrncpy( char *dest, char *source, int n );
char *mystrcat( char *dest, char *source );
int mystrcmp( char *s1, char *s2 );
char *mystrchr( char *s, char c );
#endif