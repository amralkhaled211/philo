
#include "philo.h"

void	*philo_monitor(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        if (get_time() - ph->last_meal > ph->data->time_to_die)
        {
            printf("%ld %d died\n", get_time() - ph->data->start, ph->id);
            exit(1);
        }
    }
    return (NULL);
}

void	*philo_life(void *philo)
{
    t_philo		*ph;
    pthread_t	monitor;

    ph = (t_philo *)philo;
    pthread_create(&monitor, NULL, &philo_monitor, ph);
    while (1)
    {
        pthread_mutex_lock(&ph->data->forks[ph->left_fork]);
        printf("%ld %d has taken a fork\n", get_time() - ph->data->start, ph->id);
        pthread_mutex_lock(&ph->data->forks[ph->right_fork]);
        printf("%ld %d has taken a fork\n", get_time() - ph->data->start, ph->id);
        ph->last_meal = get_time();
        printf("%ld %d is eating\n", get_time() - ph->data->start, ph->id);
        ft_usleep(ph->data->time_to_eat);
        pthread_mutex_unlock(&ph->data->forks[ph->left_fork]);
        pthread_mutex_unlock(&ph->data->forks[ph->right_fork]);
        printf("%ld %d is sleeping\n", get_time() - ph->data->start, ph->id);
        ft_usleep(ph->data->time_to_sleep);
        printf("%ld %d is thinking\n", get_time() - ph->data->start, ph->id);
    }
    return (NULL);
}


philo_death(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        if (get_time() - ph->last_meal > ph->data->time_to_die)
        {
            printf("%ld %d died\n", get_time() - ph->data->start, ph->id);
            exit(1);
        }
    }
    return (NULL);
}

void	*philo_done(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        if (ph->data->philo_done == ph->data->philo_count)
        {
            printf("%ld all philo ate %d times\n", get_time() - ph->data->start, ph->data->must_eat);
            exit(0);
        }
    }
    return (NULL);
}

void	*philo_eat(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(&ph->data->eat);
        if (ph->eat_count == ph->data->must_eat)
        {
            ph->data->philo_done++;
            pthread_mutex_unlock(&ph->data->eat);
            return (NULL);
        }
        pthread_mutex_unlock(&ph->data->eat);
    }
    return (NULL);
}

void	*philo_sleep(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        ft_usleep(ph->data->time_to_sleep);
    }
    return (NULL);
}

void	*philo_think(void *philo)
{
    t_philo	*ph;

    ph = (t_philo *)philo;
    while (1)
    {
        printf("%ld %d is thinking\n", get_time() - ph->data->start, ph->id);
    }
    return (NULL);
}

void	*philo_print(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, str);
    pthread_mutex_unlock(&philo->data->print);
    return (NULL);
}

int	init_data(t_data *data, int argc, char **argv)
{
    data->philo_count = ft_atoi(argv[1]);
    data->die_time = ft_atoi(argv[2]);
    data->eat_time = ft_atoi(argv[3]);
    data->sleep_time = ft_atoi(argv[4]);
    data->must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
    data->philo_done = 0;
    data->philo_dead = 0;
    data->start = get_time();
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
    if (!data->forks)
        return (ft_error("Error: malloc failed\n"));
    return (0);
}

int	free_data(t_data *data)
{
    free(data->philo);
    free(data->forks);
    return (0);
}

int	free_mutex(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->eat);
    return (0);
}

int main(int argc, char **argv)
{
    t_data	data;

    if (argc < 5 || argc > 6)
        return (ft_error("Error: wrong number of arguments\n"));
    if (check_args(argc, argv))
        return (1);
    if (init_data(&data, argc, argv))
        return (1);
    if (init_philo(&data))
        return (1);
    if (init_mutex(&data))
        return (1);
    if (init_thread(&data))
        return (1);
    if (free_data(&data))
        return (1);
    if (free_mutex(&data))
        return (1);
    return (0);
}

