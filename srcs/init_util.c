#include "../includes/cpu_scheduler.h"

int	option_check_algo(int type, t_data *data)
{
	if (data->scheduling_algo == FCFS || data->scheduling_algo == HRN || \
		data->scheduling_algo == MFQ || data->scheduling_algo == SJF || \
		data->scheduling_algo == SRTF)
	{
		if (type == PRIORITY)
			return (1);
		if (type == TIME_QUANTUM)
			return (1);
	}
	else if (data->scheduling_algo == PS)
	{
		if (type == TIME_QUANTUM)
			return (1);
	}
	else if (data->scheduling_algo == RR)
	{
		if (type == PRIORITY)
			return (1);
	}
	return (0);
}

void	option_each_random_sub(uint64_t *arr, uint64_t loop, uint64_t i, uint64_t j)
{
	uint64_t	k;
	uint64_t	m;
	uint64_t	tmp;

	k = 0;

	if (i == 2)
	{
		tmp = milli_to_micro(rand() % j + 1);
		while (k < loop)
			arr[k++] = tmp;
		return ;
	}
	while (k < loop)
	{
		if (i == 0)
			arr[k] = milli_to_micro(rand() % j + 1);
		else if (i == 1)
			arr[k] = rand() % j + 1;
		m = 0;
		while (m < k)
		{
			if (arr[k] == arr[m])
				--k;
			m++;
		}
		k++;
	}
}

void	option_each_random(int type, t_data *data)
{
	if (type == BURST_TIME)
		option_each_random_sub(data->burst_time ,data->process_cores, 0, 30);
	if (type == ARRIVING_TIME)
		option_each_random_sub(data->arriving_time, data->process_cores, 0, 15);
	if (type == PRIORITY)
		option_each_random_sub(data->priority, data->process_cores, 1, 5);
	if (type == TIME_QUANTUM)
		option_each_random_sub(data->time_quantum, data->process_cores, 2, 10);
}

void	option_each_sub(char **argv, int argc, int idx, int type, uint64_t *option, t_data *data)
{
	int	i;
	int	tmp_idx;

	i = -1;
	tmp_idx = idx;
	if (option_check_algo(type, data))
		error_print("bad arguments[option](incorrect option, not match with algo)");
	while (idx < tmp_idx + data->process_cores && idx < argc)
	{
		if (!is_num(argv[idx]))
			error_print("bad arguments[option](incorrect option, not a number)");
		option[++i] = milli_to_micro(atoi(argv[idx]));
		idx++;
	}
	if (idx != tmp_idx + data->process_cores)
		error_print("bad arguments[option](incorrect option, amount)");
	else
		data->option_tf[type - 10] = TRUE;
}

void	option_each(char **argv, int argc, int idx, t_data *data)
{
	if (strcmp(argv[idx], "-b") == 0)
		option_each_sub(argv, argc, idx + 1, BURST_TIME, data->burst_time, data);
	else if (strcmp(argv[idx], "-a") == 0)
		option_each_sub(argv, argc, idx + 1, ARRIVING_TIME, data->arriving_time, data);
	else if (strcmp(argv[idx], "-pr") == 0)
		option_each_sub(argv, argc, idx + 1, PRIORITY, data->priority, data);
	else if (strcmp(argv[idx], "-t") == 0)
		option_each_sub(argv, argc, idx + 1, TIME_QUANTUM, data->time_quantum, data);
	else
		error_print("bad arguments[option](incorrect option, not allowed option)");
}

void	option_malloc(t_data *data)
{
	int	i;

	i = -1;
	data->burst_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
	if (data->burst_time == NULL)
		error_print("memory error[option](failed to malloc memory)");
	data->arriving_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
	if (data->arriving_time == NULL)
		error_print("memory error[option](failed to malloc memory)");
	data->priority = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
	if (data->priority == NULL)
		error_print("memory error[option](failed to malloc memory)");
	data->time_quantum = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
	if (data->time_quantum == NULL)
		error_print("memory error[option](failed to malloc memory)");
	while (++i < data->process_cores)
	{
		data->burst_time[i] = 0;
		data->arriving_time[i] = 0;
		data->priority[i] = 0;
		data->time_quantum[i] = 0;
	}
	data->option_tf = (int *)malloc(sizeof(int) * 4);
	if (data->option_tf == NULL)
		error_print("memory error[option](failed to malloc memory)");
	i = -1;
	while (++i < 4)
		data->option_tf[i] = FALSE;
}

uint64_t	milli_to_micro(uint64_t milli)
{
	return (milli * 1000);
}

int	is_num(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
	}
	return (1);
}
