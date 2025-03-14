/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:39:14 by root              #+#    #+#             */
/*   Updated: 2025/02/27 19:16:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	cleanup_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->meal_check);
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	free(rules->forks);
}
