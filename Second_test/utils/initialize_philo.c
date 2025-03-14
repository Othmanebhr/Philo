/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:41:31 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:46:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

static t_philo *initialize_philo(int index_of_philo, t_rule *rules)
{
    t_philo *new_philo;

    new_philo = malloc(sizeof(t_philo));
    if (!new_philo)
        return (NULL);
    if (pthread_mutex_init(&new_philo->self_mutex, NULL) != 0)
    {
        free(new_philo);
        return (NULL);
    }
    new_philo->death_mutex = malloc(sizeof(pthread_mutex_t));
    if (!new_philo->death_mutex || pthread_mutex_init(new_philo->death_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&new_philo->self_mutex);
        free(new_philo);
        return (NULL);
    }
    new_philo->someone_died = malloc(sizeof(int));
    if (!new_philo->someone_died)
    {
        pthread_mutex_destroy(&new_philo->self_mutex);
        pthread_mutex_destroy(new_philo->death_mutex);
        free(new_philo->death_mutex);
        free(new_philo);
        return (NULL);
    }
    *new_philo->someone_died = 0;
    new_philo->state = 0;
    new_philo->index = index_of_philo;
    new_philo->meals_count = 0;
    new_philo->last_meal_time = current_time_in_ms();
    new_philo->rules = rules;
    new_philo->prev = NULL;
    new_philo->next = NULL;
    return (new_philo);
}

int	fill_philo(t_philo **philo, t_rule *rules, int index_of_philo)
{
	t_philo	*temp;
	t_philo	*new_philo;

	new_philo = initialize_philo(index_of_philo, rules);
	if (!new_philo)
		return (-1);
	if (!*philo)
	{
		*philo = new_philo;
		new_philo->next = new_philo;
		new_philo->prev = new_philo;
	}
	else
	{
		temp = (*philo)->prev;
		temp->next = new_philo;
		new_philo->prev = temp;
		new_philo->next = *philo;
		(*philo)->prev = new_philo;
	}
	if (new_philo->next == new_philo) // Si un seul philosophe
	{
		new_philo->left_fork = &new_philo->self_mutex;
		new_philo->right_fork = &new_philo->self_mutex;
	}
	else
	{
		new_philo->left_fork = &new_philo->prev->self_mutex;
		new_philo->right_fork = &new_philo->self_mutex;
	}
	return (0);
}
