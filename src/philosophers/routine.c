/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:34:05 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/03/10 00:00:00 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

static void	eat(t_philo *philo)
{
	long	t;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (!philo->data->someone_died)
	{
		t = get_time() - philo->data->start_time;
		if (t <= philo->data->last_printed_timestamp)
			t = philo->data->last_printed_timestamp + 1;
		philo->data->last_printed_timestamp = t;
		printf("%ld %d has taken a fork\n", t, philo->id);
		printf("%ld %d has taken a fork\n", t, philo->id);
		printf("%ld %d is eating\n", t, philo->id);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
	ft_usleep(philo->data->time_to_eat);
}

static void	sleep_and_think(t_philo *philo)
{
	long	think_t;

	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
	think_t = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (think_t < 0)
		think_t = 0;
	ft_usleep(think_t / 2);
}

static int	philo_cycle(t_philo *philo)
{
	take_forks(philo);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	eat(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (check_death(philo))
		return (1);
	sleep_and_think(philo);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_ready(philo))
		usleep(100);
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	stagger_philo(philo);
	while (!check_death(philo))
	{
		if (philo_cycle(philo))
			break ;
	}
	return (NULL);
}
