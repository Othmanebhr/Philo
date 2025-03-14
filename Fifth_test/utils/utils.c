/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:54:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/19 11:54:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_act(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->writing));
	if (!rules->stop)
		printf("%lld	philosopher %d %s\n",
			current_time_in_ms() - rules->start_time, id, str);
	pthread_mutex_unlock(&(rules->writing));
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long	save_start_time;

	save_start_time = current_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&rules->writing);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->writing);
			break ;
		}
		pthread_mutex_unlock(&rules->writing);
		if (current_time_in_ms() - save_start_time > time)
			break ;
		usleep(50);
	}
}

void	free_philo(t_philo **philo)
{
	t_philo	*first;
	t_philo	*next;
	t_philo	*current;

	if (!*philo)
		return ;
	first = *philo;
	current = *philo;
	while (1)
	{
		next = current->next;
		pthread_mutex_destroy(&current->self_mutex);
		free(current);
		if (next == first)
			break ;
		current = next;
	}
	*philo = NULL;
}

long long	current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
