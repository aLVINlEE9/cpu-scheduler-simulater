/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:11:23 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/21 00:10:52 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
Function Explanation (merge_best_actions)

	1. calculate rra, rrb
	2. merge_best_actions_sub() 
		parameter : (datas, 0, 0) => ra, rb
					(datas, 0, 1) => ra, rrb
					(datas, 1, 0) => rra, rb
					(datas, 1, 1) => rra, rrb
*/

void	merge_best_actions(t_datas *datas)
{
	t_list				*a_stack;
	t_list				*b_stack;

	a_stack = datas->a_stack;
	b_stack = datas->b_stack;
	datas->b_acts.a[1] = a_stack->count - datas->b_acts.a[0];
	datas->b_acts.b[1] = b_stack->count - datas->b_acts.b[0];
	merge_best_actions_sub(datas, 0, 0);
	merge_best_actions_sub(datas, 0, 1);
	merge_best_actions_sub(datas, 1, 0);
	merge_best_actions_sub(datas, 1, 1);
}

/*
Function Explanation (choose_best_actinos)

	parameter : (int)`DATA` == a_stack top(7)
				`B_STACK->MIN` == min vlaue from b_stack(2)
				tmp == temporaray value to find max value
	
	1. while -> case 1) count max value from top of b_stack
	
					{`B_STACK->MIN` > `DATA`} : If this condition is true, 
					It means the `DATA` from a_stack is minimum value 
					compare with all b_stack numbers
					-> It just need to sort descending order
					{now->data >= tmp} : just sort b_stack descending order
					
					
				case 2) count the right place (which `DATA` is going to be)
						from top of b_stack
					
					{`B_STACK->MIN` < `DATA`} : If this condition is true,
					It means there's value in b_stack that is less than `DATA` 
					-> Need to find the number that is less than `DATA` but 
					biggest number of them
					{now->data >= tmp} : This condition is to find biggest number
					{now->data < `DATA`} : This condition is to limit the biggest
					number to not over the `DATA`

		-------------------------
		|			|			|
		|			|			|
		|	*	7	|			|
		|		3	|			|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		--------------------------	pb
		-------------------------
		|			|			|
		|			|			|
		|			|			|
		|	*	3	|		7	|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		-------------------------- rb - pb
		-------------------------
		|			|			|
		|			|			|
		|			|		3	|
		|			|		2	|
		|	*	5	|		9	|
		|			|		7	|
		|	a_stack	|	b_stack	|
		-------------------------- pb
	
	2. merge_best_actions : compare all available commands and make it most 
							efficient way
*/

void	choose_best_actions_sub(t_datas *datas, int data)
{
	t_node			*now;
	int				tmp;
	int				i;

	now = datas->b_stack->head->next;
	tmp = INT_MIN;
	i = 0;
	while (now != datas->b_stack->tail && ++i)
	{
		if (datas->b_stack->min > data && now->data >= tmp)
		{
			tmp = now->data;
			datas->b_acts.b[0] = i - 1;
		}
		if (datas->b_stack->min < data && now->data >= tmp && now->data < data)
		{
			tmp = now->data;
			datas->b_acts.b[0] = i - 1;
		}
		now = now->next;
	}
	merge_best_actions(datas);
}

/*
Function Explanation (choose_best_actinos)

	1. set_min_value : get min number in b_stack (It will be 2)
	2. while -> count all command(ra, rra) for each numbers in a_stack 
		that makes to be top which is gonna pb.

		-------------------------
		|			|			|
		|			|			|
		|	*	7	|			|
		|		3	|			|
		|		5	|		2	|
		|			|		9	|
		|	a_stack	|	b_stack	|
		--------------------------

		(if now->data is 7 then RA is gonna be 0 times, but RRA is gonna be 3 times)
		
		a. save RA RRA count temporary in t_best_actions struct

		b. choose_best_actions_sub : count command(rb, rrb) from b_stack
*/

void	choose_best_actions(t_datas *datas)
{
	t_list			*a_stack;
	t_node			*now;
	int				cnt;

	a_stack = datas->a_stack;
	now = a_stack->head->next;
	cnt = -1;
	set_min_value(datas->b_stack);
	while (++cnt < a_stack->count)
	{
		datas->b_acts.a[0] = cnt;
		choose_best_actions_sub(datas, now->data);
		now = now->next;
	}
}

/*
Function Explanation (insertion_sort)

	1. PB 2 times : move two top numbers(9, 2) in a_stack to b_stack

		-------------------------
		|			|			|
		|			|			|
		|		7	|			|
		|		3	|		2	|
		|		5	|		9	|
		|			|			|
		|	a_stack	|	b_stack	|
		--------------------------

	2. while -> (condition : until a_stack->count is 0)
				a. init_datas : initialize variables
				b. choose_best_actions : choosing best actions that makes least time
					complexity
				c. exe_best_actions : after choose_best_actions() exe_acts struct
					is gonna fill with best actions. exe_best_actions() is gonna 
					execute actions which was in exe_acts struct.
				d. action_exe(datas, "pb", 1, 1) : when actions are done. execute
					pb.
	
	(If RA is like 3 times and RB is like 4 times, it's totally 7 times but
	if you use this function then it merge commands effiectly and the result
	will be totally 4 times(better than 7) cause, {RA 3 RB 3} -> RR 3, RB 1)
*/

void	insertion_sort(t_datas *datas)
{
	t_list	*a_stack;

	a_stack = datas->a_stack;
	action_exe(datas, "pb", 2, 1);
	while (a_stack->count)
	{
		init_datas(datas);
		choose_best_actions(datas);
		exe_best_actions(datas);
		action_exe(datas, "pb", 1, 1);
	}
	init_datas(datas);
	choose_best_actions_sub(datas, INT_MIN);
	exe_best_actions(datas);
	action_exe(datas, "pa", datas->b_stack->count, 1);
}
