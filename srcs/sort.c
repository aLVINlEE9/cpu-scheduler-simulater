#include "../includes/cpu_scheduler.h"

int	compare_burst(const void * a, const void * b)
{
	int	n1 = *(int *)a;
	int	n2 = *(int *)b;
	return (n2 - n1);
}

void	sort(t_data *data, t_process_table *process_table)
{
	int	i, j;
	int	*burst_time;
	t_process_table_node	*process_table_node;

	i = -1;
	burst_time = (int *)malloc(sizeof(int) * data->process_cores);
	process_table_node = process_table->head->next;
	while (++i < data->process_cores)
	{
		burst_time[i] = process_table_node->pcb->burst_time;
		process_table_node = process_table_node->next;
	}
	qsort(burst_time, sizeof(burst_time) / sizeof(int), sizeof(int), compare_burst);
	i = -1;
	j = -1;
	while (++i < data->process_cores)
	{
		process_table_node = process_table->head->next;
		while (++j < data->process_cores)
		{
			if (burst_time[i] == process_table_node->pcb->burst_time)
			{
				data->priority[process_table_node->pcb->user_id - 1] = i;
				process_table_node->pcb->priority = i;
				break ;
			}
			process_table_node = process_table_node->next;
		}
	}
}