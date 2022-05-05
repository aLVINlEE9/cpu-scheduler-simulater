/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:22:45 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 22:22:37 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_u;
	unsigned char	*s2_u;

	i = 0;
	s1_u = (unsigned char *)s1;
	s2_u = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*s1_u && *s2_u && i++ < n - 1)
	{
		if (*s1_u != *s2_u)
		{
			return (*s1_u - *s2_u);
		}
		s1_u++;
		s2_u++;
	}
	return (*s1_u - *s2_u);
}

void	print_action(char *action, int cnt)
{
	while (cnt--)
	{
		write(1, action, ft_strlen(action));
		write(1, "\n", 1);
	}
}

void	action_exe(t_datas *datas, char *action, int cnt, int print)
{
	if (ft_strncmp(action, "ra", 3) == 0)
		ra(datas, cnt);
	else if (ft_strncmp(action, "rb", 3) == 0)
		rb(datas, cnt);
	else if (ft_strncmp(action, "rr", 3) == 0)
		rr(datas, cnt);
	else if (ft_strncmp(action, "rra", 3) == 0)
		rra(datas, cnt);
	else if (ft_strncmp(action, "rrb", 3) == 0)
		rrb(datas, cnt);
	else if (ft_strncmp(action, "rrr", 3) == 0)
		rrr(datas, cnt);
	else if (ft_strncmp(action, "pa", 3) == 0)
		pa(datas, cnt);
	else if (ft_strncmp(action, "pb", 3) == 0)
		pb(datas, cnt);
	else if (ft_strncmp(action, "sa", 3) == 0)
		sa(datas, cnt);
	else if (ft_strncmp(action, "sb", 3) == 0)
		sb(datas, cnt);
	else if (ft_strncmp(action, "ss", 3) == 0)
		ss(datas, cnt);
	if (print)
		print_action(action, cnt);
}

void	exe_best_actions(t_datas *datas)
{
	t_exe_acts	exe_acts;

	exe_acts = datas->exe_acts;
	if (exe_acts.a[0] != -1)
		action_exe(datas, "ra", exe_acts.a[0], 1);
	if (exe_acts.a[1] != -1)
		action_exe(datas, "rra", exe_acts.a[1], 1);
	if (exe_acts.b[0] != -1)
		action_exe(datas, "rb", exe_acts.b[0], 1);
	if (exe_acts.b[1] != -1)
		action_exe(datas, "rrb", exe_acts.b[1], 1);
	if (exe_acts.r[0] != -1)
		action_exe(datas, "rr", exe_acts.r[0], 1);
	if (exe_acts.r[1] != -1)
		action_exe(datas, "rrr", exe_acts.r[1], 1);
}
