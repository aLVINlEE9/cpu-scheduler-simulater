#ifndef CPU_SCHEDULER_H
# define CPU_SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*
	Errors
*/

/*
	process state
*/

typedef enum e_process_state
{
	NEW = 0,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
}	process_state;

/*
	PCB
*/

typedef struct s_PCB
{
	pid_t			pid;
	int				user_id;
	process_state	state;
	// int				(* scheduling_algo)(struct s_PCB *)
	// register 		i;
	uint64_t		start
}	t_PCB;

/*
	process_table_node
*/

typedef struct s_process_table_node
{
	struct s_process_table_node	*next;
	struct s_process_table_node	*prev;
	pid_t						pid;
	t_PCB						*pcb;
}	t_process_table_node;

/*
	process_table(dummy node)
*/
typedef struct s_process_table
{
	t_process_table_node	*head;
	t_process_table_node	*tail;
	int						count;
}	t_process_table;


#endif