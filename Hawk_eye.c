/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hawk_eye.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:54 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 18:35:12 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead_mutex);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->is_dead_mutex);
	return (0);
}

static void	monitor_print(t_data *data, int i, int mode)
{
	if (mode == 1)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d is dead\n", get_time_ms() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("safi lfalasifa chab3o \n");
		pthread_mutex_unlock(&data->print_mutex);
	}
}

static int	monitor_check_death(t_data *data)
{
	int			i;
	long		current_time;
	long		last_meal_time;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->time_mutex);
		last_meal_time = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->time_mutex);
		current_time = get_time_ms();
		if (current_time - last_meal_time >= data->time_to_die)
		{
			pthread_mutex_lock(&data->is_dead_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->is_dead_mutex);
			monitor_print(data, i, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philosopher_meals_checker(t_data *data)
{
	int	i;
	int	count;
	int	meals_eaten;

	i = 0;
	count = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->meals_eaten_mutex);
		meals_eaten = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meals_eaten_mutex);
		if (meals_eaten == data->must_eat)
		{
			pthread_mutex_lock(&data->meals_counter_mutex);
			count++;
			pthread_mutex_unlock(&data->meals_counter_mutex);
		}
		i++;
	}
	return (count);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (death_checker(&data->philos[0]))
			break ;
		if (monitor_check_death(data))
			return (NULL);
		if (data->must_eat > 0)
		{
			if (philosopher_meals_checker(data) >= data->number_of_philo)
			{
				pthread_mutex_lock(&data->is_dead_mutex);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->is_dead_mutex);
				monitor_print(data, 0, 0);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}
