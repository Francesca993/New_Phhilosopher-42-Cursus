/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:45:46 by francesca         #+#    #+#             */
/*   Updated: 2025/04/11 09:50:55 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int is_died(t_philo *philo)
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

int     smart_sleep(size_t duration, t_philo *philo)
{
    size_t start_time;

    start_time = get_time();
    // ⏱️ Se il tempo di fine supera il momento di morte...
    if (start_time + duration > philo->eta_to_die)
    {
        // Calcola il tempo che gli resta da vivere
        duration = philo->eta_to_die - start_time;
        // Se è già morto (eta_death nel passato), non dorme
        if (philo->eta_to_die < start_time)
            duration = 0;
        //dorme solo fino alla morte
        usleep(duration * 1000);
        // Protezione su scrittura di death_flag
        pthread_mutex_lock(&philo->data->death_mutex);
        p_death(philo);
        pthread_mutex_unlock(&philo->data->death_mutex);
        return(1);
    }
    usleep(duration * 1000);
    return (0);
}

void    *life_cicle(void *args)
{
    t_philo *philo;

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

void    start_routine(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, life_cicle, &data->philos[i]))
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