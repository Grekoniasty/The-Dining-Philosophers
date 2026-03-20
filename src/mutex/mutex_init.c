/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:18:55 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/02/02 12:22:51 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

int	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (-1);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (cleanup_forks(table, i), -1);
		i++;
	}
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (cleanup_forks(table, table->num_philos), -1);
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		return (cleanup_forks(table, table->num_philos), -1);
	}
	table->someone_died = 0;
	return (0);
}
