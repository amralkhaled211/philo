/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:07:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/26 13:14:47 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "ERROR gettimeofday_fun", 16);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	printing_death(t_philo *philo, char *str)
{
	size_t	time;

	if (philo->data->philo_died == 1)
	{
		time = get_time();
		printf("%zu %d %s\n", time - philo->start, philo->id, str);
	}
	return (0);
}

int	printing_mutex(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->philo_died == 0)
	{
		time = get_time();
		printf("%zu %d %s\n", time - philo->start, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (0);
}
