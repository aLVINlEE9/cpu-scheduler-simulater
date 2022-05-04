#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
	sem_t	*sem;

	sem = sem_open("sem", O_CREAT, 0600, 1);
	printf("start process\n");
	for (int i = 0; i < 10; i++)
	{
		sleep(1);
		printf("\t\t%d\n", i);
		if (i == 4)
			sem_post(sem);
	}
}