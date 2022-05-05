/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:52:46 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:30:12 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	free_list(t_list *stack)
{
	t_node	*now;
	t_node	*tmp;

	now = stack->head;
	while (now != NULL)
	{
		tmp = now;
		free(tmp);
		now = now->next;
	}
	free(stack);
	return (1);
}

int	free_stack(t_list *stack)
{
	free(stack);
	return (1);
}

int	free_node(t_node *node)
{
	free(node);
	return (1);
}
