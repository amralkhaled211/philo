
#include "philo.h"

int		check_args(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (ft_error("Error: wrong number of arguments\n"));
    if (ft_atoi(argv[1]) < 1)
        return (ft_error("Error: wrong number of philosophers\n"));
    if (ft_atoi(argv[2]) < 60)
        return (ft_error("Error: wrong time to die\n"));
    if (ft_atoi(argv[3]) < 60)
        return (ft_error("Error: wrong time to eat\n"));
    if (ft_atoi(argv[4]) < 60)
        return (ft_error("Error: wrong time to sleep\n"));
    if (argc == 6 && ft_atoi(argv[5]) < 1)
        return (ft_error("Error: wrong number of times to eat\n"));
    return (0);
}
int		check_data(t_data *data)
{
    if (data->philo_count < 1)
        return (ft_error("Error: wrong number of philosophers\n"));
    if (data->die_time < 60)
        return (ft_error("Error: wrong time to die\n"));
    if (data->eat_time < 60)
        return (ft_error("Error: wrong time to eat\n"));
    if (data->sleep_time < 60)
        return (ft_error("Error: wrong time to sleep\n"));
    if (data->must_eat < 1)
        return (ft_error("Error: wrong number of times to eat\n"));
    return (0);
}

int		check_philo(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (data->philo[i].id < 1)
            return (ft_error("Error: wrong philosopher id\n"));
        if (data->philo[i].eat_count < 0)
            return (ft_error("Error: wrong philosopher eat count\n"));
        if (data->philo[i].last_eat < 0)
            return (ft_error("Error: wrong philosopher last eat\n"));
        if (data->philo[i].left_fork < 0)
            return (ft_error("Error: wrong philosopher left fork\n"));
        if (data->philo[i].right_fork < 0)
            return (ft_error("Error: wrong philosopher right fork\n"));
    }
    return (0);
}

int		check_mutex(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_mutex_trylock(&data->forks[i]))
            return (ft_error("Error: mutex lock failed\n"));
    }
    if (pthread_mutex_trylock(&data->print))
        return (ft_error("Error: mutex lock failed\n"));
    if (pthread_mutex_trylock(&data->eat))
        return (ft_error("Error: mutex lock failed\n"));
    return (0);
}

int		check_thread(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_join(data->philo[i].thread, NULL))
            return (ft_error("Error: thread join failed\n"));
    }
    return (0);
}

int		check_death(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (get_time() - data->philo[i].last_eat > data->die_time)
            return (ft_error("Error: philosopher died\n"));
    }
    return (0);
}

int		check_done(t_data *data)
{
    if (data->philo_done != data->philo_count)
        return (ft_error("Error: philosopher not done\n"));
    return (0);
}

int		check_eat(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (data->philo[i].eat_count != data->must_eat)
            return (ft_error("Error: philosopher not eat\n"));
    }
    return (0);
}

int		check_sleep(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (get_time() - data->philo[i].last_eat < data->eat_time)
            return (ft_error("Error: philosopher not sleep\n"));
    }
    return (0);
}

int		check_think(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (get_time() - data->philo[i].last_eat < data->eat_time + data->sleep_time)
            return (ft_error("Error: philosopher not think\n"));
    }
    return (0);
}

int		check_print(t_data *data)
{
    if (pthread_mutex_trylock(&data->print))
        return (ft_error("Error: mutex lock failed\n"));
    return (0);
}

int		check_forks(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_mutex_trylock(&data->forks[i]))
            return (ft_error("Error: mutex lock failed\n"));
    }
    return (0);
}