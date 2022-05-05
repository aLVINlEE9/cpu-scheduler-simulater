#include "../includes/cpu_scheduler.h"

void	arriving_wait(t_data *data, uint64_t start, int id)
{
	while (get_time() - start <= data->arriving_time[id - 1])
		usleep(10);
}