#include "../../includes/cpu_scheduler.h"

void	update_cost_time(t_PCB *pcb)
{
	pcb->cost_time = get_time() - pcb->running_start;
	usleep(50);
}

void	FCFS_running(t_PCB *pcb)
{
	printf("%lld\n", pcb->data->burst_time[pcb->user_id - 1]);
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id - 1])
			break ;
		// printf("%lld : %lld\n", pcb->cost_time, pcb->data->burst_time[pcb->user_id - 1]);
		pcb->resister += pcb->cost_time;
	}
	printf("done!\n");
}

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->waiting_time = pcb->running_start - pcb->readyque_arrived_time;
	pcb->turnaround_time = pcb->waiting_time + pcb->cost_time;
	pcb->done_count++;
	printf("%d %lld %lld\n", pcb->pid, pcb->turnaround_time, pcb->waiting_time);
	sem_post(pcb->data->dispatcher);
}

void	*moniter(void *data)
{
	t_PCB	*pcb;

	pcb = (t_PCB *)data;
	while (1)
	{
		sem_wait(pcb->data->moniter_sem);
		if (pcb->done_count == pcb->data->process_cores - 1)
		{
			sem_post(pcb->data->stop);
			break;
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
	return (0);
}