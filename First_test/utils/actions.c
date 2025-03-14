/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:14:27 by root              #+#    #+#             */
/*   Updated: 2024/12/01 15:17:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	think(t_philo *philo)
{
	printf("Philosopher %d is thinking.\n", philo->index);
	usleep(philo->rules->tt_sleep * 1000);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d has taken forks.\n", philo->index);
}

void eat(t_philo *philo)
{
	printf("Philosopher %d is eating.\n", philo->index);
	philo->last_meal_time = current_time_in_ms();
	philo->meals_count++;
	usleep(philo->rules->tt_eat * 1000);
}


void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d has put down forks.\n", philo->index);
}

void	sleep_philo(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->index);
	usleep(philo->rules->tt_sleep * 1000);
}
