/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:38 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 11:46:22 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (result > (2147483647 - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i++] - '0');
	}
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (-1);
	return ((int)result);
}
