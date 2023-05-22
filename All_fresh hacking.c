/* FORK.C */
#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

int main(void)

{

    pid_t pid;

    printf("Before fork:\n");

    printf("PID = %u, PPID = %u\n", getpid(), getppid());

    pid = fork();

    if (pid == -1)

        perror("fork() failure");

    if (pid == 0)

    {

        printf("Before sleep:\nPID = %u, PPID = %u\n", getpid(), getppid());

        sleep(10);

        printf("Child process:\n");

        printf("After sleep:\nPID = %u, PPID = %u\n", getpid(), getppid());

    }

    else

    {

        printf("Parent process exiting...\n");

    }

    return (0);

}

*/ PPID.C */

#include <stdio.h>

#include <unistd.h>

/**

 * main - PID

 *

 * Return: Always 0.

 */

int main(void)

{

    pid_t my_pid;

    my_pid = getppid();

    printf("%u\n", my_pid);

    return (0);

}

/* ENVIRON.C */ 

#define _GNU_SOURCE

#include <stdio.h>

#include <unistd.h>

/*

 * main - print the current environment

 *

 * Return: 0.

 */

int main(void)

{

	unsigned int i;

	for (i = 0; environ[i]; i++)

		puts(environ[i]);

	return (0);
} 

/* execve.c */

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

int

main(int argc, char *argv[])

{

    char *newargv[] = { NULL, "hello", "world", "program", NULL };

    char *newenviron[] = { NULL };

    if (argc != 2) {

        fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);

        exit(EXIT_FAILURE);

    }

    newargv[0] = argv[1];

    execve(argv[1], newargv, newenviron);

    perror("execve");   /* execve() returns only on error */

    exit(EXIT_FAILURE);

}
/* env_main.c */

#include <stdio.h>

/*

 * main - print the current environment

 * @ac: arg count

 * @av: arg vector

 * @env: pointer to environment

 *

 * Return: 0.

 */

int main(int ac __attribute__ ((unused)), char **av __attribute__ ((unused)), \

char **env)

{

	unsigned int i;

	for (i = 0; env[i]; i++)

		puts(env[i]);

	return (0);

}

/* wait.c */

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

/**

 * main - print nos. 1 - 5 and 6 - 10 in child and parent processes

 * respectively

 *

 * Return: 0.

 */

int main(void)

{

	int pid = fork();

	int n;

	if (pid < 0)

		perror("Error");

	if (pid == 0)

	{

		n = 1;

	}

	else

	{

		n = 6;

		wait(NULL);

	}

	for (int i = n; i < n + 5; i++)

	{

		printf(" %d", i);

		if (i == 10)

			putchar(10);

		fflush(stdout);

	}

	return (0);

}
/* simple_shell.c */

#define _GNU_SOURCE

#include <stdio.h>

#include <unistd.h>

/*

 * main - print the addresses of env and environ respectively

 * @ac: arg count

 * @av: arg vector

 * @env: pointer to environment

 *

 * Return: 0.

 */

int main(int ac __attribute__ ((unused)), char **av __attribute__ ((unused)), char **env)

{

	printf("&env: %p\n", &env);	printf("&environ: %p\n", &environ);

	return (0);

}

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

/**

 * main - print nos. 1 - 5 and 6 - 10 in child and parent processes

 * respectively

 *

 * Return: 0.

 */

int main(void)

{

	int pid = fork();

	int n;

	if (pid < 0)

		perror("Error");

	if (pid == 0)

	{

		n = 1;

	}

	else

	{

		n = 6;

		wait(NULL);

	}

	for (int i = n; i < n + 5; i++)

	{

		printf(" %d", i);

		if (i == 10)

			putchar(10);

		fflush(stdout);

	}

	return (0);

}

#include "main.h"

char *_getenv(const char *name)

{

	unsigned int i, idx;	char *buf;

	idx = strlen(name);

	buf = calloc(idx + 2, sizeof(char));

	if (!(buf))

		dprintf(2, "calloc() failure\n"), exit(-1);

	for (i = 0; environ[i]; i++)

	{

		if (!(strcpy(buf, name)))

		{

			free(buf);

			dprintf(2, "strcpy() failure\n"), exit(-1);

		}

		buf[idx] = '=';

		if (strncmp(buf, environ[i], strlen(buf)) == 0)

		{

			free(buf);

			return (environ[i] + idx + 1);

		}

	}

	free(buf);

	return (NULL);

}

#if 0

int main(int ac, char **av)

{

	int i = 0;

	char *val_string;

	if (ac < 2)

		dprintf(2, "Usage: %s name ...\n", av[i]), exit(-1);

	for (i = 1; av[i]; i++)

	{

		if ((val_string = _getenv(av[i])))

			puts(val_string);

		else

			dprintf(2, "%s: not found!\n", av[i]);

	}

	exit(0);

}

#endif
