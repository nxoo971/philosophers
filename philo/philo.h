/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 08:11:08 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/28 01:19:22 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define NBPHILO		1
# define TIME_TO_DIE	2
# define TIME_TO_EAT	3
# define TIME_TO_SLEEP	4
# define MUST_EAT		5

typedef struct timeval	t_timestamp;

typedef struct s_info
{
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	*mutex_meal;
	pthread_mutex_t	mutex_died;
	pthread_mutex_t	*forks;
	long int		timestamp;
	int				nbphilo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				leaved;
	int				someone_is_dead;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thread;
	long int		last_meal;
	int				nb_eat;
	int				taken_left;
	int				taken_right;
	int				is_dead;
	int				index;
	int				index_left;
	int				index_right;
}	t_philo;

//	ft_atoi.c
int			ft_atoi(const char *str);
//	parser.c
int			parse_av(int ac, char **av, t_info *info);
//	init.c
int			init_mutex(t_info *info, int size);
t_philo		*init_philo(t_info *info);
//	time.c
t_timestamp	get_timestamp(void);
long int	timestamp_to_milliseconds(void);
long int	timestamp_to_microseconds(void);
void		usleep_(const long int time_to_sleep);
//	watchers.c
void		watchers(t_info *info, t_philo *philo);
int			someone_is_dead(t_philo *philo);
//	print.c
void		print_struct(t_info info);
int			print_status(const char *action, t_philo *philo);
//	routine.c
void		*routine(void *data);
int			philo_sleep(t_philo *philo);
//	actions.c
int			take_fork_eat(t_philo *philo);
//	free.c
void		ft_memdel(void **ptr);
void		destroy_mutex(pthread_mutex_t *info, int stop);

#endif
