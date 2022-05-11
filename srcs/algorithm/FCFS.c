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
	pcb->state = READY;
	dispatcher(pcb);
	FCFS_running(pcb);
	termination(pcb);
	return (0);
}

int	FCFS(t_data *data)
{
	start_process(data);
	sem_post(data->stop);
	return (0);
}