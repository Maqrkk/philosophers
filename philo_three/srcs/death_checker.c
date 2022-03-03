/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 11:48:29 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:52:52 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/*
**	This function will be called for each philosopher to check if they
**	are dead.
*/

static void		check_philosopher_status(t_philosopher *philosopher)
{
	if (current_time() - philosopher->last_time_eaten >=
			(unsigned long)philosopher->data->time_to_die)
	{
		status_change(philosopher, DIE);
		exit(EXIT_FAILURE);
	}
}

/*
**	This is the main thread for the death checker. Will keep looping until
**	all philosophers are done eating, or until one has died.
*/

void			*death_checker(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = arg;
	while (true)
	{
		sem_wait(philosopher->data->death_lock);
		check_philosopher_status(philosopher);
		sem_post(philosopher->data->death_lock);
		usleep(100);
	}
	return (NULL);
}
