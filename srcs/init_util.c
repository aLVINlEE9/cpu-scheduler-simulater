#include "../includes/cpu_scheduler.h"

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
