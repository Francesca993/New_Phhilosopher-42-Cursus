/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:25:21 by francesca         #+#    #+#             */
/*   Updated: 2025/04/10 10:45:32 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	argvs[1-5]:
	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]
*/

void	print_usage(void)
{
	printf("usage: philo \t[number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep]\n\
\t\t[number_of_times_each_philosopher_must_eat]\n");
}

int main(int argc, char **argv)
{
    t_data  data;
    
    if (check_args(argc, argv) == 1)
        return (print_usage(), 1);
    if (init(&data, argc, argv) == 1)
        return (1);
	start_routine(&data);
	free_all(&data);
    return (0);
}