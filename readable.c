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
#define ISFILE 4
#define ISDIR 8
#define ISSYMBOLIC 10

void traverseDir(char *entryPath)
{
    char path[MAXPATH]; 
    struct dirent *dp; 
    DIR *dir;

    dir = opendir(entryPath);
    if (dir == NULL)
    {
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s/%s\n", entryPath, dp->d_name);

            strcpy(path, entryPath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            traverseDir(path);
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

    //Traverse the path
    traverseDir(rPath);

    return 0;
}
