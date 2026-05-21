/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:54:36 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:54:37 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	single_philo(t_philo *philo)
{
	safe_print(philo, "has taken a fork");
	precise_sleep(philo->data->rules->time_to_die + 1, philo->data);
}

static void	sleep_philo(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_sleep(philo->data->rules->time_to_sleep, philo->data);
}

static void	think(t_philo *philo)
{
	int	n;
	int	think_time;

	safe_print(philo, "is thinking");
	n = philo->data->rules->number_of_philosophers;
	if (n % 2 == 0)
		think_time = 1;
	else
		think_time = philo->data->rules->time_to_eat * (n % 2);
	precise_sleep(think_time, philo->data);
}

void	eat(t_philo *philo)
{
	grab_forks(philo);
	if (is_dead(philo->data))
	{
		drop_forks(philo);
		return ;
	}
	execute_meal(philo);
	drop_forks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->rules->number_of_philosophers == 1)
		return (single_philo(philo), NULL);
	if (philo->id % 2 == 0)
		precise_sleep(data->rules->time_to_eat / 2, data);
	while (!is_dead(data))
	{
		eat(philo);
		if (is_dead(data))
			break ;
		sleep_philo(philo);
		if (is_dead(data))
			break ;
		think(philo);
	}
	return (NULL);
}
