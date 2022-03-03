/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 11:42:49 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 12:04:02 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stddef.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

/*
**	This function allocates an array of process id's necessary for keeping
**	track of all the philosopher processes, and being able to kill them if
**	required.
*/

void			init_pid_array(t_data *data, int num)
{
	data->pids = malloc(sizeof(pid_t) * num);
	if (data->pids == NULL)
		write_error("A malloc failed while allocating process ids.\n", data);
	memset(data->pids, 0, sizeof(pid_t) * num);
}

/*
**	This function initializes the philosopher with information they all need.
*/

void			init_philosopher(t_philosopher *philosopher, t_data *data)
{
	philosopher->num = 0;
	philosopher->last_time_eaten = current_time();
	philosopher->times_eaten = 0;
	philosopher->data = data;
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
