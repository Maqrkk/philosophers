/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 09:56:44 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/02 11:20:32 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>

/*
**	This function will close the locks, and free allocated memory.
*/

int			destroy(t_group *group, t_data *data, int exit_status)
{
	free(group->philosophers);
	free(data->philo_threads);
	sem_close(data->write_lock);
	sem_close(data->death_lock);
	sem_close(data->forks);
	return (exit_status);
}
