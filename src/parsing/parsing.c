/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:42:44 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:50:02 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	validaty_args(char **input)
{
	int		i;
	long	nb;

	i = 0;
	while (input[i])
	{
		if (!is_valid_number(input[i]))
			return (0);
		nb = ft_atol(input[i]);
		if (nb <= 0 || nb > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

static void	init_rules(t_rules *rules, char **input)
{
	rules->number_of_philosophers = (int)ft_atol(input[0]);
	rules->time_to_die = (int)ft_atol(input[1]);
	rules->time_to_eat = (int)ft_atol(input[2]);
	rules->time_to_sleep = (int)ft_atol(input[3]);
	if (input[4])
	{
		rules->number_of_times_each_philosopher_must_eat
			= (int)ft_atol(input[4]);
	}
	else
	{
		rules->number_of_times_each_philosopher_must_eat = -1;
	}
}

int	parsing(t_rules *rules, char **input)
{
	if (!validaty_args(input))
		return (1);
	init_rules(rules, input);
	return (0);
}
