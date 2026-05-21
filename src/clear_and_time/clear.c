/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:56:18 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:56:19 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	free_mutexes(t_data *data, int n)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < n)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = 0;
		while (i < n)
			pthread_mutex_destroy(&data->philos[i++].meal_mutex);
		free(data->philos);
	}
}

void	clear_all(t_data *data)
{
	int	n;

	if (!data)
		return ;
	n = data->rules->number_of_philosophers;
	free_mutexes(data, n);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data);
}

void	clear_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}

void	destroy_mutexs(t_data *data, pthread_mutex_t *mutex1,
		pthread_mutex_t *mutex2)
{
	pthread_mutex_destroy(mutex1);
	if (mutex2)
		pthread_mutex_destroy(mutex2);
	free(data);
}

void	clear_forks_and_dx_mutex(t_data *data)
{
	clear_forks(data->forks, data->rules->number_of_philosophers);
	destroy_mutexs(data, &data->print_mutex, &data->death_mutex);
}
