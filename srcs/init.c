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
	if (data->process_cores < 1)
		error_print("bad arguments[process_cores](not enough process)");
}

void	parse_options(int argc, char **argv, t_data *data)
{
	int	i;

	i = -1;
	option_count(argc, argv, data);
	option_algo_check(data);
	while (++i < data->option_count)
		option_put(argv, &data->option_info[i], data);
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