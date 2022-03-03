/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 09:56:44 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/09 13:22:01 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>
#include <semaphore.h>

/*
**	This function will close the locks, and free allocated memory.
*/

int			destroy(t_data *data, int exit_status)
{
	free(data->pids);
	sem_close(data->write_lock);
	sem_close(data->death_lock);
	sem_close(data->forks);
	return (exit_status);
}
