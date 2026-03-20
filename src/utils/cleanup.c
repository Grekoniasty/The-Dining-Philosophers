/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:50:50 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/03/10 19:52:22 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	free(table->forks);
	free(philos);
	free(table);
}
