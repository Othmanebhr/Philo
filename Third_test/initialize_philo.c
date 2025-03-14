/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:17:45 by marvin            #+#    #+#             */
/*   Updated: 2025/02/19 12:17:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*initialize_philo(t_rules *rules, int index)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->state = 0;
	new_philo->index = index + 1;
	new_philo->meal_count = 0;
	new_philo->rules = rules;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	new_philo->left_fork = NULL; 
	if (pthread_mutex_init(&new_philo->self_mutex, NULL) != 0)
		return(free(new_philo), NULL);
	new_philo->last_meal = current_time_in_ms();
	return ((t_philo *)new_philo);
}

int	fill_philo(t_philo **philo, t_rules *rules, int idx_of_philo) //bien revoir pourquoi un double pointeur
{
	t_philo	*new_philo;
	t_philo	*temp;

	new_philo = initialize_philo(rules, idx_of_philo);
	if (!new_philo)
		return (-1);
	if (!*philo)
	{
		*philo = new_philo;
		new_philo->next = new_philo;
		new_philo->prev = new_philo;
		rules->philo = new_philo;
	}
	else
	{
		temp = (*philo)->prev;
		temp->next = new_philo;
		new_philo->prev = temp;
		new_philo->next = *philo;
		(*philo)->prev = new_philo;
	}
	if (!*philo)//a voir si on ne renvoie pas une erreur si il n'y a qu'un seul philo (1 seul fourchette, va donc mourrir)
		new_philo->left_fork = &new_philo->self_mutex;
	else
		new_philo->left_fork = &new_philo->prev->self_mutex;
	return (0);
}
