
#include "philo.h"

int		ft_atoi(const char *str)
{
    int		i;
    int		sign;
    long	nb;

    i = 0;
    sign = 1;
    nb = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = (nb * 10) + (str[i] - '0');
        i++;
    }
    return (nb * sign);
}
int		ft_strlen(const char *s)
{
    int	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void	ft_putnbr_fd(int n, int fd);
{
    if (n == -2147483648)
    {
        ft_putstr_fd("-2147483648", fd);
        return ;
    }
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n > 9)
    {
        ft_putnbr_fd(n / 10, fd);
        ft_putnbr_fd(n % 10, fd);
    }
    else
        ft_putchar_fd(n + '0', fd);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n);
{
    size_t	i;

    i = 0;
    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i == n)
        return (0);
    return (s1[i] - s2[i]);
}
void	ft_putstr_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

int		ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

long	get_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
    long	start;

    start = get_time();
    while (get_time() < start + time)
        usleep(100);
}

int		ft_error(char *str)
{
    ft_putstr_fd(str, 2);
    return (1);
}

int		free_philo(t_data *data)
{
    free(data->philo);
    return (0);
}
int		free_thread(t_data *data)
{
    int	i;

    i = -1;
    while (++i < data->philo_count)
    {
        pthread_join(data->philo[i].thread, NULL);
    }
    return (0);
}
