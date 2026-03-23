/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:25:58 by mpiasecz          #+#    #+#             */
/*   Updated: 2026/03/23 22:36:58 by mpiasecz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	*array_filler(char **av, int ac)
{
	int	*d;
	int	i;

	d = malloc(sizeof(int) * (ac - 1));
	if (!d)
		return (NULL);
	i = 0;
	while (i < ac - 1)
	{
		d[i] = ft_atol(av[i + 1]);
		if (d[i] < 0)
		{
			free(d);
			return (NULL);
		}
		i++;
	}
	return (d);
}

int	parser(int ac, char **av, t_table *table)
{
	int	*d;

	d = array_filler(av, ac);
	if (!d)
		return (-1);
	table->num_philos = d[0];
	if (table->num_philos == 0 || table->num_philos > 250)
	{
		free(d);
		write(2, "Incorrect amount of philosophers\n", 33);
		return (-1);
	}
	table->time_to_die = d[1];
	table->time_to_eat = d[2];
	table->time_to_sleep = d[3];
	if (ac == 6)
	{
		if (d[4] == 0)
			return (free(d), -1);
		table->num_must_eat = d[4];
	}
	else
		table->num_must_eat = -1;
	free(d);
	return (0);
}
