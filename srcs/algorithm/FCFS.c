#include "../../includes/cpu_scheduler.h"

void	update_cost_time(t_PCB *pcb)
{
	pcb->cost_time = get_time() - pcb->running_start;
	usleep(50);
}

void	FCFS_running(t_PCB *pcb)
{
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id - 1])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->waiting_time = pcb->running_start - pcb->readyque_arrived_time;
	pcb->turnaround_time = pcb->waiting_time + pcb->cost_time;
	printf("PROCESS: %d\t\tPID: %d\t\tTurnarount time: %lld\t\tWaiting time: %lld\n", \
			pcb->user_id, pcb->pid, pcb->turnaround_time, pcb->waiting_time);
	sem_post(pcb->data->dispatcher);
}

void	*moniter(void *data)
{
	t_PCB	*pcb;
	t_process_table_node	*process_table_node;
	int	i;

	pcb = (t_PCB *)data;
	while (1)
	{
		sem_wait(pcb->data->moniter_sem);
		process_table_node = pcb->data->process_table->head->next;
		i = -1;
		while (++i < pcb->data->process_cores)
		{
			if (pcb->data->done_count == pcb->data->process_cores - 1)
			{
				sem_post(pcb->data->stop);
				break;
			}
			process_table_node = process_table_node->next;
		}

		sem_post(pcb->data->moniter_sem);
	}
	return ((void *)0);
}

int	FCFS_start(t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->data->moniter, NULL, moniter, (void *)pcb);
	pthread_detach(pcb->data->moniter);
	arriving_wait(pcb->data, pcb, pcb->process_start, pcb->user_id);
	dispatcher(pcb);
	FCFS_running(pcb);
	termination(pcb);
	return (0);
}

void	print_result(t_data *data)
{
	int	i;
	t_process_table_node *process_table_node;

	i = -1;
	process_table_node = data->process_table->head->next;
	printf("\n\n####################\t\tresult\t\t####################\n\n\n");
	while (++i < data->process_table->count)
	{
		printf("PROCESS %d : \t", i + 1);
		printf("PID\t%d  ", process_table_node->pid);
		printf("Turnaround time\t %lld  ", process_table_node->pcb->turnaround_time);
		printf("Waiting time\t %lld  ", process_table_node->pcb->waiting_time);
		process_table_node = process_table_node->next;
		printf("\n");
	}
}

int	FCFS(t_data *data)
{
	start_process(data);
	print_result(data);
	sem_post(data->stop);
	return (0);
}