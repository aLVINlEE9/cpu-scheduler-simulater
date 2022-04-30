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
	if (!is_num(argv))
		error_print("bad arguments[process_cores](incorrect process_cores)");
	data->process_cores = atoi(argv);
	if (data->process_cores < 1)
		error_print("bad arguments[process_cores](not enough process)");
}

void	put_random_option(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->option_tf[i] == FALSE)
		{
			if (option_check_algo(i + 10, data))
				continue ;
			else
				option_each_random(i + 10, data);
		}
	}
}

void	parse_each_options(int argc, char **argv, t_data *data)
{
	int	i;
	int	next_option;

	i = 3;
	next_option = 0;
	option_malloc(data);
	while (i + next_option < argc)
	{
		option_each(argv, argc, i + next_option, data);
		next_option += (data->process_cores + 1);
		if (i + next_option > argc)
			error_print("bad arguments[option](incorrect option, amount)");
		if (i + next_option == argc)
			break ;
	}
}

void	parse_options(int argc, char **argv, t_data *data)
{
	parse_each_options(argc, argv, data);
	put_random_option(data);
}

void	init(int argc, char **argv, t_data *data)
{
	if (argc > 2)
	{
		parse_algorithm(argv[1], data);
		parse_process_cores(argv[2], data);
		parse_options(argc, argv, data);
	}
	else
		error_print("bad arguments[input](non input)");
}