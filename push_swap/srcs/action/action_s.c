/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:27:40 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:28:14 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sa(t_datas *datas, int cnt)
{
	t_list	*a_stack;
	int		i;

	a_stack = datas->a_stack;
	i = -1;
	if (a_stack->count > 1)
		while (++i < cnt)
			swap(a_stack);
}

void	sb(t_datas *datas, int cnt)
{
	t_list	*b_stack;
	int		i;

	b_stack = datas->b_stack;
	i = -1;
	if (b_stack->count > 1)
		while (++i < cnt)
			swap(b_stack);
}

void	ss(t_datas *datas, int cnt)
{
	if (datas->a_stack->count > 1 && datas->b_stack->count > 1)
	{
		sa(datas, cnt);
		sb(datas, cnt);
	}
}
