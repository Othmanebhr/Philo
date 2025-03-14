/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:34:59 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:29:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_fork(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->rules->nb_philo;
	if (philo->id % 2 == 0)
	{
		philo->fork[1] = philo->id;
		philo->fork[0] = (philo->id + 1) % philo->rules->nb_philo;
	}
}

static int	init_philo(t_rules *rules)
{
	unsigned int	i;

	i = 0;
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philo)
		return (printf("%s", ERROR_MSG_MALLOC), -1);
	while (i < rules->nb_philo)
	{
		rules->philo[i] = malloc(sizeof(t_philo));
		if (!rules->philo[i])
			return (printf("%s", ERROR_MSG_MALLOC), free_philo(rules), -1);
		if (pthread_mutex_init(&rules->philo[i]->meal_time_lock, 0) != 0)
			return (printf("%s", ERR_MUTEX_INIT), free_philo(rules), -1);
		rules->philo[i]->mutex_init = true;
		rules->philo[i]->id = i;
		rules->philo[i]->rules = rules;
		rules->philo[i]->mealcount = 0;
		assign_fork(rules->philo[i]);
		i++;
	}
	return (0);
}

static pthread_mutex_t	*init_forks(t_rules *rules)
{
	unsigned int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!forks)
		return (NULL);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			mutex_clean(forks, i);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static int	init_mutex(t_rules *rules)
{
	if (pthread_mutex_init(&rules->stop_lock, 0) != 0)
		return (printf("%s", ERR_MUTEX_INIT), -1);
	if (pthread_mutex_init(&rules->writing, 0) != 0)
	{
		pthread_mutex_destroy(&rules->stop_lock);
		printf("%s", ERR_MUTEX_INIT);
		return (-1);
	}
	rules->fork_lock = init_forks(rules);
	if (!rules->fork_lock)
	{
		pthread_mutex_destroy(&rules->stop_lock);
		pthread_mutex_destroy(&rules->writing);
		printf("Failed to init forks\n");
		return (-1);
	}
	return (0);
}

int	parse_arg(int ac, char **av, t_rules **rules)
{
	*rules = malloc(sizeof(t_rules));
	if (!*rules)
		return (printf(ERROR_MSG_MALLOC), -1);
	if (is_nb_of_arg_ok(ac) != 0)
		return (free(*rules), *rules = NULL, -1);
	if (init_args(av, *rules) != 0)
		return (free(*rules), *rules = NULL, -1);
	if (init_philo(*rules) != 0)
		return (free(*rules), *rules = NULL, -1);
	if (init_mutex(*rules))
		return (free(*rules), *rules = NULL, -1);
	(*rules)->stop = false;
	return (0);
}
