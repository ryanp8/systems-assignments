#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystring.h"

int main() {

  char s1[100];
  char s2[100] = "hello";
  char s3[100] = "goodbye";
  
  printf("start strings:\n");
  printf("s1: [%s]\n", s1);
  printf("s2: [%s]\n", s2);
  printf("s3: [%s]\n", s3);
  
  printf("\nTesting strlen(s2):\n");
  printf("[standard]:\t%lu\n", strlen(s2) );
  printf("[mine]:\t\t%d\n", mystrlen(s2) );

//   printf("\nTesting strcpy(s1, s2):\n");
//   printf("[standard]:\t[%s]\n", strcpy(s1, s2) );
//   printf("[mine]:\t\t[%s]\n", mystrcpy(s1, s2) );

  printf("\nTesting strncpy(s1, s3, 3):\n");
  printf("[standard]:\t[%s]\n", strncpy(s1, s3, 3) );
  printf("[mine]:\t\t[%s]\n", mystrncpy(s1, s3, 3) );
  
  printf("\nTesting strcat(s1, s3):\n");
  printf("[standard]:\t[%s]\n", strcat(s1, s3) );
  s1[3] = 0;
  printf("[mine]:\t\t[%s]\n", mystrcat(s1, s3) );

//   printf("\nTesting strncat(s1, s2, 3):\n");
//   printf("[standard]:\t[%s]\n", strncat(s1, s2, 3) );
//   s1[12] = 0;
//   printf("[mine]:\t\t[%s]\n", mystrncat(s1, s2, 3) );

  printf("\nTesting strchr(s1, 'l'):\n");
  printf("[standard]:\t[%p]\n", strchr(s1, 'l') );
  printf("[mine]:\t\t[%p]\n", mystrchr(s1, 'l') );
  
  printf("\nTesting strchr(s1, 0):\n");
  printf("[standard]:\t[%p]\n", strchr(s1, 0) );
  printf("[mine]:\t\t[%p]\n", mystrchr(s1, 0) );

  printf("\nTesting strchr(s1, 'z'):\n");
  printf("[standard]:\t[%p]\n", strchr(s1, 'z') );
  printf("[mine]:\t\t[%p]\n", mystrchr(s1, 'z') );

  printf("\nTesting strcmp\n");
  printf("\tComparting ab to abc:\n");
  printf("\t\t[standard]:\t[%d]\n", strcmp("ab", "abc") );
  printf("\t\t[mine]:\t\t[%d]\n", mystrcmp("ab", "abc") );
  printf("\tComparting abc to ab:\n");
  printf("\t\t[standard]:\t[%d]\n", strcmp("abc", "ab") );
  printf("\t\t[mine]:\t\t[%d]\n", mystrcmp("abc", "ab") );
  printf("\tComparting abc to abc:\n");
  printf("\t\t[standard]:\t[%d]\n", strcmp("abc", "abc") );
  printf("\t\t[mine]:\t\t[%d]\n", mystrcmp("abc", "abc") );

  return 0;
}
  