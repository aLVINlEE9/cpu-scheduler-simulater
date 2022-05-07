#include "../../includes/cpu_scheduler.h"

int	MFQ_start(t_process_table_node *process_table_node)
{
	(void)process_table_node;
	return (0);
}

int	MFQ(t_data *data)
{
	start_process(data);
	return (0);
}