#include "../../includes/cpu_scheduler.h"

void	SJF_wait(t_data *data, t_PCB *pcb, int id)
{
	pcb->state = WAITING;
	while (1)
	{
		if (data->priority[id - 1] == (uint64_t)data->done)
		{
			data->done += 1;
			sem_wait(data->wait);
			break ;
		}
	}
	pcb->state = READY;
	sem_post(data->wait);
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

int	SJF_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	pcb->state = READY;
	SJF_wait(data, pcb, pcb->user_id);
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
