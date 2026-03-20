/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:28:02 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/02/02 12:19:23 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_lock);
	dead = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (dead);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died)
	{
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			status);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static int	check_one_philo(t_table *table, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&table->death_lock);
	time_since_meal = get_time() - table->philos[i].last_meal_time;
	if (time_since_meal >= table->time_to_die)
	{
		table->someone_died = 1;
		pthread_mutex_unlock(&table->death_lock);
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n", get_time() - table->start_time,
			table->philos[i].id);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->death_lock);
	return (0);
}

static int	check_all_ate(t_table *table)
{
	int	i;

	if (table->num_must_eat == -1)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->philos[i].meals_eaten < table->num_must_eat)
		{
			pthread_mutex_unlock(&table->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->death_lock);
		i++;
	}
	pthread_mutex_lock(&table->death_lock);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_lock);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (check_one_philo(table, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(table))
			return (NULL);
		usleep(1000);
	}
}
