/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:32:35 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:31:04 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	isin_max(t_list *stack, int data)
{
	if (stack->max[0] == data || stack->max[1] == data || stack->max[2] == data)
		return (1);
	return (0);
}

int	get_max_value(t_list *stack, int threshold)
{
	t_node	*now;
	int		tmp;

	now = stack->head->next;
	tmp = INT_MIN;
	while (now != stack->tail)
	{
		if (tmp < now->data && now->data < threshold)
			tmp = now->data;
		now = now->next;
	}
	return (tmp);
}

void	set_max_array(t_list *stack)
{
	stack->max[0] = get_max_value(stack, INT_MAX);
	stack->max[1] = get_max_value(stack, stack->max[0]);
	stack->max[2] = get_max_value(stack, stack->max[1]);
}

void	set_min_value(t_list *stack)
{
	t_node	*now;
	int		tmp;

	now = stack->head->next;
	tmp = INT_MAX;
	while (now != stack->tail)
	{
		if (tmp > now->data)
			tmp = now->data;
		now = now->next;
	}
	stack->min = tmp;
}
