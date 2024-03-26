/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:48:00 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/26 17:30:43 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death_lock);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
	free(data->forks);
	free(philo);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(size_t milliscond, t_philo *philo)
{
	long long	i;
	long long	current_time;

	i = get_time();
	while (1)
	{
		
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->philo_died == 1)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		current_time = get_time();
		if (time_diff(i, current_time) >= milliscond)
			break ;
		usleep(50);
	}
}

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	printing_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	printing_mutex(philo, "has taken a fork");
	printing_mutex(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->eat_time, philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&philo->data->death_lock);
	while (philo->data->philo_died == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		philo_eat(philo);
		printing_mutex(philo, "is sleeping");
		ft_usleep(philo->data->sleep_time, philo);
		// ft_usleep(philo->data->sleep_time);
		printing_mutex(philo, "is thinking");
		pthread_mutex_lock(&philo->data->death_lock);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (NULL);
}