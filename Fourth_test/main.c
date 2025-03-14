/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:43:43 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 19:43:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_philo_threads(pthread_t *thr, t_philo *philo, t_rules *rules)
{
	int		i;
	t_philo	*current;

	i = 0;
	current = philo;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&thr[i], NULL, philo_routine, current) != 0)
		{
			rules->stop = 1;
			while (--i >= 0)
				pthread_join(thr[i], NULL);
			return (-1);
		}
		current = current->next;
		i++;
	}
	return (0);
}

static int thread_alg(t_philo **philo, t_rules *rules)
{
	int			i;
	pthread_t	death_thread;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * rules->nb_philo);
	if (!threads)
		return (-1);
	if (create_philo_threads(threads, *philo, rules) != 0)
		return (free(threads), -1);
	if (pthread_create(&death_thread, NULL, stop_checker, rules) != 0)
	{
		rules->stop = 1;
		i = 0;
		while (i < rules->nb_philo)
			pthread_join(threads[i++], NULL);
		return (free(threads), -1);
	}
	pthread_join(death_thread, NULL);
	i = 0;
	while (i < rules->nb_philo)
		pthread_join(threads[i++], NULL);
	free(threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	t_philo	*philo;
	int		i;

	philo = NULL;
	if (parse_arg(ac, av, &rules) != 0)
		ft_error(EXIT_FAILURE, "Invalid Arguments.");
	i = 0;
	while (i < rules.nb_philo)
	{
		if (fill_philo(&philo, &rules, i) != 0)
		{
			cleanup_mutexes(&rules), free_philo(&philo);
			ft_error(EXIT_FAILURE, "Failed to initialize philo.");
		}
		i++;
	}
	if (thread_alg(&philo, &rules) != 0)
	{
		cleanup_mutexes(&rules);
		free_philo(&philo);
		ft_error(EXIT_FAILURE, "Failed thread_alg");
	}
	cleanup_mutexes(&rules), free_philo(&philo);
	return (0);
}
