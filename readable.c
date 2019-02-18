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
#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXPATH 4096

/* 
 * Validate path for recursion
 * Check 1: File is a Directory
 * Check 2: File is not Symbolic
 * Check 3: Ensure path is not "." or ".."
 * If all checks passed return 1
 * Else return 0
 */
int dirTest(char *path)
{

    struct stat pathStat;

    if ((lstat(path, &pathStat) == 0) &&
        S_ISDIR(pathStat.st_mode) &&
        S_ISDIR(pathStat.st_mode) &&
        (strcmp(path, ".") != 0) && (strcmp(path, "..") != 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Check if file is regular using lstat and stMode.*/
int isReg(char *path)
{
    struct stat pathStat;

    if ((lstat(path, &pathStat) == 0) && S_ISDIR(pathStat.st_mode))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/* 
 * Recursive traversal of the directory path and all sub-directories
 * Print out absolute path of the readable & regular files and sub-directories
 */
void traverseDir(char *pathname)
{
    //Directory stream
    struct dirent *dp;

    //Change the working directory
    if (chdir(pathname) != 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }

    //Open path
    DIR *dir = opendir(pathname);

    //If not a directory countinue
    if (!dir)
    {
        return;
    }

    //Returns pointer to dirent structure, return null when end of directory reached
    while ((dp = readdir(dir)) != NULL)
    {
        //Check for Readable access permissions.
        if ((access(dp->d_name, R_OK)) == -1)
        {
            continue;
        }
        //If directory not open error out
        if (!dir)
        {
            fprintf(stderr, "Error: %s\n", strerror(errno));
        }

        //Get current working directory
        if (getcwd(pathname, MAXPATH) == NULL)
        {
            fprintf(stderr, "Error: %s\n", strerror(errno));
        }

        //If directory and Not symbolic continue traversal
        if (dirTest(dp->d_name) == 1)
        {
            traverseDir(strcat(strcat(pathname, "/"), dp->d_name));
        }
        //If regular file
        else if (isReg(dp->d_name))
        {
            //Print absolute path
            printf("%s/%s\n", pathname, dp->d_name);
        }
    }

    if (chdir("..") == -1)
    {
        fprintf(stderr, "chdir() Error: %s\n", strerror(errno));
    }

    //Close directory
    if (closedir(dir) != 0)
    {
        fprintf(stderr, "Error closing directory: %s\n", strerror(errno));
    }
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
        if (!(realpath((const char *)argv[1], rPath)))
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
