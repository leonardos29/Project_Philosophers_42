/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardos_souza <leonardos_souza@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:45:39 by leonardos_s       #+#    #+#             */
/*   Updated: 2026/05/21 04:50:06 by leonardos_s      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	iswhite_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	res;

	while (iswhite_space(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	res = 0;
	while (ft_isdigit(*nptr))
	{
		if (res > (2147483647 - (*nptr - '0')) / 10)
			return (2147483648L);
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (iswhite_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (iswhite_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
