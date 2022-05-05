#include "../../includes/cpu_scheduler.h"

void	update_remaining_time(t_PCB *pcb)
{
	pcb->remaining_time = get_time() - pcb->running_start;
}

void	FCFS_running(t_PCB *pcb)
{
	while (pcb->data->burst_time[pcb->user_id - 1] >= pcb->remaining_time)
	{
		update_remaining_time(pcb);
		pcb->resister++;
	}
}

int	FCFS_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	arriving_wait(pcb->data, pcb->process_start, pcb->user_id);
	dispatcher(pcb);
	FCFS_running(pcb);
}

int	FCFS(t_data *data)
{
	start_process(data);
	return (0);
}