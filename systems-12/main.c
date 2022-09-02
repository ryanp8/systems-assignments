#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char path[100];

    if (argc > 1) {
        strcpy(path, argv[1]);
    }
    else {
        printf("Enter the directory:\n");
        int res = read(STDIN_FILENO, path, sizeof(path));
        if (res == -1) {
            printf("Error %d: %s", errno, strerror(errno));
        }
        int path_len = strlen(path);
        path[path_len - 1] = '\0';
    }

    DIR *d;
    d = opendir(path);
    if (!d) {
        printf("Error %d: %s\n", errno, strerror(errno));
        return -1;
    }

    struct dirent *entry = readdir(d);
    struct stat sb;
    unsigned long long size = 0;

    while(entry) {
        stat(entry->d_name, &sb);
        size += sb.st_size;
        entry = readdir(d);
    }
    printf("Statistics for directory: .\n");
    printf("Total Directory Size: %llu Bytes\n", size);

    rewinddir(d);
    entry = readdir(d);

    printf("Directories:\n");
    while (entry) {
        if (entry->d_type == 4) {
            stat(entry->d_name, &sb);
            size += sb.st_size;
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    rewinddir(d);
    entry = readdir(d);

    printf("Regular files:\n");
    while (entry) {
        if (entry->d_type == 8) {
            stat(entry->d_name, &sb);
            size += sb.st_size;
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    return 0;
}