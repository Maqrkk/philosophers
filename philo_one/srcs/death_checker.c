/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 11:48:29 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/15 08:46:24 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

/*
**	This function will be called for each philosopher to check if they
**	are dead.
*/

static int	check_philosopher_status(t_philosopher *philosopher)
{
	if (philosopher->times_eaten == philosopher->data->num_times_to_eat)
		return (1);
	if ((current_time() - philosopher->last_time_eaten) >=
			(unsigned long)philosopher->data->time_to_die)
	{
		status_change(philosopher, DIE);
	}
	return (0);
}

/*
**	The loop in which the philosophers are checked for whether they are
**	done eating. Will return the amount of philosophers that are done.
*/

static int	check_loop(t_group *group)
{
	int				i;
	int				done;
	t_philosopher	*current;

	i = 0;
	done = 0;
	while (i < group->num_philosophers)
	{
		current = &group->philosophers[i];
		done += check_philosopher_status(current);
		if (current->data->death)
			break ;
		i++;
	}
	return (done);
}

/*
**	This is the main thread for the death checker. Will keep looping until
**	all philosophers are done eating, or until one has died.
*/

void		*death_checker(void *arg)
{
	t_group			*group;
	int				philosophers_done;

	group = arg;
	while (true)
	{
		pthread_mutex_lock(group->death_lock);
		philosophers_done = check_loop(group);
		pthread_mutex_unlock(group->death_lock);
		if (group->philosophers[0].data->death)
			break ;
		if (philosophers_done == group->num_philosophers)
			break ;
		usleep(100);
	}
	return (NULL);
}
