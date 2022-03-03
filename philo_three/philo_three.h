/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 11:31:08 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:38:03 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>

/*
**	This struct holds the information about the data that was input into
**	the program.
*/

typedef struct		s_data
{
	int				num_philosophers;
	unsigned long	time_started;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			eat_requirement;
	int				num_times_to_eat;
	bool			error;
	bool			death;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*death_lock;
}					t_data;

/*
**	This struct holds data relevant for a single philosopher.
*/

typedef struct		s_philosopher
{
	int				num;
	unsigned long	last_time_eaten;
	int				times_eaten;
	t_data			*data;
	pthread_t		death_checker;
}					t_philosopher;

/*
**	This enum is used when printing a message about a philosopher.
*/

typedef enum		e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}					t_action;

/*
**	death_checker.c
*/

void				*death_checker(void *arg);

/*
**	destroy.c
*/

int					destroy(t_data *data, int exit_status);

/*
**	init.c
*/

void				init_pid_array(t_data *data, int num);
void				init_philosopher(t_philosopher *philosopher, t_data *data);
void				init_locks(t_data *data);

/*
**	philosopher.c
*/

void				philosopher_loop(t_philosopher *philosopher);
void				status_change(t_philosopher *philosopher, t_action action);

/*
**	philosopher_actions.c
*/

void				philosopher_sleep(t_philosopher *philosopher);
void				philosopher_eat(t_philosopher *philosopher);

/*
**	processes.c
*/

void				process_loop(t_philosopher *philosopher, t_data *data);

/*
**	time.c
*/

unsigned long		current_time(void);

/*
**	utils.c
*/

size_t				ft_strlen(char *s);
void				write_error(char *error, t_data *data);
int					ft_atoi(const char *s);
void				ft_putchar_fd(char c, int fd);
void				write_number(unsigned long num);

#endif
