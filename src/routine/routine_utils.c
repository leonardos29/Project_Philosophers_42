/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:55:55 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:55:56 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	grab_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	else
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(first);
	if (is_dead(philo->data))
	{
		pthread_mutex_unlock(first);
		return ;
	}
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
}

void	execute_meal(t_philo *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = now;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo, "is eating");
	precise_sleep(philo->data->rules->time_to_eat, philo->data);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
