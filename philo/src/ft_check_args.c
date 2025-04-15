/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:32:29 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:04:12 by fmontini         ###   ########.fr       */
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
int	check_args(int argc, char **argv)
{
	int	n_philo;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of parameters.\n");
		return (1);
	}
	n_philo = ft_atoi(argv[1]);
	if ((n_philo <= 0) || (n_philo > 200))
		return (printf("Philosophers must be more than 0 and less than 200.\n"),
			1);
	if (ft_atoi(argv[2]) <= 0)
		return (printf("Invalid time to die.\n"), 1);
	if (ft_atoi(argv[3]) <= 0)
		return (printf("Invalid time to eat.\n"), 1);
	if (ft_atoi(argv[4]) <= 0)
		return (printf("Invalid time to sleep.\n"), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0))
		return (printf("Invalid number of meals.\n"), 1);
	return (0);
}
