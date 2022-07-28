#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - dddd
 * @argv: dsdd
 * @argc: dsdsd
 * @env: sdsd
 * Return: ddddd
 */

int main(int argc, char **argv, char **env)
{
size_t len;
char *buf;
char *token;
int status;
pid_t child;


while (getline(&buf, &len, stdin) != -1)
{
token = strtok(buf, "\n");

child = fork();
if (child == 0)
{
if (execve(token, argv, env) == -1)
perror("./simpleshell");
free(buf);
return (0);
}
else
wait(&status);
buf = NULL;
}
return (0);
}