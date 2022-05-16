#include "../../includes/cpu_scheduler.h"

void	*comp_moniter(void *pcb_v)
{
	t_PCB	*pcb;
	t_PCB	*pcb_rec;
	t_process_table_node	*process_table_node;
	uint64_t	temp;
	int	flag;
	int	i;

	pcb = (t_PCB *)pcb_v;
	process_table_node = pcb->data->process_table->head->next;
	while (1)
	{
		sem_wait(pcb->data->moniter_wait);
		if (pcb->state == RUNNING)
		{
			i = -1;
			pcb_rec = pcb;
			temp = pcb->burst_time - pcb->cost_time;
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if (pcb->user_id != i && (process_table_node->pcb->state == READY || \
					process_table_node->pcb->state == WAITING) \
					&& process_table_node->pcb->burst_time - \
					process_table_node->pcb->cost_time <= temp)
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
				pcb_rec->state = RUNNING;
				pcb->state = WAITING;
				pcb->data->done = pcb_rec->user_id;
			}
		}
		if (pcb->state != RUNNING && pcb->state != NEW)
		{
			i = -1;
			flag = 0;
			pcb_rec = pcb;
			temp = pcb->burst_time - pcb->cost_time;
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if (process_table_node->pcb->state != TERMINATED && process_table_node->pcb->state != NEW && process_table_node->pcb->burst_time - \
					process_table_node->pcb->cost_time <= temp)
				{
					temp = process_table_node->pcb->burst_time - \
							process_table_node->pcb->cost_time;
					pcb_rec = process_table_node->pcb;
					flag = 1;
				}
				process_table_node = process_table_node->next;
				usleep(10);
			}
			if (flag)
			{
				pcb_rec->state = RUNNING;
				if (pcb->state == READY)
					pcb->state = WAITING;
				pcb->data->done = pcb_rec->user_id;
			}
		}
		sem_post(pcb->data->moniter_wait);
	}
	return ((void *)0);
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

void	SRTF_wait(t_PCB *pcb)
{
	while (1)
	{
		if (pcb->state == RUNNING)
		{
			sem_post(pcb->data->moniter_wait);
			sem_wait(pcb->data->wait);
			break ;
		}
	}
}

void	SRTF_running(t_PCB *pcb)
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
		usleep(10);
	}
}

int	SRTF_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid1, NULL, comp_moniter, (void *)pcb);
	pthread_detach(pcb->tid1);
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	SRTF_wait(pcb);
	dispatcher(pcb);
	sem_post(pcb->data->wait);
	SRTF_running(pcb);
	termination(pcb);
	return (0);
}

int	SRTF(t_data *data)
{
	start_process(data);
	return (0);
}