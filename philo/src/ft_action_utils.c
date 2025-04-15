/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:23:14 by francesca         #+#    #+#             */
/*   Updated: 2025/04/13 17:53:35 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    message(char *msg, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%lu %d %s", get_time(), philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int take_fork(t_fork *fork, t_philo *philo)
{
    while (1)
    {
        // Controlla se il filosofo è morto prima di continuare
        if (is_died(philo))
            return (1);

        pthread_mutex_lock(&fork->fork_lock);
        if (fork->in_use == 0)
        {
            fork->in_use = 1;
            pthread_mutex_unlock(&fork->fork_lock);

            // Stampa il messaggio dopo aver preso la forchetta
            message("has taken a fork\n", philo);
            return (0);
        }
        pthread_mutex_unlock(&fork->fork_lock);

        // Usa uno sleep più breve per evitare starvation
        if (smart_sleep(1, philo))
            return (1);
    }
}