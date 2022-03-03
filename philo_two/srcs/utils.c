/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 09:29:23 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 11:03:11 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

/*
**	Calculates the length of a string. I know.
*/

size_t		ft_strlen(char *s)
{
	size_t	length;

	length = 0;
	while (*(s + length))
		length++;
	return (length);
}

/*
**	This function will write an error to the terminal and exit the program
**	with a failure code.
*/

void		write_error(char *error, t_data *data)
{
	if (data->error)
		return ;
	write(STDERR_FILENO, error, ft_strlen(error));
	data->error = true;
}

/*
**	This function converts a string into an integer.
*/

int			ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result >= 922337203685477580)
		{
			if (*str >= '8')
				return (-1);
			result = (result * 10) + (*str - 48);
			return ((int)result);
		}
		result *= 10;
		result += (*str - 48);
		str++;
	}
	return ((int)result);
}

/*
**	This funcion prints a single character to the screen. Only used for
**	the write_number function.
*/

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
**	Helper function for printing a number. Number can only be positive.
*/

void		write_number(unsigned long num)
{
	if (num >= 10)
		write_number(num / 10);
	ft_putchar_fd((num % 10) + '0', STDOUT_FILENO);
}
