/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:22:03 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:29:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	stop_flag(t_rules *rules, bool state)
{
	pthread_mutex_lock(&rules->stop_lock);
	rules->stop = state;
	pthread_mutex_unlock(&rules->stop_lock);
}

static int	philo_dead(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->rules->tt_die)
	{
		stop_flag(philo->rules, true);
		print_act(philo->rules, DIED, philo->id, true);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	return (0);
}

static bool	is_stopped(t_rules *rules)
{
	unsigned int	i;
	bool			all_ate;

	i = 0;
	all_ate = true;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philo[i]->meal_time_lock);
		if (philo_dead(rules->philo[i]) != 0)
			return (true);
		if (rules->nb_eat != -1)
			if (rules->philo[i]->mealcount < (unsigned int)rules->nb_eat)
				all_ate = false;
		pthread_mutex_unlock(&rules->philo[i]->meal_time_lock);
		i++;
	}
	if (rules->nb_eat != -1 && all_ate == true)
	{
		stop_flag(rules, true);
		return (true);
	}
	return (false);
}

void	*stop_checker(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	if (rules->nb_eat == 0)
		return (NULL);
	stop_flag(rules, false);
	sim_start_delay(rules->start_time);
	while (1)
	{
		if (is_stopped(rules) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
