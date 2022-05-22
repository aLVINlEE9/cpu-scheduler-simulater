#include "../../includes/cpu_scheduler.h"

void	PS_wait(t_data *data, t_PCB *pcb, int id)
{
	pcb->state = WAITING;
	while (1)
	{
		sem_wait(data->moniter_wait);
		if (data->priority[id] == (uint64_t)data->done)
		{
			data->done += 1;
			sem_wait(data->wait);
			break ;
		}
		sem_post(data->moniter_wait);
	}
	pcb->state = READY;
	sem_post(data->wait);
	sem_post(data->moniter_wait);
}

void	PS_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	PS_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	PS_wait(data, pcb, pcb->user_id);
	dispatcher(pcb);
	PS_running(pcb);
	termination(pcb);
	return (0);
}

int	PS(t_data *data)
{
	data->done = 0;
	start_process(data);
	return (0);
}