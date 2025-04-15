/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:23:14 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:01:40 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu %d %s", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// Check if the philosopher is dead before continuing
// Print the message after taking the fork
// Use a shorter sleep to avoid starvation
int	take_fork(t_fork *fork, t_philo *philo)
{
	while (1)
	{
		if (is_died(philo))
			return (1);
		pthread_mutex_lock(&fork->fork_lock);
		if (fork->in_use == 0)
		{
			fork->in_use = 1;
			pthread_mutex_unlock(&fork->fork_lock);
			message("has taken a fork\n", philo);
			return (0);
		}
		pthread_mutex_unlock(&fork->fork_lock);
		if (smart_sleep(1, philo))
			return (1);
	}
}
