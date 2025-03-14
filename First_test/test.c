static void	*philo_routine(void *arg)
{
	t_philo	*philo;  // Déclaration de la variable philo
	t_philo	*first_philo;  // Déclaration de la variable first_philo

	philo = (t_philo *)arg;  // Initialisation de philo avec l'argument passé à la fonction
	first_philo = philo;     // Assigner first_philo comme étant le premier philosophe de la boucle
	// Boucle principale du philosophe
	while (!simulation_should_end(philo, first_philo, 1))
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}


static int	simulation_should_end(t_philo *philo, t_philo *first_philo, int *has_checked_all)
{
	// Si le philosophe n'a pas mangé le nombre minimal de repas requis
	if (philo->meals_count < philo->rules->nb_of_time_eating)
		*has_checked_all = 0;
	// Si ce n'est pas le dernier philosophe, continuer la vérification
	if (philo->next != first_philo)
		return (simulation_should_end(philo->next, first_philo, *has_checked_all));
	else
	{
		// Si on a fait un tour complet et que tous ont mangé assez, continuer la simulation
		if (*has_checked_all)
			return (0);
		else 
			return (1);
	}
}