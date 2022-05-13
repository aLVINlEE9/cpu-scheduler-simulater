#include "../../includes/cpu_scheduler.h"

void	*moniter(void *pcb_v)
{
	t_PCB	*pcb;
	t_PCB	*pcb_rec;
	t_process_table_node	*process_table_node;
	uint64_t	temp;
	int	i;

	pcb = (t_PCB *)pcb_v;
	process_table_node = pcb->data->process_table->head->next;
	while (1)
	{
		if (pcb->state == RUNNING)
		{
			i = -1;
			temp = pcb->burst_time - pcb->cost_time;
			pcb_rec = pcb;
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if ((process_table_node->pcb->state == READY || \
					process_table_node->pcb->state == WAITING) \
					&& process_table_node->pcb->burst_time - \
					process_table_node->pcb->cost_time < temp)
				{
					temp = process_table_node->pcb->burst_time - \
							process_table_node->pcb->cost_time;
					pcb_rec = process_table_node->pcb;
				}
				process_table_node = process_table_node->next;
			}
			if (pcb_rec != pcb)
			{
				pcb_rec->state == RUNNING;
				pcb->state == WAITING;
				pcb->data->done = pcb_rec->user_id;
				sem_wait(pcb->data->moniter_wait);
			}
		}
	}
	return ((void *)0);
}

void	waiting_state(t_data *data, t_PCB *pcb)
{
	sem_post(data->dispatcher);
	if (pcb->state == RUNNING)
		sem_post(data->moniter_wait);
	sem_wait(data->dispatcher);
}

void	SRTF_wait(t_data *data, t_PCB *pcb, int id)
{
	pcb->state = WAITING;
	while (1)
	{
		if (id == data->done)
		{
			sem_wait(data->wait);
			data->done == 0;
			break ;
		}
	}
	pcb->state = READY;
	sem_post(data->wait);
}

void	SRTF_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->state == WAITING)
			waiting_state(pcb->data, pcb);
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
	SRTF_wait(data, pcb, pcb->user_id);
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