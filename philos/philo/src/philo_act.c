/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:31:45 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/22 13:45:02 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_end_of_dinin(t_philo *philo);
static void	ft_death_cntdwn(t_philo *philo, int64_t stay_alive_time);
static int	ft_eat(t_philo *philo);
static int	ft_sleep(t_philo *philo);
static void	ft_think(t_philo *philo);
void		ft_odd_chopstick_pickup(t_philo *philo);
int			ft_even_chopstick_pickup(t_philo *philo);
void		ft_put_down_cutilery(t_philo *philo);

void	*ft_even_routine(void *philo)
{
	while (1)
	{
		if (!ft_even_chopstick_pickup((t_philo *)philo))
		{
			ft_death_cntdwn(philo, *((t_philo *)philo)->time_to_die);
			break ;
		}
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead)
		{
			ft_put_down_cutilery(philo);
			break ;
		}
		if (!ft_eat((t_philo *)philo))
			break ;
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead
			|| !ft_sleep((t_philo *)philo))
			break ;
		ft_think((t_philo *)philo);
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead)
			break ;
	}
	return (NULL);
}

void	*ft_odd_routine(void *philo)
{
	while (1)
	{
		ft_think((t_philo *)philo);
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead)
			break ;
		ft_odd_chopstick_pickup((t_philo *)philo);
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead)
		{
			ft_put_down_cutilery(philo);
			break ;
		}
		if (!ft_eat((t_philo *)philo))
			break ;
		if (ft_end_of_dinin((t_philo *)philo) || ((t_philo *)philo)->is_dead
			|| !ft_sleep((t_philo *)philo))
			break ;
	}
	return (NULL);
}

static int	ft_end_of_dinin(t_philo *philo)
{
	pthread_mutex_lock(philo->sim_end);
	if (philo->done_dining)
	{
		pthread_mutex_unlock(philo->sim_end);
		return (1);
	}
	pthread_mutex_unlock(philo->sim_end);
	return (0);
}

static void	ft_death_cntdwn(t_philo *philo, int64_t stay_alive_time)
{
	ft_usleep(stay_alive_time * 1000 - 500);
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u died\n", ft_get_time_in_ms() - *philo->start, philo->index);
	pthread_mutex_unlock(philo->print_status);
	pthread_mutex_lock(philo->death);
	philo->is_dead = 1;
	pthread_mutex_unlock(philo->death);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print_status);
	philo->start_to_eat = ft_get_time_in_ms();
	printf("%ld %u is eating\n", philo->start_to_eat - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	if (*philo->time_to_eat < *philo->time_to_die)
	{
		ft_usleep(*philo->time_to_eat * 1000);
		pthread_mutex_lock(&(*philo->meals_count));
		philo->meals_ate++;
		pthread_mutex_unlock(&(*philo->meals_count));
		ft_put_down_cutilery(philo);
		return (1);
	}
	else
	{
		ft_death_cntdwn(philo, *philo->time_to_die);
		ft_put_down_cutilery(philo);
		return (0);
	}
}

static int	ft_sleep(t_philo *philo)
{
	int64_t	time_left;

	pthread_mutex_lock(philo->print_status);
	printf("%ld %u is sleeping\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	time_left = *philo->time_to_die - *philo->time_to_eat;
	if (time_left <= *philo->time_to_sleep)
	{
		ft_death_cntdwn(philo, time_left);
		return (0);
	}
	else
	{
		ft_usleep(*philo->time_to_sleep * 1000);
		return (1);
	}
}

// TODO: reacalculate the time to think
static void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u is thinking\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	if (*philo->time_to_die < *philo->time_to_eat)
		ft_death_cntdwn(philo, *philo->time_to_die);
	else if (*philo->time_to_eat + *philo->time_to_sleep > *philo->time_to_die)
		ft_usleep(((*philo->time_to_sleep + *philo->time_to_eat)
				- *philo->time_to_die) * 1000);
	else
		ft_usleep(((*philo->time_to_die - (*philo->time_to_sleep
						+ *philo->time_to_eat)) / 2) * 1000);
}

int	ft_even_chopstick_pickup(t_philo *philo)
{
	if (philo->borrowed_chopstick == 0)
		return (0);
	pthread_mutex_lock(philo->own_chopstick);
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u has taken a fork\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	pthread_mutex_lock(philo->borrowed_chopstick);
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u has taken a fork\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	return (1);
}

void	ft_odd_chopstick_pickup(t_philo *philo)
{
	pthread_mutex_lock(philo->borrowed_chopstick);
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u has taken a fork\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
	pthread_mutex_lock(philo->own_chopstick);
	pthread_mutex_lock(philo->print_status);
	printf("%ld %u has taken a fork\n", ft_get_time_in_ms() - *philo->start,
		philo->index);
	pthread_mutex_unlock(philo->print_status);
}

void	ft_put_down_cutilery(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(philo->own_chopstick);
		pthread_mutex_unlock(philo->borrowed_chopstick);
	}
	else
	{
		pthread_mutex_unlock(philo->borrowed_chopstick);
		pthread_mutex_unlock(philo->own_chopstick);
	}
}
