/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 04:11:50 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/27 06:30:52 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	full_digit(char *av)
{
	char	*s;

	s = av;
	while (*s && *s >= '0' && *s <= '9')
		s++;
	return (*s != '\0');
}

int	parse_av(int ac, char **av, t_info *info)
{
	info->nbphilo = ft_atoi(av[NBPHILO]);
	info->time_to_die = ft_atoi(av[TIME_TO_DIE]);
	info->time_to_eat = ft_atoi(av[TIME_TO_EAT]);
	info->time_to_sleep = ft_atoi(av[TIME_TO_SLEEP]);
	if (full_digit(av[NBPHILO]) || full_digit(av[TIME_TO_DIE])
		|| full_digit(av[TIME_TO_EAT]) || full_digit(av[TIME_TO_SLEEP]))
		return (EXIT_FAILURE);
	if (info->nbphilo <= 0 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (ac == 6)
	{
		info->must_eat = ft_atoi(av[MUST_EAT]);
		if (info->must_eat <= 0 || full_digit(av[MUST_EAT]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
