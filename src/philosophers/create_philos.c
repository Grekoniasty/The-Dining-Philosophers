/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:33:31 by mpiasecz          #+#    #+#             */
/*   Updated: 2025/11/28 13:10:13 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static void	abort_threads(t_table *table, t_philo *philos, int count)
{
	int	i;

	pthread_mutex_lock(&table->death_lock);
	table->start_time = get_time();
	i = 0;
	while (i < count)
	{
		philos[i].last_meal_time = table->start_time;
		i++;
	}
	table->someone_died = 1;
	table->ready = 1;
	pthread_mutex_unlock(&table->death_lock);
	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	create_threads(t_table *table, t_philo *philos)
{
	int	i;

	table->ready = 0;
	table->last_printed_timestamp = -1;
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philosopher_routine,
				&philos[i]) != 0)
		{
			abort_threads(table, philos, i);
			return (-1);
		}
		i++;
	}
	pthread_mutex_lock(&table->death_lock);
	table->start_time = get_time();
	i = 0;
	while (i < table->num_philos)
	{
		philos[i].last_meal_time = table->start_time;
		i++;
	}
	table->ready = 1;
	pthread_mutex_unlock(&table->death_lock);
	return (0);
}

int	init_philosophers(t_table *table, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!*philos)
		return (-1);
	i = 0;
	while (i < table->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].left_fork = &table->forks[i];
		(*philos)[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		(*philos)[i].data = table;
		i++;
	}
	table->philos = *philos;
	return (0);
}
