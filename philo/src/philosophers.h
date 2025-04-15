/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:27:49 by francesca         #+#    #+#             */
/*   Updated: 2025/04/15 14:12:01 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>  // pthreads e mutex
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free, atoi
# include <sys/time.h> // gettimeofday per timestamp
# include <unistd.h>   // usleep

// ---------- Struct ---------- //

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork_lock;
	int					in_use;
}						t_fork;

/*
Everything that should be visible to all philosophers lives inside t_data.
Everything else: time, forks, mutexes, philosophers
Total number of philosophers
Maximum time before dying without eating (ms)
Duration of meal (ms)
Duration of sleep (ms)
How many times each philosopher must eat (optional)
 Flag: did someone die? (1 yes, 0 no)
Mutex to print logs without overlap
Thread to monitor death of philosophers
*/
typedef struct s_data
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_required;
	int					someone_died;
	t_fork				*forks;
	pthread_mutex_t print_mutex; //
	pthread_mutex_t death_mutex; //
	t_philo				*philos;
}						t_data;

/*
Each philosopher has his own private info,
but shares global data via *data.
Data of a single philosopher: ID, thread, state
Philosopher's ID (1 to N)
Meal count (if required)
If this philosopher does not eat within time_to_eat milliseconds from now,
	he will die.”
Thread associated with philosopher
Pointer to shared data (access to forks, timers, etc.)
Pointer to left fork mutex
Pointer to the mutex of the right fork

*/
typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	size_t				eta_to_die;
	pthread_t			thread;
	struct s_data		*data;
	t_fork				*left_fork;
	t_fork				*right_fork;
}						t_philo;
// Utils function
int						ft_atoi(const char *str);
int						check_args(int argc, char **argv);
void					free_all(t_data *data);
size_t					get_time(void);
int						error_exit(char *msg, t_data *data, int exit);
// Function to init
int						init_philosophers(t_data *data);
int						init_data(t_data *data, int argc, char **argv);
int						init(t_data *data, int argc, char **argv);
// Function for routine
int						is_died(t_philo *philo);
void					*life_cicle(void *args);
void					start_routine(t_data *data);
void					message(char *msg, t_philo *philo);
// Action
int						smart_sleep(size_t duration, t_philo *philo);
int						take_fork(t_fork *fork, t_philo *philo);
void					p_death(t_philo *philo);
int						p_think(t_philo *philo);
int						p_sleep(t_philo *philo);
int						p_eat(t_philo *philo);

#endif