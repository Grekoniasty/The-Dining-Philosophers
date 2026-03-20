/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 00:00:00 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/03/10 00:00:00 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_ready(t_philo *philo)
{
	int	ready;

	pthread_mutex_lock(&philo->data->death_lock);
	ready = philo->data->ready;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (ready);
}

void	stagger_philo(t_philo *philo)
{
	int	is_last_odd;

	is_last_odd = (philo->data->num_philos % 2 != 0
			&& philo->id == philo->data->num_philos);
	if (philo->id % 2 == 0 || is_last_odd)
	{
		usleep(500);
		print_status(philo, "is thinking");
		if (is_last_odd)
			ft_usleep(philo->data->time_to_eat * 2);
		else
			ft_usleep(philo->data->time_to_eat);
	}
}
