/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 17:16:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 22:43:32 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>

# define BUFFER_SIZE 32

typedef struct s_node{
	int				data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list{
	int		count;
	int		min;
	int		max[3];
	t_node	*head;
	t_node	*tail;
}	t_list;

/*
	a[0] == ra;
	a[1] == rra;
	b[0] == rb;
	b[1] == rrb;
*/

typedef struct s_best_actions{
	int	a[2];
	int	b[2];
}	t_best_actions;

/*
	a[0] == ra;
	a[1] == rra;
	b[0] == rb;
	b[1] == rrb;
	r[0] == rr;
	r[1] == rrr;
*/
typedef struct s_execute_actions{
	int	a[2];
	int	b[2];
	int	r[2];
	int	count;
}	t_exe_acts;

typedef struct s_datas{
	t_best_actions		b_acts;
	t_exe_acts			exe_acts;
	t_list				*a_stack;
	t_list				*b_stack;
}	t_datas;

size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		print_action(char *action, int cnt);
void		action_exe(t_datas *datas, char *action, int cnt, int print);
void		exe_best_actions(t_datas *datas);

void		pa(t_datas *datas, int cnt);
void		pb(t_datas *datas, int cnt);
void		ra(t_datas *datas, int cnt);
void		rb(t_datas *datas, int cnt);
void		rr(t_datas *datas, int cnt);
void		rra(t_datas *datas, int cnt);
void		rrb(t_datas *datas, int cnt);
void		rrr(t_datas *datas, int cnt);
void		sa(t_datas *datas, int cnt);
void		sb(t_datas *datas, int cnt);
void		ss(t_datas *datas, int cnt);

void		rotate(t_list *stack);
void		reverse_rotate(t_list *stack);
void		push_pop(t_list *push, t_list *pop);
void		swap(t_list *stack);

void		init_stack(t_list *stack);
int			create_list(t_list *stack);
void		create_stack(t_datas *datas);

int			exception_print(char *str);
int			exception_parsing_string(char *buf);
int			exception_parsing_number(long long buf);
int			check_sort(t_list *stack);
int			exception_parsing_sort(t_list *a_stack);

int			free_list(t_list *stack);
int			free_stack(t_list *stack);
int			free_node(t_node *node);

void		init_best_actions(t_datas *datas);
void		init_execute_actions(t_datas *datas);
void		set_execute_actions(t_datas *datas, t_exe_acts *exe, int a, int b);
void		merge_best_actions_sub(t_datas *datas, int a, int b);

void		append_node_sub(t_list *stack, t_node *new_node);
int			append_node(t_list *a_stack, char *buf, size_t size);
t_node		*create_node(int data);
void		print_node(t_list *stack); // d

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
long long	ft_atol(const char *str);
int			split_to_stack(char **argv, t_list *Astack, int i);

void		init_datas(t_datas *datas);
void		parsing(t_datas *datas, int argc, char **argv);

void		sort_2(t_datas *datas);
void		sort_3(t_datas *datas);

int			isin_max(t_list *stack, int data);
int			get_max_value(t_list *stack, int threshold);
void		set_max_array(t_list *stack);
void		set_min_value(t_list *stack);

void		merge_best_actions(t_datas *datas);
void		choose_best_actions_sub(t_datas *datas, int data);
void		choose_best_actions(t_datas *datas);
void		insertion_sort(t_datas *datas);
void		sorting_algorithm(t_datas *datas);

void		insertion_sort_sub(t_datas *datas);
void		sort_left(t_datas *datas);

int			get_next_line(int fd, char **line, int read_size);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memmove(void *dst, const void *src, size_t num);

void		checker(t_datas *datas);
int			is_sort(t_list *a_stack);
#endif
