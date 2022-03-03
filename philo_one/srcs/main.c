/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 13:50:56 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:36:12 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

/*
**	This function will check if the right amount of arguments are passed to
**	the program, and check if they are the correct types.
*/

static void		check_input(int argc, char **argv, t_data *data)
{
	data->error = false;
	if (argc != 5 && argc != 6)
		return (write_error("Incorrect number of arguments.\n", data));
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->num_philosophers < 2)
		return (write_error("Need at least 2 philosophers.\n", data));
	if (data->time_to_die < 60)
		return (write_error("Time to die needs to be at least 60.\n", data));
	if (data->time_to_eat < 60)
		return (write_error("Time to eat needs to be at least 60.\n", data));
	if (data->time_to_sleep < 60)
		return (write_error("Time to sleep needs to be at least 60.\n", data));
	data->eat_requirement = (argc == 6) ? true : false;
	data->death = false;
	data->num_times_to_eat = (argc == 6) ? ft_atoi(argv[5]) : 1;
	if (data->num_times_to_eat < 1)
		write_error("Number of times to eat cannot be lower than 1.\n", data);
}

/*
**	This function assigns the correct forks to each philosopher.
*/

static void		assign_forks(t_group *group, t_data *data)
{
	int				i;
	t_philosopher	*current;

	i = 0;
	while (i < group->num_philosophers)
	{
		current = &group->philosophers[i];
		current->fork1 = data->forks + i;
		current->fork2 = data->forks + ((i + 1) % data->num_philosophers);
		i++;
	}
}

/*
**	Small helper function to print the message when all philosophers are
**	done eating.
*/

static void		print_finish_message(t_data *data)
{
	int		num;

	if (data->death || data->error)
		return ;
	num = data->num_times_to_eat;
	write(STDOUT_FILENO, "All philosophers have eaten ", 28);
	write_number(num);
	write(STDOUT_FILENO, " times!\n", 8);
}

/*
**	This function spawns all threads in a loop, then joins them all back
**	together if they finish.
*/

static void		thread_loop(t_group *group, t_data *data)
{
	int		i;
	int		ret;

	i = 0;
	while (i < data->num_philosophers)
	{
		ret = pthread_create(&data->philo_threads[i], NULL, &philosopher,
				(void*)(group->philosophers + i));
		if (ret)
			return (write_error("Failed to create a thread!\n", data));
		i++;
	}
	ret = pthread_create(&data->death_checker, NULL, death_checker,
			(void*)group);
	if (ret)
		return (write_error("Failed to create a thread!\n", data));
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	pthread_join(data->death_checker, NULL);
}

/*
**	Main function, first check if the input is valid, then start doing
**	philosophy.
*/

int				main(int argc, char **argv)
{
	t_data				data;
	t_group				group;

	check_input(argc, argv, &data);
	if (data.error)
		return (EXIT_FAILURE);
	data.time_started = current_time();
	init_philosophers(&group, &data, data.num_philosophers);
	init_locks(&data);
	if (data.error)
		return (destroy(&group, &data, EXIT_FAILURE));
	assign_forks(&group, &data);
	thread_loop(&group, &data);
	print_finish_message(&data);
	return (destroy(&group, &data, EXIT_SUCCESS));
}
