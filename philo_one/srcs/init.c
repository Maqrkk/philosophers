/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 08:40:41 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 08:21:12 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>
#include <pthread.h>

/*
**	This function initializes certain values to NULL for safety.
*/

static void		make_empty(t_group *group, t_data *data)
{
	group->philosophers = NULL;
	data->philo_threads = NULL;
	data->forks = NULL;
}

/*
**	Allocates and initializes all philosophers and their threads.
**	Will print an error if it fails.
*/

void			init_philosophers(t_group *group, t_data *data, int num)
{
	unsigned long	time;
	int				i;

	make_empty(group, data);
	group->philosophers = malloc(sizeof(t_philosopher) * num);
	if (group->philosophers == NULL)
		write_error("A malloc failed while allocating philosophers.\n", data);
	data->philo_threads = malloc(sizeof(pthread_t) * num);
	if (data->philo_threads == NULL)
		write_error("A malloc failed while allocating threads.\n", data);
	if (data->error)
		return ;
	group->num_philosophers = data->num_philosophers;
	group->death_lock = &data->death_lock;
	time = current_time();
	i = 0;
	while (i < data->num_philosophers)
	{
		group->philosophers[i].num = i + 1;
		group->philosophers[i].last_time_eaten = time;
		group->philosophers[i].times_eaten = 0;
		group->philosophers[i].data = data;
		i++;
	}
}

/*
**	This function initializes all the mutexes.
*/

void			init_locks(t_data *data)
{
	int				i;
	int				ret;

	if (data->error)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (data->forks == NULL)
	{
		write_error("A malloc failed while allocating mutexes.\n", data);
		return ;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		ret = pthread_mutex_init(data->forks + i, NULL);
		if (ret)
			write_error("Initialising a mutex failed.\n", data);
		i++;
	}
	ret = pthread_mutex_init(&data->write_lock, NULL);
	if (ret)
		write_error("Initialising a mutex failed.\n", data);
	ret = pthread_mutex_init(&data->death_lock, NULL);
	if (ret)
		write_error("Initialising a mutex failed.\n", data);
}
