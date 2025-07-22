#include "philo.h"

void routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        sleep(0);
	while (!philo->data->is_dead)
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		philo->last_meal = get_time_ms();
		print_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
}


int start_simulation(t_data *data)
{
    int i = 0;
    while (i < data->number_of_philo)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
        i++;
        // sleep(0);
    }
    i = 0;
    while (i < data->number_of_philo)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    return 0;
}


int parse_and_init(t_data *data, int ac, char **av)
{
    int i;

    i = 1;
    while (av[i])
    {    if (!is_positive_digit(av[i]))
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
    return (1);
}
int init_data(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
    data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
    if (!data->forks || !data->philos)
        return (0);
    i = -1;
    while (++i < data->number_of_philo)
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
            return (0);
    i = -1;
    while (++i < data->number_of_philo)
    {
        data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0, data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &data->forks[i + 1];
		data->philos[i].right_fork = &data->forks[(i + 2) % data->number_of_philo];
        data->philos[i].data = data;
    }
    
    data->is_dead = 0;
    data->start_time = get_time();
    return (1);
}

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac != 6)
        return (1);

    if (!parse_and_init(&data, ac, av))
        return (1);
    if (!init_data(&data))
        return (1);
    if (!start_simulation(&data))
        return (1);
    // end_simulation(&data);
    // return (0);
}

