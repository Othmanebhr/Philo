/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 02:27:00 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:30:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_nb_of_arg_ok(int ac)
{
	if (ac != 5 && ac != 6)
		return (printf("%s", ERR_INV_ARG), -1);
	return (0);
}

int	init_args(char **av, t_rules *rules)
{
	rules->nb_philo = lil_atoi(av[1]);
	if (rules->nb_philo < 1)
		return (printf("%s", ERR_INV_ARG), -1);
	rules->tt_die = lil_atoi(av[2]);
	if (rules->tt_die < 0)
		return (printf("%s", ERR_INV_ARG), -1);
	rules->tt_eat = lil_atoi(av[3]);
	if (rules->tt_eat < 0)
		return (printf("%s", ERR_INV_ARG), -1);
	rules->tt_sleep = lil_atoi(av[4]);
	if (rules->tt_sleep < 0)
		return (printf("%s", ERR_INV_ARG), -1);
	if (av[5])
	{
		rules->nb_eat = lil_atoi(av[5]);
		if (rules->nb_eat < 0)
			return (printf("%s", ERR_INV_ARG), -1);
	}
	else
		rules->nb_eat = -1;
	return (0);
}
