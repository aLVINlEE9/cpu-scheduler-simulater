#include "../includes/cpu_scheduler.h"

void	parse_algorithm(char *argv, t_data *data)
{
	if (strcmp(argv, "FCFS") == 0)
		data->scheduling_algo = FCFS;
	else if (strcmp(argv, "HRN") == 0)
		data->scheduling_algo = HRN;
	else if (strcmp(argv, "MFQ") == 0)
		data->scheduling_algo = MFQ;
	else if (strcmp(argv, "PS") == 0)
		data->scheduling_algo = PS;
	else if (strcmp(argv, "RR") == 0)
		data->scheduling_algo = RR;
	else if (strcmp(argv, "SJF") == 0)
		data->scheduling_algo = SJF;
	else if (strcmp(argv, "SRTF") == 0)
		data->scheduling_algo = SRTF;
	else
		error_print("bad arguments[algorithm](incorrect algorithm)");
}

void	parse_process_cores(char *argv, t_data *data)
{
	if (!is_not_num(argv))
		error_print("bad arguments[process_cores](incorrect process_cores)");
	data->process_cores = atoi(argv);
}

int	parse_option_nums(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;
	int	k;
	int	cnt;

	i = 2;
	cnt = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j++] == '-')
				cnt++;
		}
	}
	if (cnt == 0)
		data->option_nums = NULL;
	data->option_nums = (int *)malloc(sizeof(int) * cnt);
	if (data->option_nums == NULL)
		error_print("memory error[option_nums](failed to malloc)");
	i = 2;
	k = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j++] == '-')
			{
				data->option_nums[k] = i;
				k++;
				break ;
			}
		}
	}
	return (k);
}

void	parse_options(int argc, char **argv, t_data *data, int opt_cnt)
{
	int	i;
	int	idx;
	char ch;

	i = -1;
	idx = 0;
	srand(time(NULL));
	options_malloc(data);
	if (data->option_nums == NULL)
	{
		while (++i < data->process_cores)
		{
			data->burst_time[i] = milli_to_micro(rand() % 31);
			data->arriving_time[i] = milli_to_micro(rand() % 31);
			if (data->scheduling_algo == PS && data->priority != NULL)
				data->priority[i] = rand() % 5 + 1;
		}
		if (data->scheduling_algo == RR)
			data->time_quantum = rand() % 10 + 1;
		else
			data->time_quantum = 0;
	}
	else
	{
		i = -1;
		while (++i < opt_cnt)
		{
			idx = data->option_nums[i];
			ch = argv[idx][1];
			if (ch == 'b')
				options_input(data, data->burst_time, argv, idx + 1);
			else if (ch == 'a')
				options_input(data, data->arriving_time, argv, idx + 1);
			else if (ch == 'p' && argv[idx][2] == 'r' && argv[idx][3] == '\0' && data->priority != NULL)
				options_input(data, data->priority, argv, idx + 1);
			else if (ch == 't' && data->scheduling_algo == RR)
				data->time_quantum = atoi(argv[idx + 1]);
			else
				error_print("bad arguments[option](incorrect option)");
		}
	}
	(void)argc;
}

void	init(int argc, char **argv, t_data *data)
{
	int opt_cnt;

	opt_cnt = 0;
	if (argc >= 1)
	{
		parse_algorithm(argv[1], data);
		parse_process_cores(argv[2], data);
		opt_cnt = parse_option_nums(argc, argv, data);
		parse_options(argc, argv, data, opt_cnt);
	}
	else
		error_print("bad arguments[input](non input)");
}