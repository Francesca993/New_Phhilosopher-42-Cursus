/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:08:16 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:04:56 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].eta_to_die = 0;
		pthread_mutex_init(&data->forks[i].fork_lock, NULL);
		data->forks[i].in_use = 0;
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].right_fork = &(data->forks[(i + 1)
				% data->number_of_philos]);
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		return (1);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->number_of_philos);
	if (!data->forks)
		return (1);
	data->someone_died = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (1);
	if (init_philosophers(data))
		return (1);
	return (0);
}
