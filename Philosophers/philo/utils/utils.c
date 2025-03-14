/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 02:39:54 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:23:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philo(t_rules *rules)
{
	unsigned int	i;

	if (!rules || !rules->philo)
		return ;
	if (rules->fork_lock != NULL)
		free(rules->fork_lock);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->philo[i])
		{
			if (rules->philo[i]->mutex_init == true)
				pthread_mutex_destroy(&rules->philo[i]->meal_time_lock);
			free(rules->philo[i]);
		}
		i++;
	}
	free(rules->philo);
}

int	lil_atoi(char *str)
{
	int				i;
	unsigned long	res;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return (-1);
	return (res);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	has_sim_stop(t_rules *rules)
{
	bool	is_finish;

	is_finish = false;
	pthread_mutex_lock(&rules->stop_lock);
	if (rules->stop == true)
		is_finish = true;
	pthread_mutex_unlock(&rules->stop_lock);
	return (is_finish);
}

void	sim_start_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}
