#include "../../includes/cpu_scheduler.h"

// 
void	*response_rate_moniter(void *pcb_v)
{
	t_PCB	*pcb, *pcb_rec_1, *pcb_rec_2;
	t_process_table_node	*process_table_node;
	long double	response_rate, temp;
	int	i, flag_1, flag_2;

	pcb = (t_PCB *)pcb_v;
	while (1)
	{
		sem_wait(pcb->data->moniter_wait);
		// printf("ter %d l_ter%d state :%d id:%d\n", pcb->data->terminated, pcb->data->last_terminated, pcb->state, pcb->user_id);
		if (pcb->state == WAITING && pcb->data->terminated != pcb->data->last_terminated)
		{
			printf("ter %d l_ter%d\n", pcb->data->terminated, pcb->data->last_terminated);
			i = -1;
			flag_1 = 0;
			flag_2 = 0;
			response_rate = 0;
			temp = 1;
			process_table_node = pcb->data->process_table->head->next;
			while (++i < pcb->data->process_cores)
			{
				if (process_table_node->pcb->state == WAITING || process_table_node->pcb->state == RUNNING)
				{
					printf("id%d state%d\n", process_table_node->pcb->user_id, process_table_node->pcb->state);
					pcb->data->last_terminated = pcb->data->terminated;
					response_rate = (((long double)get_time() - (long double)process_table_node->pcb->readyque_arrived_time) + (long double)process_table_node->pcb->burst_time) / (long double)process_table_node->pcb->burst_time;
					printf("%Lf\n", response_rate);
					pcb_rec_2 = process_table_node->pcb;
					if (response_rate > temp)
					{
						pcb_rec_1 = process_table_node->pcb;
						temp = response_rate;
						flag_1 = 1;
					}
				}
				else
				{
					flag_2++;
				}
				process_table_node = process_table_node->next;
			}
			if (flag_1)
			{
				printf("moniter :%d temp: %Lf\n", pcb_rec_1->user_id, temp);
				pcb->data->done = pcb_rec_1->user_id;
			}
			else if (flag_2 == pcb->data->process_cores - 1)
			{
				printf("moniter :%d temp: %Lf\n", pcb_rec_2->user_id, temp);
				pcb->data->done = pcb_rec_2->user_id;
			}
		}
		else if (pcb->state == WAITING && pcb->data->terminated == -1)
		{
			printf("moniter :%d\n", pcb->user_id);
			pcb->data->done = pcb->user_id;
		}
		// else if (pcb->state == WAITING && pcb->data->terminated == pcb->data->last_terminated)
		// {
		// 	i = -1;
		// 	flag = 0;
		// 	process_table_node = pcb->data->process_table->head->next;
		// 	while (++i < pcb->data->process_cores)
		// 	{
		// 		if (process_table_node->pcb->state != RUNNING)
		// 			flag++;
		// 		// printf(" %d %d\n", pcb->user_id, process_table_node->pcb->state);
		// 		process_table_node = process_table_node->next;
		// 	}
		// 	if (flag == pcb->data->process_cores)
		// 	{
		// 		printf("moniter :%d\n", pcb->user_id);
		// 		pcb->data->terminated = -1;
		// 	}
		// }
		// else if (pcb->state == WAITING && pcb->data->terminated == pcb->data->last_terminated)
		// {
		// 	i = -1;
		// 	flag = 0;
		// 	process_table_node = pcb->data->process_table->head->next;
		// 	while (++i < pcb->data->process_cores)
		// 	{
		// 		if (process_table_node->pcb->state != RUNNING)
		// 			flag++;
		// 		process_table_node = process_table_node->next;
		// 	}
		// 	if (flag == pcb->data->process_cores)
		// 	{
		// 		printf("%d\n", pcb->user_id);
		// 		pcb->data->terminated = -1;
		// 	}
		// }
		sem_post(pcb->data->moniter_wait);
	}
}

void	HRN_wait(t_data *data, t_PCB *pcb, int id)
{
	pcb->state = WAITING;
	printf("wait in%d state:%d\n", id, pcb->state);
	while (1)
	{
		sem_wait(data->stop);
		if (id == data->done)
		{
			printf("wait done%d\n", id);
			sem_post(pcb->data->moniter_wait);
			sem_wait(data->wait);
			sem_post(data->stop);
			break ;
		}
		sem_post(data->stop);
	}
	pcb->state = READY;
	sem_post(data->wait);
	sem_post(data->stop);
}

void	HRN_running(t_PCB *pcb)
{
	printf("run%d\n", pcb->user_id);
	while (1)
	{
		update_cost_time(pcb);
		if (pcb->cost_time > pcb->data->burst_time[pcb->user_id])
			break ;
		pcb->resister += pcb->cost_time;
	}
}

int	HRN_start(t_data *data, t_process_table_node *process_table_node)
{
	t_PCB *pcb;

	pcb = process_table_node->pcb;
	pthread_create(&pcb->tid1, NULL, response_rate_moniter, (void *)pcb);
	pthread_detach(pcb->tid1);
	arriving_wait(data, pcb, pcb->process_start, pcb->user_id);
	HRN_wait(data, pcb, pcb->user_id);
	dispatcher(pcb);
	HRN_running(pcb);
	termination(pcb);
	return (0);
}

int HRN(t_data *data)
{
	start_process(data);
	return (0);
}