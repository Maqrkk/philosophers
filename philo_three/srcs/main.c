/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 10:52:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:56:05 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
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
**	Main function, first check if the input is valid, then start doing
**	philosophy.
*/

int				main(int argc, char **argv)
{
	t_data				data;
	t_philosopher		philosopher;

	check_input(argc, argv, &data);
	if (data.error)
		return (EXIT_FAILURE);
	data.time_started = current_time();
	init_philosopher(&philosopher, &data);
	init_pid_array(&data, data.num_philosophers);
	init_locks(&data);
	if (data.error)
		return (destroy(&data, EXIT_FAILURE));
	process_loop(&philosopher, &data);
	print_finish_message(&data);
	return (destroy(&data, EXIT_SUCCESS));
}
