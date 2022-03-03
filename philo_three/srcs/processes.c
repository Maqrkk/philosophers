/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 17:33:03 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:59:43 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>

/*
**	This function will update the array of process id's to set a specific one
**	to zero, to note it as finished.
*/

static void		set_pid_to_zero(t_data *data, pid_t pid)
{
	int			i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pid == data->pids[i])
		{
			data->pids[i] = 0;
			return ;
		}
		i++;
	}
}

/*
**	This function will kill all child processes (philosophers) because
**	a philosopher died.
*/

static void		kill_philosophers(t_data *data)
{
	int			i;
	pid_t		pid;

	i = 0;
	while (i < data->num_philosophers)
	{
		pid = data->pids[i];
		i++;
		if (pid == 0)
			continue ;
		kill(pid, SIGKILL);
	}
	data->death = true;
}

/*
**	This function will wait for all the processes to finish, and check their
**	exit status. If non-zero, that means a philospher died, and we need to
**	kill all the child processes that are still running.
*/

static void		wait_for_processes(t_data *data)
{
	int			i;
	int			status;
	pid_t		pid;

	i = 0;
	while (i < data->num_philosophers)
	{
		pid = waitpid(-1, &status, 0);
		i++;
		set_pid_to_zero(data, pid);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			continue ;
		kill_philosophers(data);
		return ;
	}
}

/*
**	The main loop for forking processes and then waiting for them.
*/

void			process_loop(t_philosopher *philosopher, t_data *data)
{
	int			i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			write_error("Failed to fork a process!\n", data);
			kill_philosophers(data);
			return ;
		}
		philosopher->num = i + 1;
		if (data->pids[i] == 0)
			philosopher_loop(philosopher);
		i++;
	}
	wait_for_processes(data);
}
