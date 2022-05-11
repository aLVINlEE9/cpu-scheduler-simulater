#include "../../includes/cpu_scheduler.h"

int	SJF_wait(t_data *data, int id)
{
	int	i;
	int flag;

	flag = 0;
	sem_wait(data->stop);
	while (1)
	{
		i = -1;
		while (++i < data->process_cores)
		{
			if (data->priority[id - 1] == i && data->done >= i)
			{
				data->done++;
				flag = 1;
				sem_post(data->stop);
				break ;
			}
		}
		if (flag == 1)
			break ;
	}
	
}

void	SJF_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id - 1])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	SJF_start(t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(pcb->data, pcb, pcb->process_start, pcb->user_id);
	if (SJF_wait(pcb->data, pcb->user_id))
	{
		sem_wait(pcb->data->stop);
		sem_post(pcb->data->stop);
		dispatcher(pcb);
	}
	SJF_running(pcb);
	termination(pcb);
	return (0);
}

int	SJF(t_data *data)
{
	sort(data, data->process_table);
	start_process(data);
	return (0);
}