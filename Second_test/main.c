/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:52:35 by root              #+#    #+#             */
/*   Updated: 2025/02/15 22:49:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int check_death(t_philo *philo);
static void monitor_philos(t_philo *philos, t_rule *rules);

static void monitor_philos(t_philo *philos, t_rule *rules)
{
    t_philo *current;
    int i;
    int all_ate_enough;

    while (1)
    {
        if (*philos->someone_died)
            return;
        i = 0;
        all_ate_enough = 1;
        current = philos;
        while (i < rules->nb_of_philo)
        {
            if (check_death(current))
                return;
            if (rules->nb_of_time_eating > 0 &&
                current->meals_count < rules->nb_of_time_eating)
                all_ate_enough = 0;
            current = current->next;
            i++;
        }
        if (*philos->someone_died)
            break;
        if ((rules->nb_of_time_eating > 0 && all_ate_enough))
            break;
        usleep(1000);
    }
}

static int check_death(t_philo *philo)
{
    long long current_time;
    int is_dead;

    pthread_mutex_lock(&philo->self_mutex);
    current_time = current_time_in_ms();
    is_dead = (current_time - philo->last_meal_time > philo->rules->tt_die);
    pthread_mutex_unlock(&philo->self_mutex);

    if (is_dead) {
        pthread_mutex_lock(philo->death_mutex);
        if (!*philo->someone_died) {
            *philo->someone_died = 1;
            printf("%lld %d died\n",
                   current_time - philo->rules->start_time, philo->index);
        }
        pthread_mutex_unlock(philo->death_mutex);
        return (1);
    }
    return (0);
}

static void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->self_mutex);
    philo->last_meal_time = current_time_in_ms();
    pthread_mutex_unlock(&philo->self_mutex);

    // Gestion spéciale pour un seul philosophe
    if (philo->rules->nb_of_philo == 1)
    {
        print_status(philo, "has taken a fork");
        usleep(philo->rules->tt_die * 1000);
        return (NULL);
    }

    // Décalage pour éviter les deadlocks
    if (philo->index % 2 == 0)
        usleep(1000);

    while (!check_death(philo))
    {
        if (philo->rules->nb_of_time_eating > 0 && 
            philo->meals_count >= philo->rules->nb_of_time_eating)
            break;
            
        think(philo);
        pick_up_forks(philo);
        eat(philo);
        put_down_forks(philo);
        sleep_philo(philo);
    }
    return (NULL);
}

static int thread_alg(t_philo *philo, t_rule *rules)
{
    pthread_t *threads;
    t_philo *current_philo;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * rules->nb_of_philo);
    if (!threads)
        return (-1);

    // Initialiser le temps de début pour tous les philosophes
    rules->start_time = current_time_in_ms();
    current_philo = philo;
    do {
        current_philo->last_meal_time = rules->start_time;
        current_philo = current_philo->next;
    } while (current_philo != philo);

    // Créer les threads
    current_philo = philo;
    while (i < rules->nb_of_philo)
    {
        if (pthread_create(&threads[i], NULL, philo_routine, current_philo) != 0)
        {
            while (--i >= 0)
            {
                pthread_cancel(threads[i]);
                pthread_join(threads[i], NULL);
            }
            free(threads);
            return (-1);
        }
        current_philo = current_philo->next;
        i++;
    }

    // Lancer le monitoring
    monitor_philos(philo, rules);

    // Attendre la fin des threads
    i = 0;
    while (i < rules->nb_of_philo)
        pthread_join(threads[i++], NULL);
    free(threads);
    return (0);
}

int main(int ac, char **av)
{
    t_philo	*philo;
    t_rule	rules;
    int		i;

    philo = NULL;
    if (ac != 5 && ac != 6) //A voir si il ne faut pas mettre un ||
        return (printf("Error: invalid number of arguments\n"));
    if (parse_arg(av, &rules) != 0)
        return (printf("Error: invalid arguments\n"));
    i = 0;
    while (i < rules.nb_of_philo)
    {
        if(fill_philo(&philo, &rules, i + 1) != 0) // + 1 pour faire commencer les philosophe a 1
        {
            free_philo(&philo);
            return (printf("Error: failed to initialize philosophers\n"));
        }
        i++;
    }
    if (thread_alg(philo, &rules) != 0)
    {
        free_philo(&philo);
        return (printf("Error: failed to create threads\n"));
    }
    free_philo(&philo);
    return (0);
}