#include "../../includes/cpu_scheduler.h"

// 
void	*response_rate_moniter(void *pcb_v)
{
	t_PCB	*pcb, *pcb_rec;
	t_process_table_node	*process_table_node;
	uint64_t	response_rate, temp;
	int	i;

	pcb = (t_PCB *)pcb_v;
	while (1)
	{
		sem_wait(pcb->data->moniter_wait);
		if (pcb->state == WAITING)
		{
			i = -1;
			temp = 0;
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if (process_table_node->pcb->state != WAITING)
					continue ;
				else
				{
					response_rate = ((get_time() - process_table_node->pcb->readyque_arrived_time) \
									+ process_table_node->pcb->burst_time) / process_table_node->pcb->burst_time;
					if (response_rate >= temp)
					{
						temp = response_rate;
						pcb_rec = process_table_node->pcb;
					}
				}
				process_table_node = process_table_node->next;
			}
		}
		sem_post(pcb->data->moniter_wait);
	}
}

void	HRN_wait(t_data *data, t_PCB *pcb, int id)
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

void	HRN_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	HRN_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid1, NULL, response_rate_moniter, (void *)pcb);
	pthread_detach(pcb->tid1);
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	HRN_wait(data, pcb, pcb->user_id);
	dispatcher(pcb);
	HRN_running(pcb);
	termination(pcb);
	return (0);
}

int HRN(t_data *data)
{
	start_process(data);
	return (0);
}