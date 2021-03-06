#include "../includes/cpu_scheduler.h"

void	termination(t_PCB *pcb)
{
	pcb->state = TERMINATED;
	pcb->response_time = pcb->real_running_start - pcb->readyque_arrived_time;
	pcb->turnaround_time = pcb->running_start - pcb->readyque_arrived_time + pcb->cost_time;
	pcb->waiting_time = pcb->response_time + pcb->waiting_time;
	pcb->data->terminated = pcb->user_id;
	write_log(pcb);
	sem_post(pcb->data->dispatcher);
}