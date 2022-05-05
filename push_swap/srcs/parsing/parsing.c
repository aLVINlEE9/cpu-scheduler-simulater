/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:04:20 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 18:30:28 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	init_datas(t_datas *datas)
{
	datas->b_acts.a[0] = 0;
	datas->b_acts.a[1] = 0;
	datas->b_acts.b[0] = 0;
	datas->b_acts.b[1] = 0;
	datas->exe_acts.a[0] = 0;
	datas->exe_acts.a[1] = 0;
	datas->exe_acts.b[0] = 0;
	datas->exe_acts.b[1] = 0;
	datas->exe_acts.r[0] = 0;
	datas->exe_acts.r[1] = 0;
	datas->exe_acts.count = INT_MAX;
}

void	parsing(t_datas *datas, int argc, char **argv)
{
	if (argc == 1)
		exit(exception_print("there is no input value"));
	init_datas(datas);
	create_stack(datas);
	if (split_to_stack(argv, datas->a_stack, 1))
		exit(free_list(datas->a_stack) && free_list(datas->b_stack));
}
