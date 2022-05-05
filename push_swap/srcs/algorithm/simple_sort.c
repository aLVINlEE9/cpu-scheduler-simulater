/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:56:46 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 22:22:04 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sort_2(t_datas *datas)
{
	t_list	*a_stack;
	t_node	*now;

	a_stack = datas->a_stack;
	now = a_stack->head->next;
	if (now->data > now->next->data)
		action_exe(datas, "sa", 1, 1);
}

void	sort_3(t_datas *datas)
{
	t_node	*a;
	t_node	*b;
	t_node	*c;

	a = datas->a_stack->head->next;
	b = a->next;
	c = b->next;
	if (a->data < b->data && b->data > c->data && c->data > a->data)
	{
		action_exe(datas, "rra", 1, 1);
		action_exe(datas, "sa", 1, 1);
	}
	else if (a->data > b->data && b->data > c->data && c->data < a->data)
	{
		action_exe(datas, "ra", 1, 1);
		action_exe(datas, "sa", 1, 1);
	}	
	else if (a->data > b->data && b->data < c->data && c->data > a->data)
		action_exe(datas, "sa", 1, 1);
	else if (a->data < b->data && b->data > c->data && c->data < a->data)
		action_exe(datas, "rra", 1, 1);
	else if (a->data > b->data && b->data < c->data && c->data < a->data)
		action_exe(datas, "ra", 1, 1);
}
