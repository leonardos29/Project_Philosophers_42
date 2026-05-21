/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:52:20 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:52:21 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	init_philo_mutexes(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
}

int	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
		{
			set_dead(data);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (0);
		}
		data->created_threads++;
		i++;
	}
	return (1);
}

int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->created_threads)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
		return (clear_all(data), 1);
	if (!start_philos(data))
	{
		set_dead(data);
		pthread_join(*monitor, NULL);
		return (clear_all(data), 1);
	}
	return (0);
}
