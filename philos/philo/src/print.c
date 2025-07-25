/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:27:50 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/20 10:24:00 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_perror(t_err err)
{
	if (err == INVALID_ARGC)
		write(STDERR_FILENO,
			"./philo [count] [die] [eat] [sleep] [OPTIONAL: meals_to_eat]\n",
			61);
	if (err == MALLOC)
		write(STDERR_FILENO, "Memory allocation failed\n", 25);
	if (err == INVALID_COUNT)
		write(STDERR_FILENO, "The count should be greater than 0\n", 36);
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

// TODO: DELETE THIS------------------------------------
// void	ft_print_state(t_philo *philo)
// {
// 	int64_t time;

// 	if (philo->status == DIED)
// 		printf("%ld %d died\n", ft_get_time_in_ms(), philo->index);
// 	else if (philo->status == TOOK_FORK)
// 		printf("%ld %u has taken a fork\n", ft_get_time_in_ms(), philo->index);
// 	else if (philo->status == EATING)
// 	{
// 		time = ft_get_time_in_us();
// 		philo->start_to_eat = time;
// 		printf("%ld %u is eating\n", time / 1000, philo->index);
// 	}
// 	else if (philo->status == SLEEPING)
// 		printf("%ld %u is sleeping\n", ft_get_time_in_ms(), philo->index);
// 	else if (philo->status == THINKING)
// 		printf("%ld %u is thinking\n", ft_get_time_in_ms(), philo->index);
// }

void	ft_set_table_test(t_table *table)
{
	printf("table philo count: %d\n", table->philos_count);
	printf("table time to eat: %ld\n", table->time_to_eat);
	printf("table time to sleep: %ld\n", table->time_to_sleep);
	printf("table time to die: %ld\n", table->time_to_die);
	printf("table eat count: %d\n", table->meals_to_eat);
}
