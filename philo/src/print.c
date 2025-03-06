/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:27:50 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 12:42:22 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_perror(t_err err)
{
	if (err == INVALID_ARGC)
		write(STDERR_FILENO, "Usage: ./philo [philo_count] [time_to_die] [time_to_eat] [time_to_sleep] [OPTIONAL: meals_to_eat]\n", 95);
	if (err == MALLOC)
		write(STDERR_FILENO, "Memory allocation failed\n", 25);
	if (err == PTHREAD_INIT)
		write(STDERR_FILENO, "Ooops initializing thread failed\n", 33);
	if (err == PTHREAD_JOIN)
		write(STDERR_FILENO, "Ooops joining thread failed\n", 28);
	if (err == PTHREAD_DETACH)
		write(STDERR_FILENO, "Ooops detaching thread failed\n", 30);
	if (err == MUTEX_INIT)
		write(STDERR_FILENO, "Ooops mutex init failed\n", 24);
	if (err == MUTEXT_DESTROY)
		write(STDERR_FILENO, "Ooops destroying mutex failed\n", 30);		
}

void	ft_print_state(t_philo *philo)
{
	if (philo->status == DIED)
		printf("%llu %u died\n", ft_get_time_in_ms(), philo->index);
	if (philo->status == TOOK_FORK)
		printf("%llu %u has taken a fork\n", ft_get_time_in_ms(), philo->index);
	if (philo->status == EATING)
		printf("%llu %u is eating\n", ft_get_time_in_ms(), philo->index);
	if (philo->status == SLEEPING)
		printf("%llu %u is sleeping\n", ft_get_time_in_ms(), philo->index);
	if (philo->status == THINKING)
		printf("%llu %u is thinking\n", ft_get_time_in_ms(), philo->index);
}

unsigned long long	ft_get_time_in_ms(void)
{
	struct timeval time;
	unsigned long long time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

// TODO: DELETE THIS
void	ft_set_table_test(t_table *table)
{
	printf("table philo count: %d\n", table->philos_count);
	printf("table time to eat: %u\n", table->time_to_eat);
	printf("table time to sleep: %u\n", table->time_to_sleep);
	printf("table time to die: %u\n", table->time_to_die);
	printf("table eat count: %d\n", table->meals_to_eat);
}