#include "../../includes/cpu_scheduler.h"

void	SJF_wait(t_data *data, t_PCB *pcb, int id)
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

void	SJF_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	SJF_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	SJF_wait(data, pcb, pcb->user_id);
	dispatcher(pcb);
	SJF_running(pcb);
	termination(pcb);
	return (0);
}

int	SJF(t_data *data)
{
	sort(data, data->process_table);
	// printf("%lld %lld %lld %lld\n", data->priority[0], data->priority[1], data->priority[2], data->priority[3]);
	start_process(data);
	return (0);
}
