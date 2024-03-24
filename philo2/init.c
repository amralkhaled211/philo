#include "philo.h"

int init_data(t_data *data, int ac, char **av)
{
    data->philo_count = ft_atoi(av[1]);
    data->die_time = ft_atoi(av[2]);
    data->eat_time = ft_atoi(av[3]);
    data->sleep_time = ft_atoi(av[4]);
    if (ac == 6)
        data->should_eat = ft_atoi(av[5]);
    else
        data->should_eat = -1;
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
    if (!data->forks)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return (1);
    }
    data->philo_died = 0;
    data->philo_full = 0;
    pthread_mutex_init(&data->print_lock, NULL);
   pthread_mutex_init(&data->death_lock, NULL);
    pthread_mutex_init(&data->eat_lock, NULL);
    return (0);
}

int init_philo(t_philo *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        philo[i].id = i + 1;
        philo[i].data = data;
        philo[i].eat_count = 0;
        philo[i].last_eat = get_time();
        if (philo[i].last_eat == -1)
            return (1);
        philo[i].start = get_time();
        if (philo[i].start == -1)
            return (1);
        philo[i].left_fork = i;
        if (i == data->philo_count - 1)
            philo[i].right_fork = 0;
        else
            philo[i].right_fork = i + 1;
        //philo[i].right_fork = (i + 1) % data->philo_count;
        i++;
    }
    return (0);
}