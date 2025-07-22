#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int             id;
	int             meals_eaten;
	long long       last_meal;
	pthread_t       thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data          *data;
}              t_philo;

typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;

	int             is_dead;
	long long       start_time;

	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	int 			meal_mutex;
	t_philo         *philos;
}               t_data;

/* philo.c */
int parse_and_init(t_data *data, int ac, char **av);

/* utils.c */
int	ft_atoi(const char *str);
long	get_time(void);
int is_positive_digit(char *str);
int	ft_isdigit(int n);
void routine(void *arg);
void print_action(t_philo *philo, char *action);
void	*monitor(void *arg);
// void think(t_philo *philo);
// void take_forks(t_philo *philo);
// void eat(t_philo *philo);
// void put_forks(t_philo *philo);
// void sleep_philo(t_philo *philo);

#endif