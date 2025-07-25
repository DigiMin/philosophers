/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:06:00 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 09:43:41 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_table_destroy(t_table **table)
{
	int	i;

	if ((pthread_join((*table)->waitress, NULL)) != 0)
		return (ft_perror(PTHREAD_DETACH), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		if ((pthread_join((*table)->philos[i].philo, NULL)) != 0)
			return (ft_perror(PTHREAD_JOIN), 0);
		i++;
	}
	return (1);
}

int	ft_table_kill(t_table **table)
{
	int	i;

	if ((pthread_detach((*table)->waitress)) != 0)
		return (ft_perror(PTHREAD_DETACH), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		if ((pthread_detach((*table)->philos[i].philo)) != 0)
			return (ft_perror(PTHREAD_DETACH), 0);
		i++;
	}
	return (1);
}

int	ft_mutex_cleanup(t_table **table)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(*table)->death) != 0)
		return (ft_perror(MUTEXT_DESTROY), printf("DEATH MUTEX\n"), 0);
	if (pthread_mutex_destroy(&(*table)->meals_count) != 0)
		return (ft_perror(MUTEXT_DESTROY), printf("MEALS MUTEX\n"), 0);
	if (pthread_mutex_destroy(&(*table)->print_status) != 0)
		return (ft_perror(MUTEXT_DESTROY), printf("PRINT MUTEX\n"), 0);
	if (pthread_mutex_destroy(&(*table)->sim_end) != 0)
		return (ft_perror(MUTEXT_DESTROY), printf("SIM_END MUTEX\n"), 0);
	while (i < (*table)->philos_count)
	{
		if (pthread_mutex_destroy(&(*table)->chopsticks[i]) != 0)
			return (ft_perror(MUTEXT_DESTROY), 0);
		i++;
	}
	return (1);
}

void	ft_free_table(t_table **table)
{
	free((*table)->philos);
	free((*table)->chopsticks);
	free((*table)->meals_ate);
}

int	ft_table_cleanup(t_table *table)
{
	int	i;

	i = 0;
	// ft_table_kill(&table);
	ft_table_destroy(&table);
	ft_mutex_cleanup(&table);
	ft_free_table(&table);
	return (1);
}
