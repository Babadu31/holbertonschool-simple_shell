#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{

	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, stdin)) != -1) {
		printf("Réception d'une ligne de longueur %zu :\n", read);
		printf("%s", line);
	}
	if (line)
		free(line);

	exit(EXIT_SUCCESS);
}
