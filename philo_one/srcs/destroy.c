/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 09:07:00 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/09 08:13:22 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

/*
**	This function will try to destroy a lock. If it is locked, will unlock and
**	destroy again.
*/

void		destroy_lock(pthread_mutex_t *lock)
{
	int		ret;

	ret = pthread_mutex_destroy(lock);
	if (ret == EBUSY)
	{
		pthread_mutex_unlock(lock);
		pthread_mutex_destroy(lock);
	}
}

/*
**	This function will destroy the locks, and free allocated memory.
*/

int			destroy(t_group *group, t_data *data, int exit_status)
{
	int			i;

	free(group->philosophers);
	free(data->philo_threads);
	destroy_lock(&data->write_lock);
	destroy_lock(&data->death_lock);
	i = 0;
	while (i < data->num_philosophers)
	{
		destroy_lock(data->forks + i);
		i++;
	}
	free(data->forks);
	return (exit_status);
}
