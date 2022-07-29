#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - dddd
 * @argv: dsdd
 * @argc: dsqdd
 * @env: sdsd
 * Return: ffd
 */

int main(int argc, char **argv, char **env)
{
size_t len = 0;
char *buf = 0;
char *token = 0;
int status = 0;
pid_t child = 0;


while (getline(&buf, &len, stdin) != -1)
{
(void)argc;
token = strtok(buf, "\n");

child = fork();

if (child == 0)
{
if (execve(token, argv, env) == -1)
perror("./simpleshell");
return (0);
}
else
wait(&status);
buf = NULL;
}
free(buf);
return (0);
}
