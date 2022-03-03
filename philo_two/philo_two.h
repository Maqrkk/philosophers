/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 08:43:12 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 09:53:26 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>

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
	pthread_t		death_checker;
	pthread_t		*philo_threads;
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
}					t_philosopher;

/*
**	This struct holds data for all the philosophers in the program.
*/

typedef struct		s_group
{
	t_philosopher	*philosophers;
	int				num_philosophers;
	sem_t			*death_lock;
}					t_group;

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

int					destroy(t_group *group, t_data *data, int exit_status);

/*
**	init.c
*/

void				init_philosophers(t_group *group, t_data *data, int num);
void				init_locks(t_data *data);

/*
**	philosopher.c
*/

void				*philosopher(void *arg);
void				status_change(t_philosopher *philosopher, t_action action);

/*
**	philosopher_actions.c
*/

void				philosopher_sleep(t_philosopher *philosopher);
void				philosopher_eat(t_philosopher *philosopher);

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
