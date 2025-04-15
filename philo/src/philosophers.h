/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:27:49 by francesca         #+#    #+#             */
/*   Updated: 2025/04/14 11:34:04 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
#include <stdio.h>         // printf
#include <stdlib.h>        // malloc, free, atoi
#include <unistd.h>        // usleep
#include <pthread.h>       // pthreads e mutex
#include <sys/time.h>      // gettimeofday per timestamp

// ---------- Struct ---------- //

typedef struct s_philo t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
	int				in_use;
}	t_fork;
//Tutto quello che deve essere visibile a tutti i filosofi vive dentro t_data.
//Tutto il resto: tempo, forchette, mutex, filosofi
typedef struct s_data {
	int             number_of_philos;   // Numero totale di filosofi
	int        		time_to_die;        // Tempo massimo prima di morire senza mangiare (ms)
	int             time_to_eat;        // Durata del pasto (ms)
	int             time_to_sleep;      // Durata del sonno (ms)
	int             meals_required;     // Quante volte ogni filosofo deve mangiare (opzionale)
	int             someone_died;       // Flag: qualcuno è morto? (1 sì, 0 no)
	t_fork			*forks;
	pthread_mutex_t print_mutex;        // Mutex per stampare i log senza overlap
	pthread_mutex_t	death_mutex;           // thread per monitorare la morte dei filosofi
	t_philo         *philos;
} t_data;


//Ogni filosofo ha le sue info private, ma condivide i dati globali tramite *data.
//Dati di un singolo filosofo: ID, thread, stato
typedef struct s_philo {
	int             id;                 // ID del filosofo (da 1 a N)
	int             meals_eaten;        // Conteggio dei pasti (se richiesto)
	size_t          eta_to_die;      // Se questo filosofo non mangia entro time_to_eat millisecondi da ora, morirà”.
	pthread_t       thread;             // Thread associato al filosofo
	struct s_data   *data;              // Puntatore ai dati condivisi (accesso a forks, timer, ecc)
	t_fork			*left_fork;         // Puntatore al mutex della forchetta sinistra
	t_fork			*right_fork;        // Puntatore al mutex della forchetta destra
} t_philo;
//Utils function
int		ft_atoi(const char *str);
int     check_args(int argc, char **argv);
void    free_all(t_data *data);
size_t	get_time(void);
int     error_exit(char *msg, t_data *data, int exit);
//Function to init
int		init_philosophers(t_data *data);
int		init_data(t_data *data, int argc, char **argv);
int		init(t_data *data, int argc, char **argv);
//Function for routine
int		is_died(t_philo *philo);
void    *life_cicle(void *args);
void    start_routine(t_data *data);
void    message(char *msg, t_philo *philo);
//Action
int		smart_sleep(size_t duration, t_philo *philo);
int		take_fork(t_fork *fork, t_philo *philo);
void    p_death(t_philo *philo);
int     p_think(t_philo *philo);
int     p_sleep(t_philo *philo);
int		p_eat(t_philo *philo);



#endif