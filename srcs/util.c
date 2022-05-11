#include "../includes/cpu_scheduler.h"

void	update_cost_time(t_PCB *pcb)
{
	pcb->cost_time = get_time() - pcb->running_start;
	usleep(50);
}

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
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
