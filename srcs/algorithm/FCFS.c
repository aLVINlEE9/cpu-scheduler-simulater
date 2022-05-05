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

int	FCFS(t_data *data)
{
	FCFS_scheduling(data);
	start_process(data);
	return (0);
}