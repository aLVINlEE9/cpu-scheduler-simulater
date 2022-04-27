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

int main(int argc, char **argv)
{
	t_data	data;

	init(argc, argv, &data);
}