/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:06:00 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 12:51:36 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


int ft_table_destroy(t_table **table)
{
	int	i = 0;
	
	i = 0;
	while (i < (*table)->philos_count)
	{
		if((pthread_join((*table)->philos[i].philo, NULL)) != 0)
			return (ft_perror(PTHREAD_JOIN), 0);
		i++;
	}
	return (1);
}

int ft_table_kill(t_table **table)
{
	int	i = 0;
	
	i = 0;
	while (i < (*table)->philos_count)
	{
		if((pthread_detach((*table)->philos[i].philo)) != 0)
			return (ft_perror(PTHREAD_DETACH), 0);
		i++;
	}
	return (1);
}

int ft_mutex_cleanup(t_table **table)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(*table)->print_status) != 0)
		return (ft_perror(MUTEXT_DESTROY), 0);
	while (i < (*table)->philos_count)
	{
		if (pthread_mutex_destroy(&(*table)->chopsticks[i]) != 0)
			return (ft_perror(MUTEXT_DESTROY), 0);
		i++;
	}
	return (1);
}

int	ft_table_cleanup(t_table *table)
{
	int	i;

	i = 0;
	if (table->is_dead)
	{
		ft_mutex_cleanup(&table);
		ft_table_kill(&table);
		free(table->philos);
		free(table->meals_ate);
		return (1);
	}
	while (i < table->philos_count)
	{
		if (table->meals_ate[i] != table->meals_to_eat)
			return (0);
	}
	ft_mutex_cleanup(&table);
	ft_table_destroy(&table);
	free(table->philos);
	free(table->meals_ate);
	return (1);
}