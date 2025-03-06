/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:42:56 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 13:04:16 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	ft_table_init(t_table *table)
{
	table->meals_to_eat = -1;
	table->philos_count = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_die = 0;
	table->philos = NULL;
	table->chopsticks = NULL;
	table->is_dead = 0;
	table->meals_ate = NULL;
}

int	ft_table_alloc(t_table **table)
{
	int	i;

	(*table)->philos = malloc(sizeof(t_philo) * (*table)->philos_count);
	if (!(*table)->philos)
		return (ft_perror(MALLOC), 0);
	(*table)->chopsticks = malloc (sizeof(pthread_mutex_t) * (*table)->philos_count);
	if (!(*table)->chopsticks)
		return (ft_perror(MALLOC), 0);
	(*table)->meals_ate = malloc (sizeof(int) * (*table)->philos_count);
	if (!(*table)->meals_ate)
		return (ft_perror(MALLOC), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		(*table)->meals_ate[i] = 0;
		i++;
	}
	return (1);
}

int ft_table_start(t_table **table)
{
	int	i;

	if (!ft_table_alloc(table))
		return (0);
	ft_philo_init(table);
	if (pthread_mutex_init(&(*table)->print_status, NULL) != 0)
		return (ft_perror(MUTEX_INIT), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		if (pthread_mutex_init(&(*table)->chopsticks[i], NULL) != 0)
			return (ft_perror(MUTEX_INIT), 0);
		i++;
	}
	i = 0;
	while (i < (*table)->philos_count)
	{
		if ((pthread_create(&((*table)->philos[i].philo), NULL, &ft_routine, (void *) &(*table)->philos[i])) != 0)
			return (ft_perror(PTHREAD_INIT), 0);
		i++;
	}
	return (1);
}

int	ft_table_set(t_table *table, int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	if ((num = ft_atoui(argv[1])) < 0)
		return (0);
	table->philos_count = num;
	if ((num = ft_atoui(argv[2])) < 0)
		return (0);
	table->time_to_eat = num;
	if ((num = ft_atoui(argv[3])) < 0)
		return (0);
	table->time_to_sleep = num;
	if ((num = ft_atoui(argv[4])) < 0)
		return (0);
	table->time_to_die = num;
	if (argc == 6)
	{
		if ((num = ft_atoui(argv[4])) < 0)
			return (0);
		table->meals_to_eat = ft_atoui(argv[5]);
	}
	if (!ft_table_start(&table))
		return (0);
	return (1);
}
