/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:51:06 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:51:07 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	init_philo_data(
	t_philo *philo,
	t_data *data,
	pthread_mutex_t *forks,
	int i)
{
	int	n_philo;

	n_philo = data->rules->number_of_philosophers;
	philo->id = i + 1;
	philo->l_fork = &forks[i];
	philo->r_fork = &forks[(i + 1) % n_philo];
	philo->last_meal = data->start_time;
	philo->meals_eaten = 0;
	philo->data = data;
}

int	create_philo(t_rules *rules, t_data *data, pthread_mutex_t *forks)
{
	int	i;
	int	n_philo;

	n_philo = rules->number_of_philosophers;
	data->philos = malloc(sizeof(t_philo) * n_philo);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < n_philo)
	{
		init_philo_data(&data->philos[i], data, forks, i);
		i++;
	}
	if (!init_philo_mutexes(data, n_philo))
	{
		free(data->philos);
		data->philos = NULL;
		return (0);
	}
	return (1);
}

pthread_mutex_t	*create_forks(t_rules *rules)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t)
			* rules->number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static int	init_data_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		destroy_mutexs(data, &data->print_mutex, NULL);
		return (0);
	}
	return (1);
}

t_data	*create_data(t_rules *rules)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->rules = rules;
	data->philos = NULL;
	data->forks = NULL;
	data->died = 0;
	data->created_threads = 0;
	data->start_time = 0;
	if (!init_data_mutexes(data))
		return (free(data), NULL);
	data->forks = create_forks(rules);
	if (!data->forks)
	{
		destroy_mutexs(data, &data->print_mutex, &data->death_mutex);
		return (NULL);
	}
	if (!create_philo(rules, data, data->forks))
	{
		clear_forks_and_dx_mutex(data);
		return (NULL);
	}
	return (data);
}
