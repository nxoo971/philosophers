/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 04:10:16 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 04:55:45 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_struct(t_info info)
{
	printf("Number of philo:\t%d\n", info.nbphilo);
	printf("Time to die:\t\t%d\n", info.time_to_die);
	printf("Time to eat:\t\t%d\n", info.time_to_eat);
	printf("Time to sleep:\t\t%d\n", info.time_to_sleep);
	printf("Must eat:\t\t%d\n", info.must_eat);
	printf("Timestamp:\t\t%ld\n", info.timestamp);
}

int	print_status(const char *action, t_philo *philo)
{
	pthread_mutex_lock(& philo->info->print);
	if (someone_is_dead(philo))
	{
		pthread_mutex_unlock(& philo->info->print);
		return (EXIT_FAILURE);
	}
	printf("%li %i %s\n",
		timestamp_to_milliseconds() - philo->info->timestamp,
		philo->index + 1, action);
	pthread_mutex_unlock(& philo->info->print);
	return (EXIT_SUCCESS);
}
