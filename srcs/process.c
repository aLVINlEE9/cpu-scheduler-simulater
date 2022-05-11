#include "../includes/cpu_scheduler.h"

void	init_process(t_process_table_node *process_table_node, int i)
{
	process_table_node->pid = getpid();
	process_table_node->pcb->pid = process_table_node->pid;
	process_table_node->pcb->user_id = i + 1;
	process_table_node->pcb->process_start = get_time();
}

void	release_resources(t_data *data)
{
	int	i;
	t_process_table_node	*process_table_node;

	i = -1;
	process_table_node = data->process_table->head->next;
	while (++i < data->process_cores)
	{
		kill(process_table_node->pid_k, SIGKILL);
		process_table_node = process_table_node->next;
	}
	sem_close(data->stop);
	sem_close(data->dispatcher);
	free(data->arriving_time);
	free(data->burst_time);
}

void	start_process(t_data *data)
{
	int	i;
	t_process_table_node	*process_table_node;

	i = -1;
	process_table_node = data->process_table->head->next;
	done = mmap(NULL, sizeof *done, PROT_READ | PROT_WRITE, 
					MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*done = 0;
	while (++i < data->process_table->count)
	{
		process_table_node->pid_k = fork();
		if (process_table_node->pid_k == 0)
		{
			init_process(process_table_node, i);
			data->algo_start(process_table_node);
			exit(0);
		}
		process_table_node = process_table_node->next;
	}
	i = -1;
	while (++i < data->process_table->count)
		wait(NULL);
}
