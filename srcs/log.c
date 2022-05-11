#include "../includes/cpu_scheduler.h"

void	write_log(t_PCB *pcb)
{
	char	*pid_ch;
	char	dir[1000] = "./log/";
	FILE	*fp;

	pid_ch = ft_itoa((int)pcb->user_id);
	strcat(dir, pid_ch);
	fp = fopen(dir, "w");
	fprintf(fp, "%d %d %lld %lld", pcb->user_id, pcb->pid, pcb->turnaround_time, pcb->turnaround_time);
	fclose(fp);
}

void	read_log(int i)
{
	char	*pid_ch;
	char	dir[1000] = "./log/";
	char	buffer[1000];
	char	**splited_buffer;
	FILE	*fp;

	pid_ch = ft_itoa((int)i);
	strcat(dir, pid_ch);
	fp = fopen(dir, "r");
	fgets(buffer, sizeof(buffer), fp);
	splited_buffer = ft_split(buffer, ' ');
	printf("PROCESS: %s\t\t", splited_buffer[0]);
	printf("PID: %s\t\t", splited_buffer[1]);
	printf("Turnarount time: %s\t\t", splited_buffer[2]);
	printf("Waiting time: %s\n", splited_buffer[3]);
	fclose(fp);
	unlink(dir);
}

void	print_log(t_data *data)
{
	int	i;
	t_process_table_node	*process_table_node;

	i = -1;
	printf("\n\n######################\t\t\t\tresult\t\t\t\t######################\n\n\n");
	process_table_node = data->process_table->head->next;
	while (++i < data->process_cores)
	{
		read_log(i + 1);
		process_table_node = process_table_node->next;
	}
}