/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:54:20 by root              #+#    #+#             */
/*   Updated: 2024/11/29 12:12:16 by root             ###   ########.fr       */
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

	while (*philo != NULL)
	{
		temp = (*philo)->next;
		pthread_mutex_destroy(&(*philo)->self_mutex);
		free(*philo);
		*philo = temp;
	}
}

long long	current_time_in_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long long)now.tv_sec * 1000 + now.tv_usec / 1000);
}