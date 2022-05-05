/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:14:18 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 22:23:44 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	is_sort(t_list *a_stack)
{
	t_node	*now;
	int		tmp;

	tmp = INT_MIN;
	now = a_stack->head->next;
	while (now != a_stack->tail)
	{
		if (tmp < now->data)
			tmp = now->data;
		else
			return (0);
		now = now->next;
	}
	return (1);
}

void	checker(t_datas *datas)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line, 1) > 0)
	{
		action_exe(datas, line, 1, 0);
		free(line);
	}
	free(line);
	if (is_sort(datas->a_stack))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int argc, char **argv)
{
	t_datas	datas;

	parsing(&datas, argc, argv);
	checker(&datas);
}
