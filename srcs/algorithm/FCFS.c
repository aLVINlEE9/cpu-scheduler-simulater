#include "../../includes/cpu_scheduler.h"

void	update_cost_time(t_PCB *pcb)
{
	pcb->cost_time = get_time() - pcb->running_start;
}

void	FCFS_running(t_PCB *pcb)
{
	while (pcb->data->burst_time[pcb->user_id - 1] >= pcb->cost_time)
	{
		update_cost_time(pcb);
		pcb->resister += pcb->cost_time;
	}
}

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->waiting_time = pcb->running_start - pcb->process_start;
	pcb->turnaround_time = pcb->waiting_time + pcb->cost_time;
	sem_post(pcb->data->dispatcher);
}

int	FCFS_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(pcb->data, pcb->process_start, pcb->user_id);
	dispatcher(pcb);
	FCFS_running(pcb);
	termination(pcb);
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
		printf("Turnaround time", process_table_node->pcb->turnaround_time);
		printf("Waiting time\t %lld  ", process_table_node->pcb->waiting_time);
		process_table_node = process_table_node->next;
	}
}

int	FCFS(t_data *data)
{
	FCFS_scheduling(data);
	start_process(data);
	print_result(data);
	return (0);
}