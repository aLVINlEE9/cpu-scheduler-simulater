#include "../../includes/cpu_scheduler.h"

void	*timequantum_moniter(void *pcb_v)
{
	t_PCB *pcb;
	uint64_t	priority;
	t_process_table_node	*process_table_node;
	int	i, j, flag_1;

	pcb = (t_PCB *)pcb_v;
	while (1)
	{
		sem_wait(pcb->data->moniter_wait);
		if (pcb->state == RUNNING)
		{
			if (pcb->cost_time / pcb->time_quantum > (uint64_t)pcb->repeated_times \
				&& pcb->cost_time % pcb->time_quantum <= 500)
			{
				pcb->repeated_times += 1;
				priority = -1;
				i = -1;
				flag_1 = 0;
				priority = pcb->data->priority[pcb->user_id];
				while (++i < pcb->data->process_cores)
				{
					j = -1;
					priority++;
					if (priority == (uint64_t)pcb->data->process_cores)
						priority = 0;
					process_table_node = pcb->data->process_table->head->next;
					while (++j < pcb->data->process_cores)
					{
						if (priority == pcb->data->priority[j] && \
							(process_table_node->pcb->state == WAITING || \
								process_table_node->pcb->state == READY))
						{
							flag_1 = 1;
							process_table_node->pcb->state = RUNNING;
							pcb->data->done = process_table_node->pcb->user_id;
							pcb->state = WAITING;
							break ;
						}
						process_table_node = process_table_node->next;
						usleep(10);
					}
					if (flag_1 == 1)
						break ;
				}
			}
		}
		else if (pcb->state != RUNNING && pcb->state != NEW && pcb->state != TERMINATED)
		{
			i = -1;
			flag_1 = 0;
			process_table_node = pcb->data->process_table->head->next;
			sem_wait(pcb->data->wait);
			if (pcb->data->terminated != -1 && pcb->data->terminated != pcb->data->last_terminated)
			{
				pcb->data->last_terminated = pcb->data->terminated;
				priority = -1;
				i = -1;
				priority = pcb->data->priority[pcb->data->terminated];
				while (++i < pcb->data->process_cores)
				{
					j = -1;
					priority++;
					if (priority == (uint64_t)pcb->data->process_cores)
						priority = 0;
					process_table_node = pcb->data->process_table->head->next;
					while (++j < pcb->data->process_cores)
					{
						if (priority == process_table_node->pcb->data->priority[j] && \
							(process_table_node->pcb->state == WAITING || \
								process_table_node->pcb->state == READY))
						{
							flag_1 = 1;
							process_table_node->pcb->state = RUNNING;
							pcb->data->done = process_table_node->pcb->user_id;
							break ;
						}
						process_table_node = process_table_node->next;
						usleep(10);
					}
					if (flag_1 == 1)
						break ;
				}
			}
			sem_post(pcb->data->wait);
		}
		sem_post(pcb->data->moniter_wait);	
	}
}

void	RR_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->state == WAITING)
		{
			pcb->wait_start = get_time();
			sem_post(pcb->data->moniter_wait);
			sem_post(pcb->data->dispatcher);
			waiting_zone(pcb->data, pcb->user_id);
			sem_wait(pcb->data->dispatcher);
			pcb->wait_start = get_time() - pcb->wait_start;
			pcb->waiting_time += pcb->wait_start;
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
	dispatcher(pcb);
	RR_running(pcb);
	termination(pcb);

	return (0);
}

int	RR(t_data *data)
{
	sort(data, data->process_table, "RR");
	start_process(data);
	return (0);
}