#include "../includes/cpu_scheduler.h"

int	compare(const void * a, const void * b)
{
	int	n1 = *(int *)a;
	int	n2 = *(int *)b;
	return (n2 - n1);
}

void	sort(t_data *data, t_process_table *process_table, char *flag)
{
	int	i, j;
	t_process_table_node	*process_table_node;

	if (strcmp(flag, "SJF") == 0)
	{
		uint64_t	*burst_time;
		i = -1;
		burst_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		process_table_node = process_table->head->next;
		while (++i < data->process_cores)
		{
			burst_time[i] = process_table_node->pcb->burst_time;
			process_table_node = process_table_node->next;
		}
		qsort(burst_time, data->process_cores, sizeof(uint64_t), compare);
		i = -1;
		while (++i < data->process_cores)
		{
			process_table_node = process_table->head->next;
			j = -1;
			while (++j < data->process_cores)
			{
				if (burst_time[i] == process_table_node->pcb->burst_time)
				{
					data->priority[j] = data->process_cores - i - 1;
					process_table_node->pcb->priority = i;
					break ;
				}
				process_table_node = process_table_node->next;
			}
		}
	}
	else if (strcmp(flag, "RR") == 0)
	{
		uint64_t	*arriving_time;
		i = -1;
		arriving_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		process_table_node = process_table->head->next;
		while (++i < data->process_cores)
		{
			arriving_time[i] = process_table_node->pcb->arriving_time;
			process_table_node = process_table_node->next;
		}
		qsort(arriving_time, data->process_cores, sizeof(uint64_t), compare);
		i = -1;
		while (++i < data->process_cores)
		{
			process_table_node = process_table->head->next;
			j = -1;
			while (++j < data->process_cores)
			{
				if (arriving_time[i] == process_table_node->pcb->arriving_time)
				{
					data->priority[j] = data->process_cores - i - 1;
					process_table_node->pcb->priority = data->process_cores - i - 1;
					break ;
				}
				process_table_node = process_table_node->next;
			}
		}
	}
}