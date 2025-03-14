/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:28:53 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 19:28:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ERROR_MSG "Error:"

typedef struct s_philo
{
	int				state;
	int				index;
	int				meal_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	self_mutex;
	long long		last_meal;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_rules	*rules;
} t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_eat;
	int				stop;
	long long		start_time;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	*forks;
	struct s_philo	*philo; // a définir
} t_rules;


//Parsing
int			parse_arg(int ac, char **av, t_rules *rules);

//Liste chainées circulaire
int			fill_philo(t_philo **philo, t_rules *rules, int idx_of_philo);

//Algo
void		*philo_routine(void *arg);
void		*stop_checker(void *arg);

//utils
void		ft_error(int status, char *str);
void		free_philo(t_philo **philo);
void		cleanup_mutexes(t_rules *rules);
long long	current_time_in_ms(void);
void		print_act(t_rules *rules, int id, char *str);
void		smart_sleep(long long time, t_rules *rules);

#endif