/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:17:02 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/24 17:17:02 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_data *data, int ac, char **av)
{
	data->philo_count = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->philo_died = 0;
	data->philo_full = 0;
	if (ac == 6)
		data->should_eat = ft_atoi(av[5]);
	else
		data->should_eat = -1;
}

void	destroy_init_mutex(t_data *data, int i)
{	
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	free(data->forks);
}

int	init_data(t_data *data, int ac, char **av)
{
	size_t	i;

	init_input(data, ac, av);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (destroy_init_mutex(data, i - 1), 1);
		i++;
	}
	if (pthread_mutex_init(&data->death_lock, NULL))
	{
		destroy_init_mutex(data, i - 1);
		return (1);
	}
	return (0);
}

void	destroy_init_mutex_philo(t_philo *philo, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		i--;
	}
}

int	init_philo(t_philo *philo, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].thread_flag = 0;
		philo[i].data = data;
		philo[i].eat_count = 0;
		philo[i].last_eat = get_time();
		philo[i].start = get_time();
		philo[i].left_fork = i;
		if (i == data->philo_count - 1)
			philo[i].right_fork = 0;
		else
			philo[i].right_fork = i + 1;
		if (pthread_mutex_init(&philo[i].meal_lock, NULL))
		{
			destroy_init_mutex_philo(philo, i);
			return (1);
		}
		i++;
	}
	return (0);
}
