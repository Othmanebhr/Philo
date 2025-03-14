/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:20:42 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:28:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork_lock[philo->fork[0]]);
	print_act(philo->rules, FORK, philo->id, false);
	pthread_mutex_lock(&philo->rules->fork_lock[philo->fork[1]]);
	print_act(philo->rules, FORK, philo->id, false);
	print_act(philo->rules, EAT, philo->id, false);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	smart_sleep(philo->rules->tt_eat, philo->rules);
	if (has_sim_stop(philo->rules) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->mealcount++;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_act(philo->rules, SLEEP, philo->id, false);
	pthread_mutex_unlock(&philo->rules->fork_lock[philo->fork[0]]);
	pthread_mutex_unlock(&philo->rules->fork_lock[philo->fork[1]]);
	smart_sleep(philo->rules->tt_sleep, philo->rules);
}

static	void	*so_lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork_lock[philo->fork[0]]);
	print_act(philo->rules, FORK, philo->id, false);
	smart_sleep(philo->rules->tt_die, philo->rules);
	print_act(philo->rules, DIED, philo->id, false);
	pthread_mutex_unlock(&philo->rules->fork_lock[philo->fork[0]]);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->nb_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->rules->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->rules->start_time);
	if (philo->rules->tt_die == 0)
		return (NULL);
	if (philo->rules->nb_philo == 1)
		return (so_lonely_philo(philo));
	else if (philo->id % 2)
		smart_thinking(philo, true);
	while (has_sim_stop(philo->rules) == false)
	{
		routine(philo);
		smart_thinking(philo, false);
	}
	return (NULL);
}
