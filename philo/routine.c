/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:48:00 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/30 18:01:56 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data, t_philo *philo)
{
	size_t	i;

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

int philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
    if (philo->eat_count >= philo->data->should_eat && philo->data->should_eat != 0)
	{
        pthread_mutex_unlock(&philo->meal_lock);
        return (0);
    }
	pthread_mutex_unlock(&philo->meal_lock);
    int left_fork = philo->left_fork;
    int right_fork = philo->right_fork;
    // Ensure that the forks are always picked up in the same order
    if (left_fork > right_fork) {
        int temp = left_fork;
        left_fork = right_fork;
        right_fork = temp;
    }
    pthread_mutex_lock(&philo->data->forks[left_fork]);
    printing_mutex(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[right_fork]);
    printing_mutex(philo, "has taken a fork");
    printing_mutex(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
    philo->last_eat = get_time();
    philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_lock);
    ft_usleep(philo->data->eat_time, philo);
	// pthread_mutex_lock(&philo->meal_lock);
	// pthread_mutex_unlock(&philo->meal_lock);
    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
    return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(15000);
	pthread_mutex_lock(&philo->data->death_lock);
	while (philo->data->philo_died == 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		philo_eat(philo);
		printing_mutex(philo, "is sleeping");
		ft_usleep(philo->data->sleep_time, philo);
		printing_mutex(philo, "is thinking");
		pthread_mutex_lock(&philo->data->death_lock);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (NULL);
}


void	*handel_one_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	printf("%d %zu has taken a fork\n", 0, philo->id);
	ft_usleep(philo->data->die_time, philo);
	printf("%zu %zu died\n", philo->data->die_time, philo->id);
	return (NULL);
}

void	multi_thread(t_philo *philo, t_data *data)
{
	size_t i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]))
		{
			ft_putstr_fd("Error: Thread creation failed\n", 2);
			return ;
		}
		pthread_mutex_lock(&philo[i].meal_lock);
		philo[i].thread_flag = 1;
		philo[i].last_eat = get_time();
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
}
