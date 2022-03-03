/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 14:23:17 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/11/14 09:05:42 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

/*
**	This function returns a timestamp in microseconds for the current moment.
*/

unsigned long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
