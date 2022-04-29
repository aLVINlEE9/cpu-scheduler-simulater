#include "../includes/cpu_scheduler.h"

void	random_gen(uint64_t *arr, uint64_t loop, uint64_t i, uint64_t j)
{
	uint64_t	k;
	uint64_t	m;

	k = 0;

	while (k < loop)
	{
		if (i == 0)
			arr[k] = milli_to_micro(rand() % (j - i + 1));
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

void	option_put(char **argv, int *options, t_data *data)
{
	int	i;

	i = -1;
	if (options[1] == BURST_TIME)
	{
		data->burst_time = (int *)malloc(sizeof(int) * data->process_cores);
		if (data->burst_time == NULL)
			error_print("memory error[parse_options](failed to malloc memory)");
		while (++i < data->process_cores)
		{
			data->burst_time[i] = 
		}
	}
	else if (options[1] == ARRIVING_TIME)
	else if (options[1] == PRIORITY)
	else if (options[1] == TIME_QUANTUM)
}

void	option_algo_check(t_data *data)
{
	int	i;

	i = -1;
	if (data->scheduling_algo == FCFS || data->scheduling_algo == HRN || \
		data->scheduling_algo == MFQ || data->scheduling_algo == SJF || \
		data->scheduling_algo == SRTF)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == PRIORITY || \
				data->option_info[i][1] == TIME_QUANTUM)
				error_print("bad arguments[parse_options](incorrect option with algo)");
		}
	}
	else if (data->scheduling_algo == PS)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == TIME_QUANTUM)
				error_print("bad arguments[parse_options](incorrect option with algo)");
		}
	}
	else if (data->scheduling_algo == RR)
	{
		while (++i < data->option_count)
		{
			if (data->option_info[i][1] == PRIORITY)
				error_print("bad arguments[parse_options](incorrect option with algo)");
		}
	}
}

int	choose_option(char *argv, t_data *data)
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
}

void	option_count_sub(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;
	int	temp;

	i = 2;
	j = 0;
	while (++i < argc)
	{
		temp = i;
		if (argv[i][0] == '-')
		{
			data->option_info[j][0] = i + 1;
			data->option_info[j][1] = choose_option(&argv[i][1], data);
			if (j != 0)
			{
				if (data->option_info[j][1] != TIME_QUANTUM)
					if (data->option_info[j][0] - data->option_info[j - 1][0] \
						!= data->option_count + 1)
						error_print("bad arguments[parse_options](incorrect option amout)");
				else
					if (data->option_info[j][0] - data->option_info[j - 1][0] \
						!= 2)
						error_print("bad arguments[parse_options](incorrect option amout)");
			}
			j++;
		}
	}
}

void	option_count(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;
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
