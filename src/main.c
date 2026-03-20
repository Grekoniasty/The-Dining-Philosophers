/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:44:06 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/03/16 16:30:23 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_all(t_table *table, t_philo **philos, char **av, int ac)
{
	if (parser(ac, av, table) == -1)
	{
		free(table);
		write(2, "Invalid argument values\n", 24);
		return (1);
	}
	if (init_mutexes(table) == -1)
	{
		free(table);
		write(2, "Mutex initialization failed\n", 28);
		return (1);
	}
	if (init_philosophers(table, philos) == -1)
	{
		cleanup(table, *philos);
		return (1);
	}
	if (table->time_to_die == 0)
	{
		write(1, "0 1 died\n", 9);
		return (cleanup(table, *philos), 1);
	}
	if (create_threads(table, *philos) == -1)
		return (cleanup(table, *philos), 1);
	return (0);
}

static int	run_simulation(t_table *table, t_philo *philos)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_routine, table) != 0)
	{
		pthread_mutex_lock(&table->death_lock);
		table->someone_died = 1;
		pthread_mutex_unlock(&table->death_lock);
		join_threads(table, philos);
		cleanup(table, philos);
		return (1);
	}
	pthread_join(monitor, NULL);
	join_threads(table, philos);
	cleanup(table, philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid amount of arguments\n", 29);
		return (1);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (init_all(table, &philos, av, ac) != 0)
		return (1);
	return (run_simulation(table, philos));
}
