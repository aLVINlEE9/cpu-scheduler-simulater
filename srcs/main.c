#include "../includes/cpu_scheduler.h"

/*
	Implemented Algorithms
		1) FCFS
		2) SJF
		3) SRTF
		4) PS
		5) RR
		6) MFQ
		7) HRN

	input : {algorithm} {process cores} -b {n} {n} ... -a {n} {n} ... -pr {n} {n} ... -t {n} {n} ...

	option (not optioned -> random value)
		   : -b = burst_time_for_each_processes
		   : -a = arriving_time_for_each_processes
		   : -pr = priority (PS required)
		   : -t = time_quantum (RR required)

		input example : FCFS 5 -b 2 3 10 14 11 -a 0 0 0 0 0
					  : RR 3 -b 2 3 10 -a 0 2 4 -t 5
					  : PS 3 -pr 3 2 1
*/

void	print_scheduling_info(t_data *data)
{
	int i = -1;

	printf("\n\n####################\t\tcpu scheduling information\t\t####################\n\n\n");
	while (++i < data->process_cores)
	{
		printf("PROCESS %d : \t", i + 1);
		printf("burst_time\t%lld  ", data->burst_time[i]);
		printf("arriving_time\t%lld  ", data->arriving_time[i]);
		if (data->priority == NULL)
			printf("no priority\t");
		else
			printf("priority\t%lld  ", data->priority[i]);
		printf("time_quantum\t%lld  ", data->time_quantum);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	t_data	data;

	srand(time(NULL));
	init(argc, argv, &data);
	print_scheduling_info(&data);
	exit(0);
}