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
