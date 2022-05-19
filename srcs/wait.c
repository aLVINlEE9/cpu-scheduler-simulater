#include "../includes/cpu_scheduler.h"

void	arriving_wait(t_data *data, t_PCB *pcb, uint64_t start, int id)
{
	while (get_time() - start <= data->arriving_time[id])
		usleep(10);
	pcb->readyque_arrived_time = get_time();
	pcb->state = READY;
}

void	waiting_zone(t_data *data, int id)
{
	while (1)
	{
		if (id == data->done)
		{
			data->done = -1;
			break ;
		}
	}
}