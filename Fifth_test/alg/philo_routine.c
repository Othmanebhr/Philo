/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:46:17 by root              #+#    #+#             */
/*   Updated: 2025/02/28 15:38:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	*handle_single_philo(t_philo *philo)
{
	print_act(philo->rules, 1, "has taken a fork");
	smart_sleep(philo->rules->tt_die, philo->rules);
	pthread_mutex_lock(&philo->rules->meal_check);
	pthread_mutex_lock(&philo->rules->writing);
	if (!philo->rules->stop)
	{
		printf("%lld	philosopher %d died\n",
			current_time_in_ms() - philo->rules->start_time, 1);
		philo->rules->stop = 1;
	}
	pthread_mutex_unlock(&philo->rules->writing);
	pthread_mutex_unlock(&philo->rules->meal_check);
	return (NULL);
}

static int	try_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->self_mutex);
	print_act(philo->rules, philo->index, "has taken a fork");
	pthread_mutex_lock(&(philo->rules->meal_check));
	print_act(philo->rules, philo->index, "is eating");
	philo->last_meal = current_time_in_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->rules->meal_check));
	if (!philo->rules->stop)
		smart_sleep(philo->rules->tt_eat, philo->rules);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->self_mutex);
	return (1);
}

static int	philo_sleep_and_think(t_philo *philo)
{
	if (philo->rules->stop)
		return (1);
	print_act(philo->rules, philo->index, "is sleeping");
	if (!philo->rules->stop)
		smart_sleep(philo->rules->tt_sleep, philo->rules);
	if (philo->rules->stop)
		return (1);
	print_act(philo->rules, philo->index, "is thinking");
	if (philo->index % 2)
		usleep(5000);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		eating_status;

	philo = (t_philo *) arg;
	if (philo->rules->nb_philo == 1)
		return (handle_single_philo(philo));
	if (philo->index % 2)
		usleep(5000);
	while (!philo->rules->stop)
	{
		pthread_mutex_lock(philo->left_fork);
		print_act(philo->rules, philo->index, "has taken a fork");
		eating_status = try_to_eat(philo);
		if (eating_status && philo_sleep_and_think(philo))
			break ;
		else if (!eating_status)
			pthread_mutex_unlock(philo->left_fork);
	}
	return (NULL);
}
