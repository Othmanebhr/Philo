/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:41:07 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:52:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int parse_arg(char **av, t_rule *rules)
{
    rules->nb_of_philo = lil_atoi(av[1]);
    if (rules->nb_of_philo <= 0) return (-1);
    rules->tt_die = lil_atoi(av[2]);
    if (rules->tt_die <= 0) return (-1);
    rules->tt_eat = lil_atoi(av[3]);
    if (rules->tt_eat <= 0) return (-1);
    rules->tt_sleep = lil_atoi(av[4]);
    if (rules->tt_sleep <= 0) return (-1);

    if (av[5] != NULL) 
    {
        rules->nb_of_time_eating = lil_atoi(av[5]);
        if (rules->nb_of_time_eating < 0)
            return (-1);
    }
    else
        rules->nb_of_time_eating = -1; // Infini si non défini

    return (0);
}
