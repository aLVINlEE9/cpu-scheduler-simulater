#include "../../includes/cpu_scheduler.h"

int	SRTF_start(t_data *data, t_process_table_node *process_table_node)
{
	(void)process_table_node;
	(void)data;
	return (0);
}

int	SRTF(t_data *data)
{
	start_process(data);
	return (0);
}