#include "../../includes/cpu_scheduler.h"

void	*moniter(void *pcb_v)
{
	t_PCB	*pcb;
	t_process_table_node	*process_table_node;
	int	i;

	pcb = (t_PCB *)pcb_v;
	process_table_node = pcb->data->process_table->head->next;
	while (1)
	{
		i = -1;
		if (pcb->state == RUNNING)
		{
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if (process_table_node->pcb->state = RUNNING && \
					process_table_node->pcb->burst_time - process_table_node->pcb->cost_time \
					< pcb->burst_time - pcb->cost_time)
				{
					
				}
				process_table_node = process_table_node->next;
			}
		}
	}
	return ((void *)0);
}

void	SRTF_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id - 1])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	SRTF_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid, NULL, moniter, (void *)pcb);
	pthread_detach(pcb->tid);
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	pcb->state = READY;
	dispatcher(pcb);
	SRTF_running(pcb);
	termination(pcb);
	return (0);
}

int	SRTF(t_data *data)
{
	start_process(data);
	return (0);
}