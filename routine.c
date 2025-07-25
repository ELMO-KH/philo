/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:25:15 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 18:26:55 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

static void	eating_process(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->time_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->time_mutex);
	pthread_mutex_lock(&philo->data->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_eaten_mutex);
	ft_usleep(philo, philo->data->time_to_eat);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_usleep(philo, philo->data->time_to_die);
		pthread_mutex_lock(&philo->data->is_dead_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->is_dead_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d is dead\n", get_time_ms()
			- philo->data->start_time,
			philo->data->philos[0].id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	else
	{
		eating_process(philo);
		unlock_forks(philo);
	}
}

static void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (death_checker(philo))
			break ;
		philo_think(philo);
		if (death_checker(philo))
			break ;
		philo_eat(philo);
		if (death_checker(philo))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
