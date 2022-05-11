#include "../../includes/cpu_scheduler.h"

void	SJF_wait(t_data *data, t_PCB *pcb, int id)
{
	uint64_t	i;
	int flag;
	
	flag = 0;
	printf("%d %d\n", id, *done);
	sem_wait(data->stop);
	while (1)
	{
		i = 0;
		while (i < (uint64_t)data->process_cores)
		{
			if (data->priority[id - 1] == i && (uint64_t)*done >= i)
			{
				*done += 1;
				flag = 1;
				printf("%d\n", *done);
				sem_post(data->stop);
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
	}
	sem_wait(data->stop);
	pcb->state = READY;
	sem_post(data->stop);
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
	SJF_wait(pcb->data, pcb, pcb->user_id);
	dispatcher(pcb);
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