/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:27 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 18:38:22 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!death_checker(philo))
	{
		printf("%ld %d %s\n",
			get_time_ms() - philo->data->start_time,
			philo->id,
			action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	destroy_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->monitor_mutex);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->meals_counter_mutex);
	pthread_mutex_destroy(&data->meals_eaten_mutex);
	pthread_mutex_destroy(&data->is_dead_mutex);
}
