#include "../includes/cpu_scheduler.h"

void	create_pcb(t_PCB *pcb, int id)
{
	pcb->pid = 0;
	pcb->user_id = id;
	pcb->state = NEW;
	pcb->start = 0;
}

void	append_process_table_node(t_process_table *process_table, \
									t_process_table_node *new_node, int id)
{
	process_table->tail->prev->next = new_node;
	new_node->prev = process_table->tail->prev;
	new_node->next = process_table->tail;
	process_table->tail->prev = new_node;
	process_table->count++;
	new_node->pid = 0;
	new_node->pcb = (t_process_table_node *)malloc(sizeof(t_process_table_node));
	if (new_node->pcb == NULL)
		error_print("memory error[node](failed to malloc memory)");
	create_pcb(new_node->pcb, id);
}

t_process_table_node	*create_process_table_node(void)
{
	t_process_table_node	*new_node;

	new_node = (t_process_table_node *)malloc(sizeof(t_process_table_node));
	if (new_node == NULL)
		error_print("memory error[node](failed to malloc memory)");
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->pid = 0;
	new_node->pcb = NULL;
	return (new_node);
}

void	create_process_table(t_data *data)
{
	data->process_table->head = create_process_table_node();
	data->process_table->tail = create_process_table_node();
	data->process_table->count = 0;
}

void	init_process_table(t_data *data)
{
	int	i;
	t_process_table_node	*new_node;

	i = -1;
	data->process_table = (t_process_table *)malloc(sizeof(t_process_table));
	if (data->process_table == NULL)
		error_print("memory error[node](failed to malloc memory)");
	create_process_table(data);
	while (++i < data->process_cores)
	{
		new_node = create_process_table_node();
		append_process_table_node(data->process_table, new_node, i);
	}
}
