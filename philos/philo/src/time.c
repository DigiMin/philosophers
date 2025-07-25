/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:31:46 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 09:48:18 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/// @brief Uses gettimeofday function and extract from the timeval structure
///			the time in miliseconds
/// @param  take no parameters
/// @return returns a signed int64_t ()
int64_t	ft_get_time_in_ms(void)
{
	struct timeval	time;
	int64_t			time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

int64_t	ft_get_time_in_us(void)
{
	struct timeval	time;
	int64_t			time_us;

	gettimeofday(&time, NULL);
	time_us = time.tv_sec * 1000000 + time.tv_usec;
	return (time_us);
}

int64_t	ft_usleep(int64_t duration)
{
	int64_t	start;
	int64_t	now;
	int64_t	elapsed;

	if (duration < 0)
		return (0);
	start = ft_get_time_in_us();
	now = ft_get_time_in_us();
	elapsed = now - start;
	duration -= 200;
	while (elapsed < duration)
	{
		if (duration > 1000)
			usleep(duration);
		now = ft_get_time_in_us();
		elapsed = now - start;
	}
	return (elapsed);
}
