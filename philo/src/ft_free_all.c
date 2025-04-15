/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:06:13 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:04:30 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	error_exit(char *msg, t_data *data, int exit)
{
	printf("Error %d: %s\n", exit, msg);
	if (data)
		free_all(data);
	return (exit);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_exit("gettimeofday() error\n", NULL, 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
