/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:41:55 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/27 04:18:34 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timestamp	get_timestamp(void)
{
	t_timestamp	timestamp;

	gettimeofday(& timestamp, 0);
	return (timestamp);
}

long int	timestamp_to_milliseconds(void)
{
	t_timestamp	timestamp;

	timestamp = get_timestamp();
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

long int	timestamp_to_microseconds(void)
{
	return (get_timestamp().tv_usec);
}

void	usleep_(const long int time_to_sleep)
{
	long	begin;

	begin = timestamp_to_milliseconds();
	while (timestamp_to_milliseconds() - begin < time_to_sleep)
		usleep(10);
}
