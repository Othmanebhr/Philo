/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:14:58 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:21:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void print_status(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->death_mutex);
	if (!*philo->someone_died)
		printf("%lld %d %s\n", 
			current_time_in_ms() - philo->rules->start_time,
			philo->index,
			message);
	pthread_mutex_unlock(philo->death_mutex);
}
