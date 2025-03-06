/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:40:34 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/06 13:05:06 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_error
{
	INVALID_ARGC,
	MALLOC,
	PTHREAD_INIT,
	PTHREAD_JOIN,
	PTHREAD_DETACH,
	MUTEX_INIT,
	MUTEXT_DESTROY
}					t_err;

typedef enum e_philo_status
{
	DIED,
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
}					t_status;

// TIMEVAL structure returns time elapsed frm the EPOCH
// in tv_sec-seconds and tv_usec-microseconds
// TODO: conversion
// IN MILLI SECONDS

typedef struct t_philo
{
	unsigned int	index;
	t_status		status;
	pthread_t		philo;
	pthread_mutex_t	*own_chopstick;
	pthread_mutex_t	*borrowed_chopstick;
	pthread_mutex_t	*print_status;
}					t_philo;

typedef struct t_table
{
	int				meals_to_eat;
	int				philos_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	print_status;
	int				is_dead;
	int				*meals_ate;

}					t_table;

// TABLE INIT
int					ft_table_set(t_table *table, int argc, char **argv);
void				ft_table_init(t_table *table);
int					ft_table_alloc(t_table **table);
int					ft_table_start(t_table **table);

// TABLE KILL
int					ft_table_destroy(t_table **table);
int					ft_table_kill(t_table **table);
int					ft_table_cleanup(t_table *table);

// PHILOS
void				ft_philo_init(t_table **table);

// ACTION
void				*ft_routine(void *philo);

// PRINT
void				ft_perror(t_err err);
void				ft_print_state(t_philo *philo);
unsigned long long	ft_get_time_in_ms(void);
void				ft_set_table_test(t_table *table);

// HELPERS
int					ft_isspace(char *c);
int					ft_isnum(char *c);
int					ft_sign(char *c);
unsigned int		ft_atoui(char *str);

#endif