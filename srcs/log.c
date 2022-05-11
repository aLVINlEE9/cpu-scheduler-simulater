#include "../includes/cpu_scheduler.h"

void	write_log(t_PCB *pcb)
{
	char	*pid_ch;
	FILE	*fp;

	pid_ch = ft_itoa((int)pcb->pid);
	fp = fopen(pid_ch, "w");
	fprintf(fp, "%d %d %lld %lld", pcb->user_id, pcb->pid, pcb->turnaround_time, pcb->turnaround_time);
	fclose(fp);
}
