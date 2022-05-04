#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
# include <semaphore.h>

typedef struct s_info{
	uint64_t time;
	sem_t	*sem;
}	t_info;

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static int	child_process(char **envp, t_info *info)
{
	char *sem_adr;

	sem_wait(info->sem);
	char *argv[]   = { "/Users/alvinlee/Git_Folder/cpu-scheduler-simulater/exe", NULL, NULL};

	execve("/Users/alvinlee/Git_Folder/cpu-scheduler-simulater/exe", argv, envp);
	// if (get_time() - info->time > 400)
	// 	sem_post(info->sem);
	return (1);
}

int main(int argc, char **envp)
{
	pid_t pid;
	int	status;
	t_info info;
	int i = -1;

	sem_unlink("sem");
	info.sem = sem_open("sem", O_CREAT, 0600, 1);
	info.time = get_time();

	while (++i < 2)
	{
		pid = fork();
		if (pid == 0)
		{
			child_process(envp, &info);
		}
	}
	waitpid(pid, &status, 0);
}

