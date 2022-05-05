/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:25:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:27:59 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	pa(t_datas *datas, int cnt)
{
	t_list	*a_stack;
	t_list	*b_stack;
	int		i;

	a_stack = datas->a_stack;
	b_stack = datas->b_stack;
	i = -1;
	if (b_stack->count != 0)
		while (++i < cnt)
			push_pop(a_stack, b_stack);
}

void	pb(t_datas *datas, int cnt)
{
	t_list	*a_stack;
	t_list	*b_stack;
	int		i;

	a_stack = datas->a_stack;
	b_stack = datas->b_stack;
	i = -1;
	if (a_stack->count != 0)
		while (++i < cnt)
			push_pop(b_stack, a_stack);
}
