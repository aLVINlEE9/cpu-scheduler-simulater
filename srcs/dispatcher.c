#include "../includes/cpu_scheduler.h"

void	dispatcher(t_PCB *pcb)
{
	sem_wait(pcb->data->dispatcher);
	printf("dis id%d\n", pcb->user_id);
	pcb->state = RUNNING;
	pcb->running_start = get_time();
	pcb->real_running_start = get_time();
}