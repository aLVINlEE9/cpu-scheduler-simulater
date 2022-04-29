#include "../includes/cpu_scheduler.h"

void	random_gen(uint64_t *arr, uint64_t loop, uint64_t i, uint64_t j)
{
	uint64_t	k;
	uint64_t	m;

	k = 0;

	while (k < loop)
	{
		if (i == 0)
			arr[k] = milli_to_micro(rand() % (j + 1));
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

void	not_use_options(int type, t_data *data)
{
	if (type == PRIORITY)
		data->priority = NULL;
	else if (type == TIME_QUANTUM)
		data->time_quantum = 0;
}

void	option_random_sub(int type, t_data *data)
{
	if (type == BURST_TIME)
	{
		data->burst_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->burst_time == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		random_gen(data->burst_time, data->process_cores, 0, 30);
	}
	else if (type == ARRIVING_TIME)
	{
		data->arriving_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->arriving_time == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		random_gen(data->arriving_time, data->process_cores, 0, 15);
	}
	else if (type == PRIORITY)
	{
		data->priority = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->priority == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		random_gen(data->priority, data->process_cores, 1, 5);
	}
	else if (type == TIME_QUANTUM)
		data->time_quantum = rand() % 10 + 1;
}

void	option_random(t_data *data)
{
	if (data->scheduling_algo == FCFS || data->scheduling_algo == HRN || \
		data->scheduling_algo == MFQ || data->scheduling_algo == SJF || \
		data->scheduling_algo == SRTF)
	{
		if (data->option_v[BURST_TIME - 10] == FALSE)
			option_random_sub(BURST_TIME, data);
		if (data->option_v[ARRIVING_TIME - 10] == FALSE)
			option_random_sub(ARRIVING_TIME, data);
		not_use_options(PRIORITY, data);
		not_use_options(TIME_QUANTUM, data);
	}
	else if (data->scheduling_algo == PS)
	{
		if (data->option_v[BURST_TIME - 10] == FALSE)
			option_random_sub(BURST_TIME, data);
		if (data->option_v[ARRIVING_TIME - 10] == FALSE)
			option_random_sub(ARRIVING_TIME, data);
		if (data->option_v[PRIORITY - 10] == FALSE)
			option_random_sub(PRIORITY, data);
		not_use_options(TIME_QUANTUM, data);
	}
	else if (data->scheduling_algo == RR)
	{
		if (data->option_v[BURST_TIME - 10] == FALSE)
			option_random_sub(BURST_TIME, data);
		if (data->option_v[ARRIVING_TIME - 10] == FALSE)
			option_random_sub(ARRIVING_TIME, data);
		if (data->option_v[TIME_QUANTUM - 10] == FALSE)
			option_random_sub(TIME_QUANTUM, data);
		not_use_options(PRIORITY, data);
	}
}

void	option_put(char **argv, int *options, t_data *data)
{
	int	i;

	i = -1;
	if (options[1] == BURST_TIME)
	{
		data->burst_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->burst_time == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		while (++i < data->process_cores)
			data->burst_time[i] = milli_to_micro(atoi(argv[options[0] + i]));
	}
	else if (options[1] == ARRIVING_TIME)
	{
		data->arriving_time = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->arriving_time == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		while (++i < data->process_cores)
			data->arriving_time[i] = milli_to_micro(atoi(argv[options[0] + i]));
	}
	else if (options[1] == PRIORITY)
	{
		data->priority = (uint64_t *)malloc(sizeof(uint64_t) * data->process_cores);
		if (data->priority == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		while (++i < data->process_cores)
			data->priority[i] = atoi(argv[options[0] + i]);
	}
	else if (options[1] == TIME_QUANTUM)
	{
		data->time_quantum = milli_to_micro(atoi(argv[options[0]]));
	}
}

void	option_ex(t_data *data)
{
	data->option_v = (int *)malloc(sizeof(int) * 4);
	if (data->option_v == NULL)
		error_print("memory error[parse_options](failed to malloc memory)");
	data->option_v[0] = FALSE;
	data->option_v[1] = FALSE;
	data->option_v[2] = FALSE;
	data->option_v[3] = FALSE;
}

void	option_algo_check(t_data *data)
{
	int	i;

	i = -1;
	option_ex(data);
	if (data->scheduling_algo == FCFS || data->scheduling_algo == HRN || \
		data->scheduling_algo == MFQ || data->scheduling_algo == SJF || \
		data->scheduling_algo == SRTF)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == PRIORITY || \
				data->option_info[i][1] == TIME_QUANTUM)
				error_print("bad arguments[parse_options](incorrect option with algo)");
			data->option_v[data->option_info[i][1] - 10] = TRUE;
		}
	}
	else if (data->scheduling_algo == PS)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == TIME_QUANTUM)
				error_print("bad arguments[parse_options](incorrect option with algo)");
			data->option_v[data->option_info[i][1] - 10] = TRUE;
		}
	}
	else if (data->scheduling_algo == RR)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == PRIORITY)
				error_print("bad arguments[parse_options](incorrect option with algo)");
			data->option_v[data->option_info[i][1] - 10] = TRUE;
		}
	}
}

int	choose_option(char *argv)
{
	if (strcmp(argv, "b") == 0)
		return (BURST_TIME);
	else if (strcmp(argv, "a") == 0)
		return (ARRIVING_TIME);
	else if (strcmp(argv, "pr") == 0)
		return (PRIORITY);
	else if (strcmp(argv, "t") == 0)
		return (TIME_QUANTUM);
	else
		error_print("bad arguments[parse_options](incorrect option)");
	return (0);
}

void	option_count_sub(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			data->option_info[j][0] = i + 1;
			data->option_info[j][1] = choose_option(&argv[i][1]);
			if (j != 0)
			{
				if (data->option_info[j][1] != TIME_QUANTUM)
				{
					if (data->option_info[j][0] - data->option_info[j - 1][0] \
						!= data->process_cores + 1)
						error_print("bad arguments[parse_options](incorrect option amount)");
				}
				else
				{
					if (data->option_info[j][0] - data->option_info[j - 1][0] \
						!= 2)
						error_print("bad arguments[parse_options](incorrect option amount)");
				}
			}
			j++;
		}
	}
}

void	option_count(int argc, char **argv, t_data *data)
{
	int	i;
	int	cnt;

	i = 2;
	cnt = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			cnt++;
	}
	data->option_count = cnt;
	if (cnt == 0)
		return ;
	data->option_info = (int **)malloc(sizeof(int *) * cnt);
	if (data->option_info == NULL)
		error_print("memory error[parse_options](failed to malloc memory)");
	i = -1;
	while (++i < data->option_count)
	{
		data->option_info[i] = (int *)malloc(sizeof(int) * 2);
		if (data->option_info[i] == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
	}
	option_count_sub(argc, argv, data);
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
			return (0);
	}
	return (1);
}
