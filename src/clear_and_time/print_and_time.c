/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:56:47 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:56:48 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->died)
	{
		printf("%ld %d %s\n",
			get_time() - philo->data->start_time,
			philo->id,
			msg);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->died)
	{
		philo->data->died = 1;
		printf("%ld %d died\n",
			get_time() - philo->data->start_time,
			philo->id);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_error(const char *err_msg, int exit_code)
{
	size_t	len;

	len = 0;
	while (err_msg[len])
		len++;
	write(2, err_msg, len);
	return (exit_code);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long duration_ms, t_data *data)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < duration_ms)
	{
		if (is_dead(data))
			return ;
		usleep(200);
	}
}
