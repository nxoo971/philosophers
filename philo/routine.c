/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:55:07 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 00:43:42 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index % 2 == 0)
		usleep(philo->info->time_to_eat * 0.7);
	while (42)
	{
		if (philo->last_meal != -1 && philo->info->nbphilo % 2)
			usleep_(philo->info->time_to_die * 0.25);
		if (take_fork_eat(philo) == EXIT_FAILURE)
			break ;
		if (philo_sleep(philo) == EXIT_FAILURE)
			break ;
		if (print_status("is thinking", philo) == EXIT_FAILURE)
			break ;
	}
	return (0);
}
