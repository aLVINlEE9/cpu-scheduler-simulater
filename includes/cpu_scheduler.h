#ifndef CPU_SCHEDULER_H
# define CPU_SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/mman.h>


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
	pthread_t		tid1;
	pthread_t		tid2;
	int				user_id;
	process_state	state;
	uint64_t		resister;
	struct s_data	*data;
	uint64_t		burst_time;
	uint64_t		arriving_time;
	uint64_t		priority;
	uint64_t		time_quantum;
	uint64_t		process_start;
	uint64_t		readyque_arrived_time;
	uint64_t		running_start;
	uint64_t		real_running_start;
	uint64_t		waiting_time;
	uint64_t		turnaround_time;
	uint64_t		cost_time;
	int				repeated_times;
}	t_PCB;

/*
	process_table_node
*/
typedef struct s_process_table_node
{
	struct s_process_table_node	*next;
	struct s_process_table_node	*prev;
	pid_t						pid;
	pid_t						pid_k;
	t_PCB						*pcb;
}	t_process_table_node;

/*
	process_table(dummy node)
*/
typedef struct s_process_table
{
	t_process_table_node	*head;
	t_process_table_node	*tail;
	uint64_t				average_waiting_time;
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
	int				(* algo_start)(struct s_data *, t_process_table_node *);
	int				*option_tf;
	uint64_t		*burst_time;
	uint64_t		*arriving_time;
	uint64_t		*priority;
	uint64_t		*time_quantum;
	sem_t			*dispatcher;
	sem_t			*wait;
	sem_t			*moniter_wait;
	int				done;
}	t_data;

void		update_cost_time(t_PCB *pcb);
void		FCFS_running(t_PCB *pcb);
void		termination(t_PCB *pcb);
int			FCFS_start(t_data *data, t_process_table_node *process_table_node);
void		print_result(t_data *data);
int			FCFS(t_data *data);

int			HRN_start(t_data *data, t_process_table_node *process_table_node);
int 		HRN(t_data *data);

int			MFQ_start(t_data *data, t_process_table_node *process_table_node);
int			MFQ(t_data *data);

int			PS_start(t_data *data, t_process_table_node *process_table_node);
int			PS(t_data *data);

int			RR_start(t_data *data, t_process_table_node *process_table_node);
int			RR(t_data *data);

int			SJF_start(t_data *data, t_process_table_node *process_table_node);
void		SJF_wait(t_data *data, t_PCB *pcb, int id);
int			SJF(t_data *data);

int			SRTF_start(t_data *data, t_process_table_node *process_table_node);
int			SRTF(t_data *data);

void		dispatcher(t_PCB *pcb);
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
void		init_semaphores(t_data *data);
void		init(int argc, char **argv, t_data *data);

void		print_log(t_data *data);
void		write_log(t_PCB *pcb);

void		print_scheduling_info(t_data *data);

void		create_pcb(t_data *data, t_PCB *pcb, int id);
void		append_process_table_node(t_data *data, t_process_table *process_table, \
									t_process_table_node *new_node, int id);
t_process_table_node	*create_process_table_node(void);
void		create_process_table(t_data *data);
void		init_process_table(t_data *data);

void		init_process(t_process_table_node *process_table_node, int i);
void		start_process(t_data *data);

int			compare(const void * a, const void * b);
void		sort(t_data *data, t_process_table *process_table, char *flag);

uint64_t	get_time(void);
void		arriving_wait(t_data *data, t_PCB *pcb, uint64_t start, int id);
void		waiting_zone(t_data *data, int id);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);

#endif