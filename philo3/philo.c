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
	int		i;
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

void	eat_checker(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (data->should_eat != -1 && i < data->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		pthread_mutex_lock(&philo[i].data->death_lock);
		if (philo[i].eat_count > data->should_eat)
			data->philo_full++;
		if (data->philo_full == data->philo_count)
		{
			data->philo_died = 1;
			pthread_mutex_unlock(&philo[i].data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		pthread_mutex_unlock(&philo[i].data->death_lock);
		i++;
	}
}

void	checker(t_philo *philo, t_data *data)
{
	int		i;
	size_t	time;

	while (1)
	{
		death_checker(philo, data);
		//pthread_mutex_lock(&data->death_lock);
		if (data->philo_died == 1)
			return ;
		//pthread_mutex_unlock(&data->death_lock);
		eat_checker(philo, data);
		//pthread_mutex_lock(&data->death_lock);
		if (data->philo_died == 1)
			return ;
		//pthread_mutex_unlock(&data->death_lock);
	}
}

int	handel_one_philo(t_philo *philo, t_data *data)
{
	if (data->philo_count == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(data->die_time * 1000, philo);
		printf("%u 1 died\n", data->die_time);
		destroy_mutex(data, philo);
		return (1);
	}
	return (0);
}

int start_routine(t_philo *philo, t_data *data)
{
	int		i;
	void	*retval;

	i = 0;
	if (handel_one_philo(philo, data))
		return (0);
	while (i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]))
		{
			ft_putstr_fd("Error: Thread creation failed\n", 2);
			break ;
		}
		pthread_mutex_lock(&philo[i].meal_lock);
		philo[i].thread_flag = 1;
		philo[i].last_eat = get_time();
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	checker(philo, data);
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
	destroy_mutex(data, philo);
	return (0);
}
