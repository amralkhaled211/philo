/* void    *philo_routine(void *pointer)
{
    size_t	time;

    t_philo *philo = (t_philo *)pointer;
    while (1 && philo->is_dead != 1)
    {
        time = get_time() - philo->start;

        pthread_mutex_lock(&philo->data->death_lock);
        if (philo->data->philosopher_died)
        {
            pthread_mutex_unlock(&philo->data->death_lock);
            exit(0);
        }
        pthread_mutex_unlock(&philo->data->death_lock);

        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        printf("%zu %d has taken a left fork\n", time, philo->id);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        printf("%zu %d has taken a right fork\n", time, philo->id);
        printf("%zu %d is eating\n", time, philo->id);
        philo->last_eat = get_time();
        ft_usleep(philo->data->eat_time);
        pthread_mutex_unlock(&philo->lock);

        pthread_mutex_lock(&philo->lock);
        if (get_time() - philo->last_eat >= philo->data->die_time )
        {
            time = get_time() - philo->start;
            pthread_mutex_lock(&philo->data->print_lock);
            printf("%zu %d has died\n", time, philo->id);
            philo->is_dead = 1;
            pthread_mutex_lock(&philo->data->death_lock);
            philo->data->philosopher_died = 1;
            pthread_mutex_unlock(&philo->data->death_lock);
            pthread_mutex_unlock(&philo->data->print_lock);
            pthread_mutex_unlock(&philo->lock);
            exit(0);
        }
        pthread_mutex_unlock(&philo->lock);

        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
        printf("%ld %d is sleeping\n", time, philo->id);
        ft_usleep(philo->data->sleep_time);

        pthread_mutex_lock(&philo->lock);
        if (get_time() - philo->last_eat >= philo->data->die_time )
        {
            time = get_time() - philo->start;
            pthread_mutex_lock(&philo->data->print_lock);
            printf("%zu %d has died\n", time, philo->id);
            philo->is_dead = 1;
            pthread_mutex_unlock(&philo->data->print_lock);
            pthread_mutex_unlock(&philo->lock);
            exit(0);
        }
        pthread_mutex_unlock(&philo->lock);

        printf("%ld %d is thinking\n", time, philo->id);
        pthread_mutex_lock(&philo->lock);
        if (get_time() - philo->last_eat >= philo->data->die_time )
        {
            time = get_time() - philo->start;
            pthread_mutex_lock(&philo->data->print_lock);
            printf("%zu %d has died\n", time, philo->id);
            philo->is_dead = 1;
            pthread_mutex_unlock(&philo->data->print_lock);
            pthread_mutex_unlock(&philo->lock);
            exit (0);
        }
        pthread_mutex_unlock(&philo->lock);
    }
    return NULL;
} */