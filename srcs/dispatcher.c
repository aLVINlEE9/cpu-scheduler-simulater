#include "../includes/cpu_scheduler.h"

void	dispatcher(t_PCB *pcb)
{
	sem_wait(pcb->data->dispatcher);
	pcb->state = RUNNING;
	pcb->running_start = get_time();
}