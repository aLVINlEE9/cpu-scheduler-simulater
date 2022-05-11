#include "../includes/cpu_scheduler.h"

void	arriving_wait(t_data *data, t_PCB *pcb, uint64_t start, int id)
{
	while (get_time() - start <= data->arriving_time[id - 1])
		usleep(10);
	pcb->readyque_arrived_time = get_time();
	// printf("wait%d %lld\n", id, pcb->readyque_arrived_time - pcb->process_start);
}
