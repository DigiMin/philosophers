/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:55:08 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 13:03:37 by honnguye         ###   ########.fr       */
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
		(*table)->philos[i].status = THINKING;
		(*table)->philos[i].own_chopstick = &(*table)->chopsticks[i];
		if (i > 0)
			(*table)->philos[i].borrowed_chopstick = &(*table)->chopsticks[i - 1];
		else
			(*table)->philos[i].borrowed_chopstick = &(*table)->chopsticks[(*table)->philos_count - 1];
		(*table)->philos[i].print_status = &(*table)->print_status;
		i++;
	}
}
