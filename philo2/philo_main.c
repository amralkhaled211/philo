
#include "philo.h"

int handle_non_numeric_input(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            ft_putstr_fd("Error: Non-numeric input\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int handel_input(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (1);
    }
    if (handle_non_numeric_input(av[1]) || handle_non_numeric_input(av[2])
        || handle_non_numeric_input(av[3]) || handle_non_numeric_input(av[4]))
        return (1);
    return (0);
}

int init_all(int ac, char **av, t_data **data, t_philo **philo)
{
    *data = (t_data *)malloc(sizeof(t_data));
    if (!*data)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        return (1);
    }
    if (init_data(*data, ac, av))
    {
        free(*data);
        return (1);
    }
    *philo = (t_philo *)malloc(sizeof(t_philo) * (*data)->philo_count);
    if (!*philo)
    {
        ft_putstr_fd("Error: Memory allocation failed\n", 2);
        free(*data);
        return (1);
    }
    if (init_philo(*philo, *data))
    {
        free(*data);
        free(*philo);
        return (1);
    }
    return (0);
}
    
int main(int ac, char **av)
{
    t_philo *philo;
    t_data *data;

    if (handel_input(ac, av))
        return (1);
    if (init_all(ac, av, &data, &philo))
        return (1);
    start_routine(philo, data);
    return (0);
}
