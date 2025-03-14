/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:35 by root              #+#    #+#             */
/*   Updated: 2024/12/01 16:03:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	simulation_should_end(t_philo *first_philo)
{
	t_philo	*current_philo;
	int		has_checked_all;

	current_philo = first_philo;
	has_checked_all = 1;
	while (1)
	{
		if (current_philo->meals_count < current_philo->rules->nb_of_time_eating)
			has_checked_all = 0;
		if (current_time_in_ms() - current_philo->last_meal_time > current_philo->rules->tt_die)
		{
			printf("Philosopher %d has died", current_philo->index);
			return (1);
		}
		if (current_philo->next == first_philo)
			break;
		current_philo = current_philo->next;
	}
	// Si tous les philosophes ont mangé assez, retourne 0, sinon retourne 1
	if (has_checked_all == 1)
		return (0);
	return (1);
}

static void *philo_routine(void *arg)
{
	t_philo *philo;         // Pointeur vers le philosophe actuel
	t_philo *first_philo;   // Pointeur vers le premier philosophe de la liste

	philo = (t_philo *)arg; // Récupère l'argument passé
	first_philo = philo;    // Initialise le pointeur vers le premier philosophe

	// Boucle principale du philosophe
	while (simulation_should_end(first_philo) == 0) // Continue tant que la simulation n'est pas terminée
	{
		think(philo);          // Le philosophe réfléchit
		pick_up_forks(philo);  // Le philosophe prend les fourchettes
		eat(philo);            // Le philosophe mange
		put_down_forks(philo); // Le philosophe repose les fourchettes
		sleep_philo(philo);    // Le philosophe dort
		printf("test");
	}
	return (NULL);
}

static int	thread_alg(t_philo *philo, t_rule rules)
{
	pthread_t	*threads;
	t_philo		*current_philo;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * rules.nb_of_philo);
	if (!threads)
		return (-1);
	current_philo = philo;
	while (current_philo != philo || i == 0)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, (void *)current_philo) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_cancel(threads[i]);
				pthread_join(threads[i], NULL); //a voir pourquoi on doit join avant de quitter
			}
			free(threads);
			return (-1);
		}
		current_philo = current_philo->next;
		i++;
		if (i >= rules.nb_of_philo)
			break;  // Pour éviter de boucler indéfiniment si nb_of_philo est atteint
	}
	i = 0;
	while (i < rules.nb_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_rule	rules;
	int		i;

	philo = NULL;
	if (ac != 5 && ac != 6)
		return (printf("Number of arguments non valid!\n"));
	if (parse_arg(av, &rules) != 0)
		return (printf("Parse is fucked\n"));
	i = 0;
	while (i < rules.nb_of_philo)
	{
		if(fill_philo(&philo, &rules, i) != 0)
		{
			free_philo(&philo);
			return (printf("fill_philo is fucked\n"));
		}
		i++;
	}
	if (thread_alg(philo, rules) != 0)
	{
		free_philo(&philo);
		return(printf("thread_alg is fucked\n"));
	}
	// free_philo(&philo);
	return (0);
}
