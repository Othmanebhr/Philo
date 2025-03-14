/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 04:45:50 by root              #+#    #+#             */
/*   Updated: 2025/03/03 18:31:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_act(t_rules *rules, char *str, int id, bool death_check)
{
	pthread_mutex_lock(&rules->writing);
	if (has_sim_stop(rules) == false || death_check == true)
		printf("%ld %d %s\n",
			get_time() - rules->start_time, id + 1, str);
	pthread_mutex_unlock(&rules->writing);
}

void	smart_sleep(time_t time, t_rules *rules)
{
	time_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
	{
		if (has_sim_stop(rules))
			break ;
		usleep(100);
	}
}

void	smart_thinking(t_philo *philo, bool first_philo)
{
	time_t	tt_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	tt_think = (philo->rules->tt_die
			- (get_time() - philo->last_meal)
			- philo->rules->tt_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (tt_think < 0)
		tt_think = 0;
	if (tt_think == 0 && first_philo == true)
		tt_think = 1;
	if (tt_think > 600)
		tt_think = 200;
	if (first_philo == false)
		print_act(philo->rules, THINK, philo->id, false);
	smart_sleep(tt_think, philo->rules);
}
