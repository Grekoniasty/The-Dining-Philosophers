/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:25:56 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/02/02 12:23:47 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table {
    int                 num_philos;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 num_must_eat;
    pthread_mutex_t     *forks;
    pthread_mutex_t     print_lock;
    pthread_mutex_t     death_lock;
    int                 someone_died;
    int                 ready;
    long                start_time;
    struct s_philo      *philos;
} t_table;

typedef struct s_philo {
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table *data;
    pthread_t thread;
} t_philo;


/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                       Utils Functions                       #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

long	ft_atol(const char *str);
long	get_time(void);
long	get_elapsed_time(long start_time);
void	ft_usleep(long milliseconds);
void    cleanup(t_table *table, t_philo *philos);

/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                          Parsing                            #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

int parser(int ac, char ** av, t_table *table);

/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                          Mutexes                            #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

int init_mutexes(t_table *table);

/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                       Philo Utils                          #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

int		is_ready(t_philo *philo);
void	stagger_philo(t_philo *philo);

/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                          Threads                            #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

void	join_threads(t_table *table, t_philo *philos);
int		create_threads(t_table *table, t_philo *philos);
int		init_philosophers(t_table *table, t_philo **philos);
void	*philosopher_routine(void *arg);

/*#-------------------------------------------------------------#*/
/*#                                                             #*/
/*#                          Monitoring                         #*/
/*#                                                             #*/
/*#-------------------------------------------------------------#*/

void    *monitor_routine(void *arg);
void	print_status(t_philo *philo, char *status);
int     check_death(t_philo *philo);

#endif
