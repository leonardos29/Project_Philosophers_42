/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:57:16 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:57:17 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_rules;

typedef struct s_data
{
	t_rules			*rules;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				died;
	int				created_threads;
	long			start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	meal_mutex;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}	t_philo;

int				parsing(t_rules *rules, char **input);
int				validaty_args(char **input);
int				ft_isdigit(int c);
long			ft_atol(const char *nptr);
int				iswhite_space(char c);
int				is_valid_number(char *str);

t_data			*create_data(t_rules *rules);
int				create_philo(t_rules *rules, t_data *data,
					pthread_mutex_t *forks);
pthread_mutex_t	*create_forks(t_rules *rules);

int				start_philos(t_data *data);
int				join_philos(t_data *data);
int				init_philo_mutexes(t_data *data, int count);
void			init_meals(t_data *data);
int				start_simulation(t_data *data, pthread_t *monitor);

void			*routine(void *arg);
void			eat(t_philo *philo);
void			grab_forks(t_philo *philo);
void			execute_meal(t_philo *philo);
void			drop_forks(t_philo *philo);

void			*monitor_routine(void *arg);
int				is_dead(t_data *data);
void			set_dead(t_data *data);

void			safe_print(t_philo *philo, char *msg);
void			print_death(t_philo *philo);
long			get_time(void);
void			precise_sleep(long duration_ms, t_data *data);

void			clear_all(t_data *data);
void			clear_forks(pthread_mutex_t *forks, int n);
void			destroy_mutexs(t_data *data, pthread_mutex_t *mutex1,
					pthread_mutex_t *mutex2);
void			clear_forks_and_dx_mutex(t_data *data);

int				ft_error(const char *err_msg, int exit_code);

#endif
