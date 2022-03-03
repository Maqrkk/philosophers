/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 19:16:00 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 12:47:50 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/*
**	Small helper functions to release forks in case of death.
*/

static int		release_forks(t_philosopher *philosopher, int amount)
{
	sem_post(philosopher->data->forks);
	if (amount == 2)
		sem_post(philosopher->data->forks);
	return (EXIT_FAILURE);
}

/*
**	Helper function that spawns the death_checker for this philosopher.
**	If it fails, will exit the process.
*/

static void		spawn_death_checker(t_philosopher *philosopher)
{
	int		ret;

	ret = pthread_create(&philosopher->death_checker, NULL,
			death_checker, philosopher);
	if (ret)
	{
		write_error("Failed to create a thread!\n", philosopher->data);
		exit(EXIT_FAILURE);
	}
}

/*
**	Main loop for a philosopher.
*/

void			philosopher_loop(t_philosopher *philosopher)
{
	spawn_death_checker(philosopher);
	while (!philosopher->data->death &&
			philosopher->times_eaten < philosopher->data->num_times_to_eat)
	{
		status_change(philosopher, THINK);
		sem_wait(philosopher->data->forks);
		if (philosopher->data->death)
			exit(release_forks(philosopher, 1));
		status_change(philosopher, FORK);
		sem_wait(philosopher->data->forks);
		if (philosopher->data->death)
			exit(release_forks(philosopher, 2));
		status_change(philosopher, FORK);
		philosopher_eat(philosopher);
		sem_post(philosopher->data->forks);
		sem_post(philosopher->data->forks);
		philosopher_sleep(philosopher);
	}
	if (philosopher->data->death)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

/*
**	This function prints the timestamp, philosopher number and message.
*/

static void		write_status(unsigned long time, int num, char *message)
{
	write_number(time);
	ft_putchar_fd(' ', STDOUT_FILENO);
	write_number(num);
	write(STDOUT_FILENO, message, ft_strlen(message));
}

/*
**	This function prints the messages for each status change of a philosopher.
*/

void			status_change(t_philosopher *philosopher, t_action action)
{
	unsigned long	time;

	sem_wait(philosopher->data->write_lock);
	if (philosopher->data->death)
	{
		sem_post(philosopher->data->write_lock);
		return ;
	}
	time = current_time() - philosopher->data->time_started;
	if (action == FORK)
		write_status(time, philosopher->num, " has taken a fork\n");
	else if (action == EAT)
		write_status(time, philosopher->num, " is eating\n");
	else if (action == SLEEP)
		write_status(time, philosopher->num, " is sleeping\n");
	else if (action == THINK)
		write_status(time, philosopher->num, " is thinking\n");
	else if (action == DIE)
		write_status(time, philosopher->num, " died\n");
	if (action != DIE)
		sem_post(philosopher->data->write_lock);
}
