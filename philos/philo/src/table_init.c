/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 08:42:56 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 10:25:42 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_table_alloc(t_table **table);
static int	ft_table_start(t_table **table);
static int	ft_init_mutexes(t_table **table);
static int	ft_init_threads(t_table **table);

int	ft_table_set(t_table *table, int argc, char **argv)
{
	table->philos_count = (int)ft_atoui(argv[1]);
	if (table->philos_count < 0)
		return (0);
	table->time_to_die = ft_atoui(argv[2]);
	if (table->time_to_die < 0)
		return (0);
	table->time_to_eat = ft_atoui(argv[3]);
	if (table->time_to_eat < 0)
		return (0);
	table->time_to_sleep = ft_atoui(argv[4]);
	if (table->time_to_sleep < 0)
		return (0);
	if (argc == 6)
	{
		table->meals_to_eat = (int)ft_atoui(argv[5]);
		if (table->meals_to_eat < 0)
			return (0);
	}
	if (!ft_table_start(&table))
		return (0);
	return (1);
}

static int	ft_table_alloc(t_table **table)
{
	int	i;

	if ((*table)->philos_count <= 0)
		return (ft_perror(INVALID_COUNT), 0);
	(*table)->philos = malloc(sizeof(t_philo) * (*table)->philos_count);
	if (!(*table)->philos)
		return (ft_perror(MALLOC), 0);
	(*table)->chopsticks = malloc(sizeof(pthread_mutex_t)
			* (*table)->philos_count);
	if (!(*table)->chopsticks)
		return (ft_perror(MALLOC), 0);
	(*table)->meals_ate = malloc(sizeof(int *) * (*table)->philos_count);
	if (!(*table)->meals_ate)
		return (ft_perror(MALLOC), 0);
	i = 0;
	return (1);
}

void	ft_table_init(t_table *table)
{
	table->meals_to_eat = -1;
	table->philos_count = 0;
	table->start = ft_get_time_in_ms();
	table->time_to_eat = 0;
	table->time_to_die = 0;
	table->time_to_sleep = 0;
	table->philos = NULL;
	table->chopsticks = NULL;
	table->is_dead = 0;
	table->meals_ate = NULL;
}

static int	ft_table_start(t_table **table)
{
	int	i;

	if (!ft_init_mutexes(table))
		return (0);
	ft_philo_init(table);
	i = 0;
	while (i < (*table)->philos_count)
	{
		(*table)->meals_ate[i] = &(*table)->philos[i].meals_ate;
		i++;
	}
	if (!ft_init_threads(table))
		return (0);
	return (1);
}

static int	ft_init_mutexes(t_table **table)
{
	int	i;

	if (!ft_table_alloc(table))
		return (0);
	if (pthread_mutex_init(&(*table)->death, NULL) != 0)
		return (ft_perror(MUTEX_INIT), 0);
	if (pthread_mutex_init(&(*table)->meals_count, NULL) != 0)
		return (ft_perror(MUTEX_INIT), 0);
	if (pthread_mutex_init(&(*table)->print_status, NULL) != 0)
		return (ft_perror(MUTEX_INIT), 0);
	if (pthread_mutex_init(&(*table)->sim_end, NULL) != 0)
		return (ft_perror(MUTEX_INIT), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		if (pthread_mutex_init(&(*table)->chopsticks[i], NULL) != 0)
			return (ft_perror(MUTEX_INIT), 0);
		i++;
	}
	return (1);
}

static int	ft_init_threads(t_table **table)
{
	int	i;

	if (pthread_create(&(*table)->waitress, NULL, &ft_waitress,
			(void *)*table) != 0)
		return (ft_perror(PTHREAD_INIT), 0);
	i = 0;
	while (i < (*table)->philos_count)
	{
		if (i % 2 == 0)
		{
			if ((pthread_create(&((*table)->philos[i].philo), NULL,
						&ft_even_routine, (void *)&(*table)->philos[i])) != 0)
				return (ft_perror(PTHREAD_INIT), 0);
		}
		else
		{
			if ((pthread_create(&((*table)->philos[i].philo), NULL,
						&ft_odd_routine, (void *)&(*table)->philos[i])) != 0)
				return (ft_perror(PTHREAD_INIT), 0);
		}
		i++;
	}
	return (1);
}
