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

void	death_checker(t_philo *philo, t_data *data)
{
	size_t	i;
	size_t	time;

	i = -1;
	while (++i < data->philo_count)
	{
		time = get_time();
		pthread_mutex_lock(&philo[i].meal_lock);
		pthread_mutex_lock(&philo[i].data->death_lock);
		if (time - philo[i].last_eat >= data->die_time)
		{
			philo[i].data->philo_died = 1;
			pthread_mutex_unlock(&philo[i].data->death_lock);
			pthread_mutex_unlock(&philo[i].meal_lock);
			printing_death(&philo[i], "died");
			return ;
		}
		pthread_mutex_unlock(&philo[i].data->death_lock);
		pthread_mutex_unlock(&philo[i].meal_lock);
	}
}

void eat_checker(t_philo *philo, t_data *data)
{
    size_t i;
    size_t done_eating;

    i = 0;
    done_eating = 0;
    if (data->should_eat == -1)
        return;
    while (i < data->philo_count)
    {
        pthread_mutex_lock(&philo[i].meal_lock);
        if (philo[i].eat_count >= data->should_eat)
            done_eating++;
        pthread_mutex_unlock(&philo[i].meal_lock);
        i++;
    }
    if (done_eating == data->philo_count)
    {
        pthread_mutex_lock(&data->death_lock);
        data->philo_died = 1;
        pthread_mutex_unlock(&data->death_lock);
    }
}

void	checker(t_philo *philo, t_data *data)
{
	while (1)
	{
		usleep(100);
		death_checker(philo, data);
		eat_checker(philo, data);
		if (data->philo_died == 1)
			return ;
	}
}

int	join_threads(t_philo *philo, t_data *data)
{
	size_t		i;

	i = 0;
	while (i < data->philo_count)
	{
		if (philo[i].thread_flag == 1)
		{
			if (pthread_join(philo[i].thread, NULL))
			{
				ft_putstr_fd("Error: Thread join failed\n", 2);
				destroy_mutex(data, philo);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	start_routine(t_philo *philo, t_data *data)
{
	if (data->philo_count == 1)
	{
		if (pthread_create(&philo[0].thread, NULL,
				&handel_one_philo, &philo[0]))
			ft_putstr_fd("Error: Thread creation failed\n", 2);
		if (pthread_join(philo[0].thread, NULL))
		{
			ft_putstr_fd("Error: Thread join failed\n", 2);
			return (destroy_mutex(data, philo), 1);
		}
		return (destroy_mutex(data, philo), 0);
	}
	multi_thread(philo, data);
	checker(philo, data);
	if (join_threads(philo, data) == 1)
		return (1);
	destroy_mutex(data, philo);
	return (0);
}
