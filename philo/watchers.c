/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:32:05 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 04:55:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	someone_is_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(& philo->info->mutex_died);
	res = philo->info->someone_is_dead;
	pthread_mutex_unlock(& philo->info->mutex_died);
	return (res);
}

static int	timestamp_greather_than_timetodie(
	t_info *info, int last_meal, int timestamp, int index_philo)
{
	if (last_meal != -1 && timestamp >= info->time_to_die)
	{
		pthread_mutex_lock(& info->mutex_died);
		info->someone_is_dead = 1;
		pthread_mutex_unlock(& info->mutex_died);
		pthread_mutex_lock(& info->print);
		printf("%ld %d died\n", timestamp_to_milliseconds() - info->timestamp,
			index_philo + 1);
		pthread_mutex_unlock(& info->print);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	dojob(t_info *info, t_philo *philo)
{
	long int	timestamp;
	long int	last_meal;
	int			i;
	int			nb;

	i = -1;
	nb = philo->info->nbphilo;
	last_meal = 0;
	timestamp = 0;
	while (++i < nb)
	{
		pthread_mutex_lock(& info->mutex_meal[i]);
		timestamp = timestamp_to_milliseconds() - philo[i].last_meal;
		last_meal = philo[i].last_meal;
		pthread_mutex_unlock(& info->mutex_meal[i]);
		if (timestamp_greather_than_timetodie(info, last_meal, timestamp, i))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	watchers(t_info *info, t_philo *philo)
{
	while (42)
	{
		if (dojob(info, philo))
			return ;
		pthread_mutex_lock(&info->mutex_eat);
		if (info->leaved == info->nbphilo)
		{
			pthread_mutex_unlock(&info->mutex_eat);
			break ;
		}
		pthread_mutex_unlock(&info->mutex_eat);
		usleep(100);
	}
}
