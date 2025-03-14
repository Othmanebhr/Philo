/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:54:12 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:31:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define ERROR_MSG_MALLOC "Malloc failed\n"
# define ERR_MUTEX_INIT "Failed to initialize mutex\n"
# define ERR_INV_ARG "Invalid args\n"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	int				nb_eat;
	bool			stop;
	unsigned int	nb_philo;
	time_t			tt_die;
	time_t			tt_sleep;
	time_t			tt_eat;
	time_t			start_time;
	t_philo			**philo;
	pthread_t		death_thread;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	writing;
	pthread_mutex_t	*fork_lock;
}	t_rules;

typedef struct s_philo
{
	time_t			last_meal;
	t_rules			*rules;
	pthread_t		thread;
	unsigned int	id;
	unsigned int	mealcount;
	unsigned int	fork[2];
	pthread_mutex_t	meal_time_lock;
	bool			mutex_init;
}	t_philo;

//parsing
int		parse_arg(int ac, char **av, t_rules **rules);
int		is_nb_of_arg_ok(int ac);
int		init_args(char **av, t_rules *rules);

//utils
int		lil_atoi(char *str);
void	free_philo(t_rules *rules);
time_t	get_time(void);
bool	has_sim_stop(t_rules *rules);
void	mutex_clean(pthread_mutex_t *forks, unsigned int nb_forks);

//utils-actions
void	print_act(t_rules *rules, char *str, int id, bool death_check);
void	smart_sleep(time_t time, t_rules *rules);
void	smart_thinking(t_philo *philo, bool first_philo);
void	sim_start_delay(time_t start_time); //a changer

//utils-clean
void	cleanup(t_rules *rules, unsigned int i);
void	cleannup2(t_rules	*rules);
void	destroy_mutexes(t_rules *rules);
void	*free_rules(t_rules *rules);
void	mutex_clean(pthread_mutex_t *forks, unsigned int nb_forks);

//alg
void	*philo_routine(void *arg);
void	*stop_checker(void *arg);
bool	has_sim_stop(t_rules *rules);

#endif