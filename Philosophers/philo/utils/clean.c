/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:19:56 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:25:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_clean(pthread_mutex_t *forks, unsigned int nb_forks)
{
	unsigned int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	*free_rules(t_rules *rules)
{
	unsigned int	i;

	if (!rules)
		return (NULL);
	if (rules->fork_lock != NULL)
		free(rules->fork_lock);
	if (rules->philo != NULL)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			if (rules->philo[i] != NULL)
				free(rules->philo[i]);
			i++;
		}
		free(rules->philo);
	}
	free(rules);
	return (NULL);
}

void	destroy_mutexes(t_rules *rules)
{
	unsigned int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->fork_lock[i]);
		pthread_mutex_destroy(&rules->philo[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->stop_lock);
}

void	cleannup2(t_rules	*rules)
{
	unsigned int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[i]->thread, NULL);
		i++;
	}
	if (rules->nb_philo > 1)
		pthread_join(rules->death_thread, NULL);
	destroy_mutexes(rules);
	free_rules(rules);
}

void	cleanup(t_rules *rules, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(rules->philo[j]->thread, NULL);
		j++;
	}
	j = 0;
	while (j < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->fork_lock[j]);
		if (rules->philo[j]->mutex_init)
			pthread_mutex_destroy(&rules->philo[j]->meal_time_lock);
		j++;
	}
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->stop_lock);
	free_philo(rules);
	free(rules);
}
