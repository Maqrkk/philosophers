/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 14:37:56 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/02 11:00:31 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>

/*
**	This function initializes certain values to NULL for safety.
*/

static void		make_empty(t_group *group, t_data *data)
{
	group->philosophers = NULL;
	data->philo_threads = NULL;
}

/*
**	Allocates and initializes all philosophers. Will print an error and exit
**	if it fails.
*/

void			init_philosophers(t_group *group, t_data *data, int num)
{
	int				i;
	unsigned long	time;

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
**	This function initializes all the semaphores.
*/

void			init_locks(t_data *data)
{
	if (data->error)
		return ;
	data->forks = sem_open("philo_forks", O_CREAT, 0644,
			data->num_philosophers);
	if (data->forks == SEM_FAILED)
		write_error("Opening a semaphore failed.\n", data);
	sem_unlink("philo_forks");
	data->write_lock = sem_open("philo_write", O_CREAT, 0644, 1);
	if (data->write_lock == SEM_FAILED)
		write_error("Opening a semaphore failed.\n", data);
	sem_unlink("philo_write");
	data->death_lock = sem_open("philo_death", O_CREAT, 0644, 1);
	if (data->death_lock == SEM_FAILED)
		write_error("Opening a semaphore failed.\n", data);
	sem_unlink("philo_death");
}
