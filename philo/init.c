/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 04:12:48 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 01:19:16 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(pthread_mutex_t *datas, int stop)
{
	int	i;

	i = -1;
	while (++i < stop)
		pthread_mutex_destroy(& datas[i]);
}

static int	init_fork_meal(t_info *info, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(& info->forks[i], 0) != 0
			|| pthread_mutex_init(& info->mutex_meal[i], 0) != 0)
		{
			destroy_mutex(info->forks, i);
			return (!pthread_mutex_destroy(& info->print)
				&& !pthread_mutex_destroy(info->mutex_meal));
		}
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_info *info, int size)
{
	if (pthread_mutex_init(& info->print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(& info->mutex_eat, NULL) != 0)
		return (!pthread_mutex_destroy(& info->print));
	if (pthread_mutex_init(& info->mutex_died, NULL) != 0)
		return (!pthread_mutex_destroy(& info->mutex_died));
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbphilo);
	if (!info->forks)
		return (!pthread_mutex_destroy(& info->print)
			&& !pthread_mutex_destroy(info->mutex_meal));
	info->mutex_meal = malloc(sizeof(pthread_mutex_t) * info->nbphilo);
	if (!info->mutex_meal)
		return (!pthread_mutex_destroy(& info->print)
			&& !pthread_mutex_destroy(info->mutex_meal));
	if (init_fork_meal(info, size))
		return (!pthread_mutex_destroy(& info->print)
			&& pthread_mutex_destroy(info->mutex_meal));
	return (EXIT_SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * info->nbphilo);
	if (!philo)
		return (0);
	i = -1;
	memset(philo, 0, sizeof(t_philo) * info->nbphilo);
	while (++i < info->nbphilo)
	{
		philo[i].index = i;
		philo[i].index_left = philo[i].index;
		if (i == info->nbphilo - 1)
			philo[i].index_right = 0;
		else
			philo[i].index_right = (i + 1);
		philo[i].last_meal = -1;
		philo[i].fork_left = & info->forks[philo[i].index_left];
		philo[i].fork_right = & info->forks[philo[i].index_right];
		philo[i].nb_eat = 0;
		philo[i].info = info;
	}
	return (philo);
}
