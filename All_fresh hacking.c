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
