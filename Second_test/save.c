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
	t_philo *philo;
	t_philo *first_philo;

	philo = (t_philo *)arg;
	first_philo = philo;
	while (simulation_should_end(first_philo) == 0)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		printf("test");
	}
	return (NULL);
}