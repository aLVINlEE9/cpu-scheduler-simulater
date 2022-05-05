/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:03:04 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:28:18 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	rotate(t_list *stack)
{
	t_node	*first;
	t_node	*last;
	t_node	*move;

	first = stack->head->next->next;
	move = stack->head->next;
	last = stack->tail->prev;
	first->prev = stack->head;
	stack->head->next = first;
	last->next = move;
	move->prev = last;
	move->next = stack->tail;
	stack->tail->prev = move;
}

void	reverse_rotate(t_list *stack)
{
	t_node	*first;
	t_node	*last;
	t_node	*move;

	first = stack->head->next;
	move = stack->tail->prev;
	last = stack->tail->prev->prev;
	last->next = stack->tail;
	stack->tail->prev = last;
	first->prev = move;
	move->next = first;
	move->prev = stack->head;
	stack->head->next = move;
}

void	push_pop(t_list *push, t_list *pop)
{
	t_node	*pop_node;
	t_node	*push_node;
	int		poped;

	pop_node = pop->head->next;
	poped = pop_node->data;
	pop->head->next = pop_node->next;
	pop_node->next->prev = pop->head;
	pop_node->next = NULL;
	pop_node->prev = NULL;
	free(pop_node);
	pop->count--;
	push_node = create_node(poped);
	push->head->next->prev = push_node;
	push_node->next = push->head->next;
	push_node->prev = push->head;
	push->head->next = push_node;
	push->count++;
}

void	swap(t_list *stack)
{
	t_node	*first;
	t_node	*second;
	int		tmp;

	first = stack->head->next;
	second = stack->head->next->next;
	tmp = first->data;
	first->data = second->data;
	second->data = tmp;
}
