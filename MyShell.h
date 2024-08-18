#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

extern char **environ;

void sighandler(int);
char *validator_getline(void);
int _memory(char *buff);
int _memory1(char *buff);
char **function_strtok(char *buff, int pointer);
void exit1(char *buffer, char **commands);
int env1(char *buff, char **commands);
char *_getenv(char *stri);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strstr(char *haystack, char *needle);
int _strcmp(char *s1, char *s2);
char *get_path(char *command);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *found_function(char **folder, char *command);
void function_fork(char *buffer, char **command, char **argv, int count);
char *_itoa(int number);
int *_perror(char *argv, char *str, char *command);


#endif
