#include "../includes/cpu_scheduler.h"

void	init_process(t_process_table_node *process_table_node, int i)
{
	process_table_node->pid = getpid();
	process_table_node->pcb->pid = process_table_node->pid;
	process_table_node->pcb->user_id = i + 1;
	process_table_node->pcb->state = READY;
	process_table_node->pcb->process_start = get_time();
}

void	start_process(t_data *data)
{
	int	i;
	pid_t	pid;
	t_process_table_node	*process_table_node;

	i = -1;
	process_table_node = data->process_table->head->next;
	while (++i < data->process_table->count)
	{
		pid = fork();
		if (pid == 0)
		{
			init_process(process_table_node, i);
			data->algo_start(process_table_node);
			exit(0);
		}
		process_table_node = process_table_node->next;
	}
}