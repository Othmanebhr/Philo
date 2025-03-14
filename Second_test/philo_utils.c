/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:54:20 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:14:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	lil_atoi(char *str)
{
	unsigned long	res;
	int				i;

	i = 0;
	res = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return(-1);
	return (res);
}

void free_philo(t_philo **philo)
{
	t_philo *temp;
	t_philo *first;

	if (!*philo)
		return;
	first = *philo;
	temp = *philo;
	do {
		temp = (*philo)->next;
		// Détruire les mutex
		pthread_mutex_destroy(&(*philo)->self_mutex);
		if ((*philo)->death_mutex)
		{
			pthread_mutex_destroy((*philo)->death_mutex);
			free((*philo)->death_mutex);
		}
		// Libérer la mémoire
		if ((*philo)->someone_died)
			free((*philo)->someone_died);
		free(*philo);
		*philo = temp;
	} while (*philo && *philo != first);//a changer

	*philo = NULL;
}

long long	current_time_in_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long long)now.tv_sec * 1000 + now.tv_usec / 1000);
}