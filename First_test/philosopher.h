/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:29:13 by root              #+#    #+#             */
/*   Updated: 2024/11/29 11:58:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_rule 
{
	int				nb_of_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_of_time_eating;
}	t_rule;

typedef struct t_philo
{
	int				state; // 0 = Reflexion, 1 = Mange, 2 = Sleep
	int				index;
	int				meals_count;
	long long		last_meal_time;
	struct t_philo	*next;
	struct t_philo	*prev;
	t_rule			*rules;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	self_mutex;
}	t_philo;

//utils
int			lil_atoi(char *str);
void		free_philo(t_philo **philo);
long long	current_time_in_ms(void);

//Parsing
int			parse_arg(char **av, t_rule *rules);

//Fill chain_list philo
int			fill_philo(t_philo **philo, t_rule *rules, int index_of_philo);

//actions
void		think(t_philo *philo);
void		pick_up_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);

#endif