/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:22:05 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 13:05:25 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *philo)
{
	(void) philo;
	usleep(1000);
	return (NULL);
}

void ft_activity_switch(t_philo *philo)
{
	pthread_mutex_lock(philo->print_status);
	ft_print_state(philo);
	pthread_mutex_unlock(philo->print_status);
}