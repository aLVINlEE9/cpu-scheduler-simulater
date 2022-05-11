#include "../../includes/cpu_scheduler.h"

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

int	FCFS_start(t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
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