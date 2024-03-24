
#include "philo.h"

int		ft_atoi(const char *str)
{
    int		i;
    int		sign;
    long	nbr;

    i = 0;
    sign = 1;
    nbr = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return ((int)(nbr * sign));
}

int		ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int		ft_strlen(const char *str)
{
    int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

size_t get_time(void)
{
   struct timeval	time;

    if (gettimeofday(&time, NULL) == -1)
    {
        write(2, "ERROR gettimeofday_fun", 16);
        return ((size_t)-1);
    }
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int printing_philo(t_philo *philo, char *str)
{
    size_t time;
    if (philo->data->philo_died == 0)
    {
        time = get_time();
        if (time == -1)
            return (1);
	    printf("%zu %d %s\n", time - philo->start, philo->id, str);
    }
    return (0);
}
/// what is the difference between printing_philo and printing_mutex?

int	printing_mutex(t_philo *philo, char *str)
{
    size_t time;
	pthread_mutex_lock(&philo->data->print_lock);
    if (philo->data->philo_died == 0)
    {
        time = get_time();
        if (time == -1)
            return (1);
	    printf("%zu %d %s\n", time - philo->start, philo->id, str);
    }
	pthread_mutex_unlock(&philo->data->print_lock);
    return (0);
}