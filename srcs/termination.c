#include "../includes/cpu_scheduler.h"

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->waiting_time = pcb->running_start - pcb->readyque_arrived_time;
	pcb->turnaround_time = pcb->waiting_time + pcb->cost_time;
	write_log(pcb);
	// printf("PROCESS: %d\t\tPID: %d\t\tTurnarount time: %lld\t\tWaiting time: %lld\n", \
	// 		pcb->user_id, pcb->pid, pcb->turnaround_time, pcb->waiting_time);
	sem_post(pcb->data->dispatcher);
}