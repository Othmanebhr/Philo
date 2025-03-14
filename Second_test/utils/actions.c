/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:14:27 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:49:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void pick_up_forks(t_philo *philo)
{
    if (philo->index % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void think(t_philo *philo)
{
    pthread_mutex_lock(philo->death_mutex);
    print_status(philo, "is thinking");
    pthread_mutex_unlock(philo->death_mutex);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->self_mutex);
    pthread_mutex_lock(philo->death_mutex);
    philo->last_meal_time = current_time_in_ms();
    print_status(philo, "is eating");
    philo->meals_count++;
    pthread_mutex_unlock(philo->death_mutex);
    pthread_mutex_unlock(&philo->self_mutex);
    if (!*philo->someone_died)
        usleep(philo->rules->tt_eat * 1000);
}

void sleep_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->death_mutex);
    print_status(philo, "is sleeping");
    pthread_mutex_unlock(philo->death_mutex);
    if (!*philo->someone_died)
        usleep(philo->rules->tt_sleep * 1000);
}

