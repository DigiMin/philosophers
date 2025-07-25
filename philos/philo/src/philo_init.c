/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:55:08 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 09:40:13 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_philo_init(t_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)->philos_count)
	{
		(*table)->philos[i].index = i;
		(*table)->philos[i].is_dead = 0;
		(*table)->philos[i].start_to_eat = ft_get_time_in_ms();
		(*table)->philos[i].start = &(*table)->start;
		(*table)->philos[i].time_to_eat = &(*table)->time_to_eat;
		(*table)->philos[i].time_to_sleep = &(*table)->time_to_sleep;
		(*table)->philos[i].time_to_die = &(*table)->time_to_die;
		(*table)->philos[i].meals_to_eat = &(*table)->meals_to_eat;
		(*table)->philos[i].meals_ate = 0;
		(*table)->philos[i].done_dining = 0;
		(*table)->philos[i].meals_count = &(*table)->meals_count;
		(*table)->philos[i].sim_end = &(*table)->sim_end;
		(*table)->philos[i].death = &(*table)->death;
		(*table)->philos[i].own_chopstick = &(*table)->chopsticks[i];
		(*table)->philos[i].print_status = &(*table)->print_status;
		if ((*table)->philos_count == 1)
		{
			(*table)->philos[i].borrowed_chopstick = 0;
			break ;
		}
		else if (i > 0)
			(*table)->philos[i].borrowed_chopstick = &(*table)->chopsticks[i
				- 1];
		else
			(*table)->philos[i].borrowed_chopstick = &(*table)->chopsticks[(*table)->philos_count
				- 1];
		i++;
	}
}
