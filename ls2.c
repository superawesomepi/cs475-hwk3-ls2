#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"



// TODO: function definitions here for ls2

void printDir(const char *dirpath, int indent) {
    char filepath[128];
    DIR *p;
    struct dirent *d;
    struct stat fileInfo;
    p=opendir(dirpath);
    if(p == NULL) {
        printf("You requested a directory that isn't real, go away\n");
        return 0;
    }
    while(d=readdir(p)) {
        strcpy(filepath, dirpath);
        strcat(filepath, "/");
        strcat(filepath, d->d_name);
        lstat(filepath, &fileInfo);
        if (S_ISDIR(fileInfo.st_mode)) {
            if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0);
            else {
                for(int i = 0; i < indent; i++) {
                    printf("    ");
                }
                printf("%s%s",d->d_name, "/ (directory)\n");
                printDir(filepath, indent + 1);
            }
        } 
        else if (S_ISREG(fileInfo.st_mode)) {
            for(int i = 0; i < indent; i++) {
                printf("    ");
            }
            printf("%s (%d bytes)\n",d->d_name, fileInfo.st_size);
        }       
    }
}

int searchDir(const char *dirpath, int indent, const char *name, stack_t *s) {
    DIR *p;
    struct dirent *d;
    struct stat fileInfo;
    int corFile = 0;
    p=opendir(dirpath);
    while(d=readdir(p)) {
        char *filepath = (char*) malloc(128);    
        filepath[0] = '\0';  //empty the string
        strcpy(filepath, dirpath);
        strcat(filepath, "/");
        strcat(filepath, d->d_name);
        lstat(filepath, &fileInfo);
        if (S_ISDIR(fileInfo.st_mode)) {
            if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0);
            else {
                if(searchDir(filepath, indent + 1, name, s)) {
                    //printf("matching file found within directory %s\n", d->d_name);
                    char *filename = (char*) malloc(128);    
                    filename[0] = '\0';  //empty the string
                    for(int i = 0; i < indent; i++) {
                        snprintf(filename + strlen(filename), 128, "    ");
                    }
                    snprintf(filename + strlen(filename), 128, "%s%s",d->d_name, "/ (directory)");
                    push(s, filename);
                    corFile = 1;
                }
            }
        } 
        else if (S_ISREG(fileInfo.st_mode)) {
            if(!strcmp(d->d_name, name)) {
                char *filename = (char*) malloc(128);    
                filename[0] = '\0';  //empty the string
                for(int i = 0; i < indent; i++) {
                    snprintf(filename + strlen(filename), 128, "    ");
                }
                snprintf(filename + strlen(filename), 128, "%s (%d bytes)",d->d_name, fileInfo.st_size);
                push(s, filename);                               
                corFile = 1;
            }
        }    
        free(filepath);
    }
return corFile; 
}
