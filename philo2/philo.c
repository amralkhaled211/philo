/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:44:48 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/22 11:44:48 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    destroy_mutex(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->death_lock);
    pthread_mutex_destroy(&data->eat_lock);
    free(data->forks);
    free(data);
    free(philo);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(size_t milliscond, t_philo *philo)
{
    long long i, current_time;

    i = get_time();
    if (i == -1)
        destroy_mutex(philo->data, philo);
    while (!philo->data->philo_died)
    {
        current_time = get_time();
        if (current_time == -1)
        {
            destroy_mutex(philo->data, philo);
            break;
        }
        if (time_diff(i, current_time) >= milliscond)
            break ;
        usleep(50);
    }
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (printing_philo(philo, "has taken a fork") == 1)
        return (1);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (printing_philo(philo, "has taken a fork") == 1)
        return (1);
	//pthread_mutex_lock(&philo->data->eat_lock);
	if (printing_philo(philo, "is eating") == 1)
        return (1);
	philo->last_eat = get_time();
    if (philo->last_eat == -1)
        return (1);
	//pthread_mutex_unlock(&philo->data->eat_lock);
	ft_usleep(philo->data->eat_time, philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
    return (0);
}

void    *philo_routine(void *pointer)
{
    int		i;
    t_philo	*philo;

    i = 0;
    philo = (t_philo *)pointer;
    if (philo->id % 2 == 0)
        usleep(15000);
    while (1)
    {
        if (philo->data->philo_died == 1)
            return (NULL);
        if (philo_eat(philo) == 1)
            destroy_mutex(philo->data, philo);
        if (philo->data->philo_died == 1)
            return (NULL);
        if (printing_mutex(philo, "is sleeping") == 1)
            destroy_mutex(philo->data, philo);
        ft_usleep(philo->data->sleep_time, philo);
        if (philo->data->philo_died == 1)
            return (NULL);
        if (printing_mutex(philo, "is thinking") == 1)
            destroy_mutex(philo->data, philo);
        i++;
    }
    return (NULL);
}

void check_death(t_philo *philo, t_data *data)
{
    int i;
    size_t time;

    while(1)
    {
        i = -1;
        while (++i < data->philo_count)
        {
            time = get_time();
            if (time == -1)
                destroy_mutex(data, philo);
            pthread_mutex_lock(&philo[i].data->death_lock);
            if (time - philo[i].last_eat >= data->die_time)
            {
                printing_philo(&philo[i], "has died");
                philo[i].data->philo_died = 1;
            }
           // usleep(100);
            if (philo[i].data->philo_died == 1)
            {
                pthread_mutex_unlock(&philo[i].data->death_lock);
                return;
            }
            pthread_mutex_unlock(&philo[i].data->death_lock);
        }
    }
}
void start_routine(t_philo *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]))
        {
            ft_putstr_fd("Error: Thread creation failed\n", 2);
            destroy_mutex(data, philo);
        }
		philo[i].last_eat = get_time();
        if (philo[i].last_eat == -1)
            destroy_mutex(data, philo);
        i++;
    }
	check_death(philo, data);
    i = 0;
    while (i < data->philo_count)
    {
        if (pthread_join(philo[i].thread, NULL))
        {
            ft_putstr_fd("Error: Thread join failed\n", 2);
            destroy_mutex(data , philo);
        }
        i++;
    }
    destroy_mutex(data, philo);
}
