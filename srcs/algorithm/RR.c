#include "../../includes/cpu_scheduler.h"

void	*timequantum_moniter(void *pcb_v)
{
	t_PCB *pcb;

	pcb = (t_PCB *)pcb_v;
	while (1)
	{
		sem_wait(pcb->data->moniter_wait);
		if (pcb->state == RUNNING)
		{
			if (pcb->cost_time > pcb->time_quantum)
			{
				pcb->state = WAITING;
			}
		}
		sem_post(pcb->data->moniter_wait);
	}
}

void	waiting_zone(t_data *data, int id)
{
	while (1)
	{
		if (id == data->done)
		{
			data->done = -1;
			break ;
		}
	}
}

void	RR_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->state == WAITING)
		{
			sem_post(pcb->data->moniter_wait);
			sem_post(pcb->data->dispatcher);
			waiting_zone(pcb->data, pcb->user_id);
			sem_wait(pcb->data->dispatcher);
			pcb->running_start = get_time() - pcb->cost_time;
		}
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	RR_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid1, NULL, timequantum_moniter, (void *)pcb);
	pthread_detach(pcb->tid1);
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	RR_running(pcb);
	termination(pcb);

	return (0);
}

int	RR(t_data *data)
{
	start_process(data);
	return (0);
}