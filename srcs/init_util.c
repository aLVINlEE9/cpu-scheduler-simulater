#include "../includes/cpu_scheduler.h"

void	options_input(t_data *data, uint64_t *opt, char **argv, int idx)
{
	int	i;

	i = -1;
	while (++i < data->process_cores)
		opt[i] = atoi(argv[idx + i]);
}

void	options_malloc(t_data *data)
{
	int	cores;

	cores = data->process_cores;
	data->burst_time = (uint64_t *)malloc(sizeof(uint64_t) * cores);
	data->arriving_time = (uint64_t *)malloc(sizeof(uint64_t) * cores);
	if (data->scheduling_algo == PS)
		data->priority = (uint64_t *)malloc(sizeof(uint64_t) * cores);
	else
		data->priority = NULL;
}

uint64_t	milli_to_micro(uint64_t milli)
{
	return (milli * 1000);
}

int	is_not_num(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
	}
	return (0);
}
