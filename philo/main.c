/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:10:49 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 01:21:48 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	memdelarr(void **ptr, int size)
{
	while (--size >= 0)
		ft_memdel((void **)& ptr[size]);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	static t_info	info = {.must_eat = -1, 0};
	static t_philo	*philo = {0};
	int				i;

	if (ac < 5 || ac > 6)
		return (0);
	if (parse_av(ac, av, & info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex(& info, info.nbphilo) == EXIT_FAILURE)
		return (memdelarr((void *[2]){info.mutex_meal, info.forks}, 2));
	philo = init_philo(& info);
	if (!philo)
		return (memdelarr((void *[3])
				{philo, info.forks, info.mutex_meal}, 3));
	info.timestamp = timestamp_to_milliseconds();
	i = -1;
	while (++i < info.nbphilo)
		pthread_create(& philo[i].thread, NULL, & routine, & philo[i]);
	watchers(& info, philo);
	i = -1;
	while (++i < info.nbphilo)
		pthread_join(philo[i].thread, 0);
	destroy_mutex(info.forks, info.nbphilo);
	return (!memdelarr((void *[3])
			{philo, info.forks, info.mutex_meal}, 3));
}
