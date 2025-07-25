/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:53:46 by elkharti          #+#    #+#             */
/*   Updated: 2025/07/25 18:06:08 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	monitor_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	meals_counter_mutex;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_mutex_t	is_dead_mutex;
	t_philo			*philos;
};

// Function declarations
int		parse_and_init(t_data *data, int ac, char **av);
int		init_data(t_data *data);
int		start_simulation(t_data *data);
long	get_time_ms(void);
void	ft_usleep(t_philo *philo, long time_in_ms);
void	print_action(t_philo *philo, const char *action);
int		is_positive_digit(char *str);
int		ft_atoi(char *str);
void	*routine(void *arg);
void	*monitor(void *arg);
int		death_checker(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	destroy_all_mutex(t_data *data);
#endif
