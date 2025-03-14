/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:58:41 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:27:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	thread_alg(t_rules	*rules)
{
	unsigned int	i;

	i = 0;
	rules->start_time = get_time() + (rules->nb_philo * 2 * 10);
	while (i < rules->nb_philo)
	{
		rules->philo[i]->last_meal = rules->start_time;
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i]->thread, NULL,
				&philo_routine, rules->philo[i]) != 0)
			return (printf("Failed to init routine"), cleanup(rules, i), -1);
		i++;
	}
	if (rules->nb_philo > 1)
	{
		if (pthread_create(&rules->death_thread, NULL,
				&stop_checker, rules) != 0)
			return (printf("Failed to init stop check"), cleanup(rules, i), -1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = NULL;
	if (parse_arg(ac, av, &rules) != 0)
		return (1);
	if (thread_alg(rules) != 0)
		return (1);
	cleannup2(rules);
	return (0);
}
