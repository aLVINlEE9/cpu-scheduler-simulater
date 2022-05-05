/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:10:21 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:30:07 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	exception_print(char *str)
{
	write(1, "[Exception Occurred : ", 22);
	write(1, str, (int)ft_strlen(str));
	write(1, "]", 1);
	return (1);
}

int	exception_parsing_string(char *buf)
{
	int	i;

	i = 1;
	if (buf[0] == '0' && buf[1] != '\0')
		return (exception_print("zero cannot be first place"));
	else if ((buf[0] < '0' || buf[0] > '9') && buf[0] != '-')
		return (exception_print("one of input value is not a number"));
	if (buf[0] == '-')
	{
		if (buf[1] == '0')
			return (exception_print("zero cannot be first place"));
		else if (buf[1] == '\0')
			return (exception_print("one of input value is not a number"));
	}
	while (buf[i])
	{
		if (buf[i] < '0' || buf[i] > '9')
			return (exception_print("one of input value is not a number"));
		if (i > 10)
			return (exception_print("one of input value is not in \
			integer interval"));
		i++;
	}
	return (0);
}

int	exception_parsing_number(long long buf)
{
	if (!(buf >= INT_MIN && buf <= INT_MAX))
		return (exception_print("one of input value is not in \
		integer interval"));
	return (0);
}

int	check_sort(t_list *stack)
{
	t_node	*now;
	int		cnt;

	now = stack->head->next;
	cnt = -1;
	while (++cnt < stack->count - 1)
	{
		if (now->data > now->next->data)
			return (0);
		now = now->next;
	}
	return (1);
}

int	exception_parsing_sort(t_list *a_stack)
{
	t_node	*now;
	t_node	*tmp;
	int		i;
	int		j;

	if (check_sort(a_stack))
		return (exception_print("input values are already sorted"));
	now = a_stack->head->next;
	i = -1;
	while (++i < a_stack->count - 1)
	{
		j = i;
		tmp = now->next;
		while (j < a_stack->count - 1)
		{
			if (now->data == tmp->data)
				return (exception_print("there are same numbers \
				in input values"));
			tmp = tmp->next;
			j++;
		}
		now = now->next;
	}
	return (0);
}
