/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honnguye <honnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:40:34 by honnguye          #+#    #+#             */
/*   Updated: 2025/03/17 10:04:31 by honnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_error
{
	INVALID_ARGC,
	MALLOC,
	INVALID_COUNT,
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
	int				index;
	int				is_dead;
	int64_t			start_to_eat;
	int64_t			start_to_sleep;
	int64_t			start_to_think;
	int64_t			*start;
	int64_t			*time_to_die;
	int64_t			*time_to_eat;
	int64_t			*time_to_sleep;
	int				*meals_to_eat;
	int				meals_ate;
	int				done_dining;
	pthread_t		philo;
	pthread_mutex_t	*own_chopstick;
	pthread_mutex_t	*borrowed_chopstick;
	pthread_mutex_t	*meals_count;
	pthread_mutex_t	*sim_end;
	pthread_mutex_t	*print_status;
	pthread_mutex_t	*death;
}					t_philo;

typedef struct t_table
{
	pthread_t		waitress;
	int				philos_count;
	int64_t			start;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int				meals_to_eat;
	t_philo			*philos;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	meals_count;
	pthread_mutex_t	print_status;
	pthread_mutex_t	death;
	pthread_mutex_t	sim_end;
	int				is_dead;
	int				**meals_ate;

}					t_table;

// TABLE INIT
int					ft_table_set(t_table *table, int argc, char **argv);
void				ft_table_init(t_table *table);

// TABLE KILL
int					ft_table_destroy(t_table **table);
int					ft_table_kill(t_table **table);
int					ft_table_cleanup(t_table *table);

// PHILOS
void				ft_philo_init(t_table **table);

// PHILO ACTION
void				*ft_even_routine(void *philo);
void				*ft_odd_routine(void *philo);
// void				ft_activity_switch(t_philo *philo);

// WAITRESS ACTION
void				*ft_waitress(void *table);

// TIME
int64_t				ft_get_time_in_ms(void);
int64_t				ft_get_time_in_us(void);
int64_t				ft_usleep(int64_t duration);

// PRINT
void				ft_perror(t_err err);
// void				ft_print_state(t_philo *philo);
void				ft_set_table_test(t_table *table);

// HELPERS
int					ft_isspace(char *c);
int					ft_isnum(char *c);
int					ft_sign(char *c);
int64_t				ft_atoui(char *str);

#endif