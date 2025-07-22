#include "philo.h"

int	ft_isdigit(int n)
{
	return (n >= '0' && n <= '9');
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > (unsigned long)LONG_MAX)
			return (-1);
		if (sign == -1 && result > (unsigned long)LONG_MAX + 1)
			return (0);
		i++;
	}
	return (result * sign);
}

int is_positive_digit(char *str)
{
    int i;

	if (!str || !str[0])
        return (0);
    i = 0;
    if (str[0] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
