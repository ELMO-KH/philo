/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:46 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 18:05:09 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, data) != 0)
		return (0);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}

static void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->monitor_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->meals_counter_mutex, NULL);
	pthread_mutex_init(&data->meals_eaten_mutex, NULL);
	pthread_mutex_init(&data->is_dead_mutex, NULL);
}

int	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->forks || !data->philos)
		return (0);
	(init_mutex(data), data->is_dead = 0, data->start_time = get_time_ms());
	i = 0;
	while (i < data->number_of_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philo];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	parse_and_init(t_data *data, int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (!is_positive_digit(av[i]))
			return (0);
		i++;
	}
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->number_of_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat <= 0))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse_and_init(&data, ac, av))
		return (1);
	if (!init_data(&data))
		return (1);
	if (!start_simulation(&data))
		return (1);
	destroy_all_mutex(&data);
	free(data.forks);
	free(data.philos);
	return (0);
}
