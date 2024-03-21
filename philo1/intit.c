#include "philo.h"

int	init_philo(t_data *data)
{
    int	i;

    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
    if (!data->philo)
        return (ft_error("Error: malloc failed\n"));
    i = -1;
    while (++i < data->philo_count)
    {
        data->philo[i].id = i + 1;
        data->philo[i].eat_count = 0;
        data->philo[i].last_eat = get_time();
        data->philo[i].left_fork = i;
        data->philo[i].right_fork = (i + 1) % data->philo_count;
        data->philo[i].data = data;
    }
    return (0);
}

int	init_mutex(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        pthread_mutex_init(&data->forks[i], NULL);
    }
    pthread_mutex_init(&data->print, NULL);
    pthread_mutex_init(&data->eat, NULL);
    return (0);
}

int	init_thread(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        pthread_create(&data->philo[i].thread, NULL, &philo_life, &data->philo[i]);
    }
    i = -1;
    while (++i < data->philo_count)
    {
        pthread_join(data->philo[i].thread, NULL);
    }
    return (0);
}