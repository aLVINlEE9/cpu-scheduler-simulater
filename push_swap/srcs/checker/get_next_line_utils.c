/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:29:14 by seungsle          #+#    #+#             */
/*   Updated: 2022/03/20 22:17:20 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			size_1;
	size_t			size_2;
	char			*ret;

	if (!s1 && !s2)
		return (NULL);
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (size_1 + size_2 + 1));
	if (!ret)
		return (NULL);
	ft_memmove(ret, s1, size_1);
	ft_memmove(ret + size_1, s2, size_2);
	ret[size_1 + size_2] = '\0';
	free((char *)s1);
	return (ret);
}

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	size_t			i;
	size_t			f;
	unsigned char	*buffer_s;
	unsigned char	*buffer_d;

	i = 0;
	f = 1;
	buffer_d = (unsigned char *)dst;
	buffer_s = (unsigned char *)src;
	if (buffer_d == NULL && buffer_s == NULL)
		return (NULL);
	if (buffer_d > buffer_s)
	{
		f = -1;
		buffer_d += (num - 1);
		buffer_s += (num - 1);
	}
	while (i++ < num)
	{
		*buffer_d = *buffer_s;
		buffer_d += f;
		buffer_s += f;
	}
	return (dst);
}
