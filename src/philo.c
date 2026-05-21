/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:42:03 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:42:04 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_data		*data;
	pthread_t	monitor;

	if (!(argc == 5 || argc == 6))
		return (ft_error("Invalid number of arguments", 2));
	if (parsing(&rules, argv + 1) == 1)
		return (ft_error("Error\n", 1));
	data = create_data(&rules);
	if (!data)
		return (1);
	data->start_time = get_time();
	init_meals(data);
	if (start_simulation(data, &monitor))
		return (1);
	join_philos(data);
	pthread_join(monitor, NULL);
	clear_all(data);
	return (0);
}
