#ifndef CPU_SCHEDULER_H
# define CPU_SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#define FALSE			0
#define TRUE			1

/*
	define options
*/

#define BURST_TIME		10
#define ARRIVING_TIME	11
#define PRIORITY		12
#define TIME_QUANTUM	13

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
	// register 		i;
	uint64_t		start;
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

/*
	data(input values)
*/
typedef struct s_data
{
	t_process_table *process_table;
	int				process_cores;
	int				(* scheduling_algo)(struct s_data *);
	int				*option_tf;
	uint64_t		*burst_time;
	uint64_t		*arriving_time;
	uint64_t		*priority;
	uint64_t		*time_quantum;
}	t_data;

int			FCFS(t_data *data);
int			HRN(t_data *data);
int			MFQ(t_data *data);
int			PS(t_data *data);
int			RR(t_data *data);
int			SJF(t_data *data);
int			SRTF(t_data *data);

void		error_print(char *err_msg);

int			option_check_algo(int type, t_data *data);
void		option_each_random_sub(uint64_t *arr, uint64_t loop, uint64_t i, uint64_t j);
void		option_each_random(int type, t_data *data);
void		option_each_sub(char **argv, int argc, int idx, int type, uint64_t *option, t_data *data);
void		option_each(char **argv, int argc, int idx, t_data *data);
void		option_malloc(t_data *data);
uint64_t	milli_to_micro(uint64_t milli);
int			is_num(char *argv);

void		parse_algorithm(char *argv, t_data *data);
void		parse_process_cores(char *argv, t_data *data);
void		put_random_option(t_data *data);
void		parse_each_options(int argc, char **argv, t_data *data);
void		parse_options(int argc, char **argv, t_data *data);
void		init(int argc, char **argv, t_data *data);

void		print_scheduling_info(t_data *data);

#endif