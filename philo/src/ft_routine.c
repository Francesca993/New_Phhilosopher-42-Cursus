/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:45:46 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:06:05 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	else if (philo->eta_to_die < get_time())
	{
		p_death(philo);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

// If the end time exceeds the time of death...
// He calculates the time he has left to live
// If he is already dead (eta_death in the past), he does not sleep
/// She only sleeps until death
// Protection on writing death_flag
int	smart_sleep(size_t duration, t_philo *philo)
{
	size_t	start_time;

	start_time = get_time();
	if (start_time + duration > philo->eta_to_die)
	{
		duration = philo->eta_to_die - start_time;
		if (philo->eta_to_die < start_time)
			duration = 0;
		usleep(duration * 1000);
		pthread_mutex_lock(&philo->data->death_mutex);
		p_death(philo);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	usleep(duration * 1000);
	return (0);
}

void	*life_cicle(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->eta_to_die = get_time() + philo->data->time_to_die;
	if (philo->id % 2 == 0)
	{
		if (smart_sleep(philo->data->time_to_eat / 3, philo))
			return (NULL);
	}
	while (philo->meals_eaten != philo->data->meals_required)
	{
		if (is_died(philo))
			return (NULL);
		if (p_eat(philo) || p_sleep(philo) || p_think(philo))
			return (NULL);
		if (philo->data->meals_required != -1)
			philo->meals_eaten++;
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, life_cicle,
				&data->philos[i]))
			error_exit("Fail pthread_create", data, 1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			error_exit("Fail pthread_join", data, 1);
		i++;
	}
}
