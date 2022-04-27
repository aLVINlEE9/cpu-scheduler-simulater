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

void	parse_option_nums(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;
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
	data->option_nums = cnt;
}

void	init(int argc, char **argv, t_data *data)
{
	if (argc >= 1)
	{
		parse_algorithm(argv[1], data);
		parse_process_cores(argv[2], data);
		parse_option_nums(argc, argv, data);
	}
	else
		error_print("bad arguments[input](non input)");
}