/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:37:38 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 01:19:59 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//static?
int	unlock(pthread_mutex_t **fork, int size)
{
	while (--size >= 0)
		pthread_mutex_unlock(fork[size]);
	return (EXIT_FAILURE);
}

static int	ate_everything(t_philo *philo)
{
	if (philo->nb_eat == philo->info->must_eat)
	{
		pthread_mutex_lock(& philo->info->mutex_eat);
		philo->info->leaved++;
		return (unlock((pthread_mutex_t *[3])
				{philo->fork_right, philo->fork_left,
					& philo->info->mutex_eat}, 3));
	}
	return (EXIT_SUCCESS);
}

static int	take_fork(t_philo *philo, pthread_mutex_t *forks[2])
{
	const int		modulo = philo->index % 2 > 0;

	pthread_mutex_lock(forks[modulo]);
	if (print_status("has taken a fork", philo) || forks[0] == forks[1])
	{
		pthread_mutex_lock(& philo->info->mutex_meal[philo->index]);
		philo->last_meal = timestamp_to_milliseconds();
		pthread_mutex_unlock(& philo->info->mutex_meal[philo->index]);
		return (unlock((pthread_mutex_t *[1]){forks[modulo]}, 1));
	}
	pthread_mutex_lock(forks[!modulo]);
	if (print_status("has taken a fork", philo))
		return (unlock(forks, 2));
	return (EXIT_SUCCESS);
}

int	take_fork_eat(t_philo *philo)
{
	pthread_mutex_t	*forks[2];

	forks[0] = philo->fork_right;
	forks[1] = philo->fork_left;
	if (take_fork(philo, forks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(& philo->info->mutex_meal[philo->index]);
	philo->last_meal = timestamp_to_milliseconds();
	pthread_mutex_unlock(& philo->info->mutex_meal[philo->index]);
	philo->nb_eat++;
	if (print_status("is eating", philo))
		return (unlock(forks, 2));
	usleep_(philo->info->time_to_eat);
	if (ate_everything(philo))
		return (EXIT_FAILURE);
	return (!unlock(forks, 2));
}

int	philo_sleep(t_philo *philo)
{
	if (print_status("is sleeping", philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	usleep_(philo->info->time_to_sleep);
	if (philo->nb_eat == philo->info->must_eat)
	{
		pthread_mutex_lock(& philo->info->mutex_eat);
		philo->info->leaved++;
		return (unlock((pthread_mutex_t *[3])
				{philo->fork_right, philo->fork_left,
					& philo->info->mutex_eat}, 3));
	}
	return (EXIT_SUCCESS);
}
