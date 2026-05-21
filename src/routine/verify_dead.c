/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_dead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:54:57 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:54:58 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	is_dead(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death_mutex);
	res = data->died;
	pthread_mutex_unlock(&data->death_mutex);
	return (res);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

static int	check_philo_status(t_data *data, int i, int *all_finished)
{
	long	time_since_meal;
	int		meals;
	int		must_eat;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	time_since_meal = get_time() - data->philos[i].last_meal;
	meals = data->philos[i].meals_eaten;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	must_eat = data->rules->number_of_times_each_philosopher_must_eat;
	if (must_eat != -1 && meals < must_eat)
		*all_finished = 0;
	if (time_since_meal >= data->rules->time_to_die)
	{
		print_death(&data->philos[i]);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_finished;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		all_finished = 1;
		i = 0;
		while (i < data->rules->number_of_philosophers)
		{
			if (check_philo_status(data, i, &all_finished))
				return (NULL);
			i++;
		}
		if (data->rules->number_of_times_each_philosopher_must_eat != -1
			&& all_finished)
		{
			set_dead(data);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
