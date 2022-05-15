#include "../includes/cpu_scheduler.h"

void	update_cost_time(t_PCB *pcb)
{
	pcb->cost_time = get_time() - pcb->running_start;
	usleep(10);
	// printf("id%d cost%lld\n", pcb->user_id, pcb->cost_time);
}

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	if (n == 0)
		return ;
	while (i++ < n)
	{
		*ptr++ = 0;
	}
	return ;
}

static void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

static void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_u;

	i = 0;
	s_u = (unsigned char *)s;
	while (i < n)
	{
		if (s_u[i] == (unsigned char)c)
		{
			return ((void *)(s_u + i));
		}
		i++;
	}
	return (NULL);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

static char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	temp;

	i = 0;
	if (!dst && !(char *)src)
		return (0);
	temp = ft_strlen(src);
	if (!size)
		return (temp);
	while (i + 1 < size && (char)src[i])
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (temp);
}

static size_t	ft_num_size(long n)
{
	size_t	i;

	i = 0;
	while (1)
	{
		i++;
		n /= 10;
		if (n == 0)
			break ;
	}
	return (i);
}

static char	*ft_malloc(size_t size)
{
	char		*ret;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*ft_putstr(char *ret, long num, size_t idx, size_t size)
{
	if (num < 0)
	{
		ret[0] = '-';
		num *= -1;
	}
	ret[size] = '\0';
	while (1)
	{
		ret[idx] = '0' + (num % 10);
		num /= 10;
		idx--;
		if (num == 0)
			break ;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	size_t		idx;
	long		num;
	size_t		size;
	char		*ret;

	num = n;
	size = ft_num_size(num);
	if (num < 0)
		size += 1;
	idx = size - 1;
	ret = ft_malloc(size);
	if (!ret)
		return (NULL);
	ret = ft_putstr(ret, num, idx, size);
	return (ret);
}

static char	**ft_malloc_error(char **ret)
{
	int		i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (NULL);
}

static int	ft_idx(char *buf, char c)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while (1)
	{
		if (!*buf)
			break ;
		if (*buf == c)
		{
			buf++;
			continue ;
		}
		tmp = ft_strchr(buf, c);
		if (!(tmp))
		{
			while (*buf++)
				;
			idx++;
			break ;
		}
		idx++;
		buf = tmp + 1;
	}
	return (idx);
}

char	**ft_split(char const *s, char c)
{
	char	*buf;
	char	**ret;
	int		idx;

	idx = 0;
	ret = (char **)ft_calloc((ft_idx((char *)s, c) + 1), sizeof(char *));
	if (!s || !ret)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			buf = (char *)s;
			while (*s && *s != c)
				s++;
			ret[idx] = (char *)malloc(sizeof(char) * (s - buf + 1) + 1);
			if (!ret[idx])
				return (ft_malloc_error(ret));
			ft_strlcpy(ret[idx++], buf, (s - buf + 1));
		}
		else
			s++;
	}
	return (ret);
}

