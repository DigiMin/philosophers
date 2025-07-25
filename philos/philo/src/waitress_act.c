/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress_act.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:36:54 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 09:40:02 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_set_done_dinin(t_table **t);
static int	ft_philos_full(t_table *t);
static int	ft_one_dead(t_table *t);

void	*ft_waitress(void *table)
{
	while (1)
	{
		if (ft_one_dead((t_table *)table))
			break ;
		if (((t_table *)table)->meals_to_eat > -1
			&& ft_philos_full((t_table *)table))
			break ;
		usleep(((t_table *)table)->time_to_die / 2);
	}
	return (NULL);
}

static int	ft_philos_full(t_table *t)
{
	int	i;
	int	fully_ate;

	i = 0;
	fully_ate = 0;
	pthread_mutex_lock(&t->meals_count);
	while (i < (t->philos_count))
	{
		if (t->meals_to_eat <= *t->meals_ate[i])
			fully_ate++;
		i++;
	}
	pthread_mutex_unlock(&t->meals_count);
	if (fully_ate == t->philos_count)
	{
		ft_set_done_dinin(&t);
		return (1);
	}
	return (0);
}

static int	ft_one_dead(t_table *t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&t->death);
	while (i < t->philos_count)
	{
		if (t->philos[i].is_dead)
			break ;
		i++;
	}
	pthread_mutex_unlock(&t->death);
	if (i == t->philos_count)
		return (0);
	ft_set_done_dinin(&t);
	return (1);
}

static void	ft_set_done_dinin(t_table **t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(*t)->sim_end);
	while (i < (*t)->philos_count)
	{
		(*t)->philos[i].done_dining = 1;
		i++;
	}
	pthread_mutex_unlock(&(*t)->sim_end);
}
