#include "../../includes/cpu_scheduler.h"

void	*comp_moniter(void *pcb_v)
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
				printf("(%d) %lld < %lld\n", process_table_node->pcb->user_id, process_table_node->pcb->burst_time - \
						process_table_node->pcb->cost_time, temp);
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
				usleep(10);
			}
			if (pcb_rec != pcb)
			{
				sem_wait(pcb->data->moniter_wait);
				printf("fast %d\n", pcb_rec->user_id);
				pcb_rec->state = RUNNING;
				pcb->state = WAITING;
				pcb->data->done = pcb_rec->user_id;
			}
		}
	}
	return ((void *)0);
}

void	SRTF_wait(t_data *data, int id)
{
	while (1)
	{
		if (id == data->done)
		{
			sem_wait(data->wait);
			printf("wait rel%d\n", id);
			data->done = 0;
			break ;
		}
	}
	sem_post(data->wait);
}

void	SRTF_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->state == WAITING)
		{
			sem_post(pcb->data->dispatcher);
			SRTF_wait(pcb->data, pcb->user_id);
			sem_post(pcb->data->moniter_wait);
			sem_wait(pcb->data->dispatcher);
		}
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id - 1])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	SRTF_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid1, NULL, comp_moniter, (void *)pcb);
	pthread_detach(pcb->tid1);
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