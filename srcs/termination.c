#include "../includes/cpu_scheduler.h"

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->waiting_time = pcb->running_start - pcb->readyque_arrived_time;
	pcb->turnaround_time = pcb->waiting_time + pcb->cost_time;
	write_log(pcb);
	// printf("%d\t\t%lld\t\t%lld\t\t%lld\n", \
	// 		pcb->user_id, pcb->running_start, pcb->readyque_arrived_time, pcb->cost_time);
	sem_post(pcb->data->dispatcher);
}