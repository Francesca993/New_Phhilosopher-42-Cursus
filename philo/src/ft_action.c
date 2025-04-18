/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:57:49 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:02:43 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Each time he eats, resets the maximum time by which he must eat again
// She sleeps for the time it takes to “eat”
int	p_eat(t_philo *philo)
{
	if (take_fork(philo->right_fork, philo) || take_fork(philo->left_fork,
			philo))
		return (1);
	philo->eta_to_die = get_time() + philo->data->time_to_die;
	if (is_died(philo))
		return (1);
	message("is eating\n", philo);
	if (smart_sleep(philo->data->time_to_eat, philo))
		return (1);
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	philo->right_fork->in_use = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_lock);
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	philo->left_fork->in_use = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_lock);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	if (is_died(philo))
		return (1);
	message("is sleeping\n", philo);
	if (smart_sleep(philo->data->time_to_sleep, philo))
		return (1);
	return (0);
}

int	p_think(t_philo *philo)
{
	if (is_died(philo))
		return (1);
	message("is thinking\n", philo);
	return (0);
}

void	p_death(t_philo *philo)
{
	if (philo->data->someone_died == 0)
	{
		message("died\n", philo);
		philo->data->someone_died = 1;
	}
}
