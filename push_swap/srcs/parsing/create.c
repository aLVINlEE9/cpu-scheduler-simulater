/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:31:52 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:30:03 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	init_stack(t_list *stack)
{
	stack->count = 0;
	stack->max[0] = 0;
	stack->max[1] = 0;
	stack->max[2] = 0;
	stack->min = 0;
}

int	create_list(t_list *stack)
{
	t_node	*head;
	t_node	*tail;

	stack->head = (t_node *)malloc(sizeof(t_node));
	if (stack->head == NULL)
		return (exception_print("haed malloc failed"));
	stack->tail = (t_node *)malloc(sizeof(t_node));
	if (stack->tail == NULL)
		return (exception_print("tail malloc failed") && \
		free_node(stack->head));
	head = stack->head;
	tail = stack->tail;
	head->data = 0;
	tail->data = 0;
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = head;
	return (0);
}

void	create_stack(t_datas *datas)
{
	datas->a_stack = (t_list *)malloc(sizeof(t_list));
	if (datas->a_stack == NULL)
		exit(exception_print("a_stack malloc failed"));
	if (create_list(datas->a_stack))
		exit(free_stack(datas->a_stack));
	init_stack(datas->a_stack);
	datas->b_stack = (t_list *)malloc(sizeof(t_list));
	if (datas->b_stack == NULL)
		exit(exception_print("b_stack malloc failed") && \
		free_list(datas->a_stack));
	if (create_list(datas->b_stack))
		exit(free_list(datas->a_stack) && free_stack(datas->b_stack));
	init_stack(datas->b_stack);
}
