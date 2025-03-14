/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:41:11 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 19:41:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	is_nb_of_arg_ok(int ac)
{
	if (ac != 5 && ac != 6)
		ft_error(EXIT_FAILURE, "Wrong number of arguments.");
}
static int	lil_atoi(char *str)
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

static int	parse_arg2(t_rules *rules)
{
	int	i;

	i = 0;
	rules->stop = 0;
	rules->philo = NULL;
	rules->start_time = current_time_in_ms();
	if (pthread_mutex_init(&rules->meal_check, NULL))
		return(-1);
	if (pthread_mutex_init(&rules->writing, NULL) != 0)
		return (pthread_mutex_destroy(&rules->meal_check), -1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (-1);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
		{
			pthread_mutex_destroy(&rules->meal_check);
			pthread_mutex_destroy(&rules->writing);
			free(rules->forks);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parse_arg(int ac, char **av, t_rules *rules)
{
	is_nb_of_arg_ok(ac);
	rules->nb_philo = lil_atoi(av[1]);
	if (rules->nb_philo < 1)
		return (-1);
	rules->tt_die = lil_atoi(av[2]);
	if (rules->tt_die < 0)
		return (-1);
	rules->tt_eat = lil_atoi(av[3]);
	if (rules->tt_eat < 0)
		return (-1);
	rules->tt_sleep = lil_atoi(av[4]);
	if (rules->tt_sleep < 0)
		return (-1);
	if (av[5])
	{
		rules->nb_eat = lil_atoi(av[5]);
		if (rules->nb_eat < 0)
			return(-1);
	}
	else
		rules->nb_eat = 0;
	if (parse_arg2(rules) != 0)
		return (-1);
	return (0);
}
