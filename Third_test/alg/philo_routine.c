/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:46:17 by root              #+#    #+#             */
/*   Updated: 2025/02/24 21:46:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->rules->nb_philo == 1)
	{
		print_act(philo->rules, 1, "has taken a fork.");//a voir si il ne doit pas manger aussi
		smart_sleep(philo->rules->tt_die, philo->rules);
		print_act(philo->rules, 1, "died.");
		return (NULL);
	}
	if (philo->index % 2 == 0)
		usleep(15000); //15 ms usleep prends des microseconde
	while(!philo->rules->stop)
	{
		pthread_mutex_lock(philo->left_fork); // prendre les fourchettes
		print_act(philo->rules, philo->index, "has taken a fork.");
		pthread_mutex_lock(&philo->self_mutex);
		print_act(philo->rules, philo->index, "has taken a fork.");

		pthread_mutex_lock(&(philo->rules->meal_check));
		print_act(philo->rules, philo->index, "is eating.");
		philo->last_meal = current_time_in_ms();
		philo->meal_count++;
		pthread_mutex_unlock(&(philo->rules->meal_check));
		smart_sleep(philo->rules->tt_eat, philo->rules); // a voir le *1000
		
		pthread_mutex_unlock(philo->left_fork);//ajouter une virgule au besoin
		pthread_mutex_unlock(&philo->self_mutex);

		print_act(philo->rules, philo->index, "is sleeping.");
		smart_sleep(philo->rules->tt_sleep, philo->rules);
		print_act(philo->rules, philo->index, "is thinking.");
	}
	return (NULL);
}
