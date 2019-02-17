/*
 *
 * ok.c
 * 
 * Assignment 3
 * CS 360
 * 
 * Author: JT Mundi
 * 
 * Date Created: 02/15/19
 * Last Modified: 02/15/19
 * 
 */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MAXPATH 4096
#define MAXNAME 255

void traverseDir(char *entryPath)
{
    DIR *dir;
    dir = opendir(entryPath);

    if (dir == NULL)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        struct dirent *entry;
        char *name;
        entry = readdir(dir);
        if (!entry)
            break;
        name = entry->d_name;

        //Skip Symbolic Links
        if (entry->d_type == 10)
        {
            continue;
        }
        if ((strcmp(name, ".") == 0) || (strcmp(name, "..") == 0))
            continue;

        if (entry->d_type == 8)
            printf("%s/%s\n", entryPath, name);
        else if (entry->d_type == 4)
        {
            printf("%s/%s/\n", entryPath, name);

            char *oldPath = strdup(entryPath);
            char *newPath = entryPath;
            strcat(newPath, "/");
            strcat(newPath, name);
            traverseDir(newPath);
            entryPath = oldPath;
        }
    }
    closedir(dir);
}

int main(int argc, char const *argv[])
{

    char rPath[MAXPATH];

    //Check for the correct amount of arguments
    if (argc > 2)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        fprintf(stderr, "Interface: ./readable <pathname>\n");
        exit(EXIT_FAILURE);
    }

    //If the user provides path
    if (argc == 2)
    {
        if (realpath((const char *)argv[1], rPath) == NULL)
        {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    //Path for the current working directory
    else
    {
        if (getcwd(rPath, MAXPATH) == NULL)
        {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    assert(rPath != NULL);

    traverseDir(rPath);

    return 0;
}
