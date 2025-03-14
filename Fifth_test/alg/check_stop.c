/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:03:52 by marvin            #+#    #+#             */
/*   Updated: 2025/02/21 19:03:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	if_death(t_rules *rules, t_philo *current)
{
	pthread_mutex_lock(&rules->writing);
	printf("%lld	philosopher %d died\n",
		current_time_in_ms() - rules->start_time, current->index);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->writing);
	pthread_mutex_unlock(&rules->meal_check);
}

static int	check_all_philosophers_ate(t_rules *rules)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = rules->philo;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&(rules->meal_check));
		if (current->meal_count < rules->nb_eat)
		{
			pthread_mutex_unlock(&(rules->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->meal_check));
		current = current->next;
		i++;
	}
	return (i == rules->nb_philo);
}

static int	is_eating_ok(t_rules *rules)
{
	if (rules->nb_eat > 0)
	{
		if (check_all_philosophers_ate(rules))
		{
			pthread_mutex_lock(&rules->writing);
			rules->stop = 1;
			pthread_mutex_unlock(&rules->writing);
			return (-1);
		}
	}
	return (0);
}

void	*stop_checker(void *arg)
{
	t_rules	*rules;
	t_philo	*current;
	int		i;

	rules = (t_rules *)arg;
	while (!rules->stop)
	{
		current = rules->philo;
		i = 0;
		while (i < rules->nb_philo && !rules->stop)
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (current_time_in_ms() - current->last_meal > rules->tt_die)
				return (if_death(rules, current), NULL);
			pthread_mutex_unlock(&(rules->meal_check));
			current = current->next;
			i++;
		}
		if (is_eating_ok(rules) != 0)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
