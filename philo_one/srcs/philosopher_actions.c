/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 08:27:37 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 09:01:43 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

/*
**	Helper function to sleep in small increments, because usleep is
**	inconsistent over bigger periods of time. Will keep track of when a
**	philosopher dies aswell.
*/

static void	philo_usleep(unsigned long total_time)
{
	unsigned long	start_time;

	start_time = current_time();
	while (current_time() - start_time < total_time)
		usleep(100);
}

/*
**	This function lets a philosopher sleep.
*/

void		philosopher_sleep(t_philosopher *philosopher)
{
	status_change(philosopher, SLEEP);
	if (philosopher->data->death)
		return ;
	philo_usleep(philosopher->data->time_to_sleep);
}

/*
**	This function lets a philosopher eat.
*/

void		philosopher_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->death_lock);
	if (philosopher->data->death)
	{
		pthread_mutex_unlock(&philosopher->data->death_lock);
		return ;
	}
	status_change(philosopher, EAT);
	if (philosopher->data->eat_requirement == true)
		philosopher->times_eaten++;
	philosopher->last_time_eaten = current_time();
	pthread_mutex_unlock(&philosopher->data->death_lock);
	philo_usleep(philosopher->data->time_to_eat);
}
