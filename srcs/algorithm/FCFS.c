#include "../../includes/cpu_scheduler.h"

int	FCFS_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
}

void	FCFS_scheduling(t_data *data)
{

}

int	FCFS(t_data *data)
{
	FCFS_scheduling(data);
	start_process(data);
	return (0);
}