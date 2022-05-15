#include "../includes/cpu_scheduler.h"

void	arriving_wait(t_data *data, t_PCB *pcb, uint64_t start, int id)
{
	while (get_time() - start <= data->arriving_time[id])
		usleep(10);
	pcb->readyque_arrived_time = get_time();
	pcb->state = READY;
	// printf("id :%d readyque_arrived_time: %lld\n", id, pcb->readyque_arrived_time);
}
