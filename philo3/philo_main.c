/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:16:52 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/24 17:16:52 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_non_numeric_input(char *str)
{
	int	i;

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

int	handel_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	if (handle_non_numeric_input(av[1]) || handle_non_numeric_input(av[2])
		|| handle_non_numeric_input(av[3]) || handle_non_numeric_input(av[4]))
		return (1);
	if (ac == 6 && handle_non_numeric_input(av[5]))
		return (1);
	return (0);
}

static void	free_destroy_mutex_stages(t_philo **philo, t_data *data, int i)
{
	int	j;

	if (i == 1)
	{
		j = 0;
		while (j < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[j]);
			j++;
		}
		pthread_mutex_destroy(&data->death_lock);
		free(data->forks);
	}
	else if (i == 2)
	{
		j = 0;
		while (j < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[j]);
			j++;
		}
		pthread_mutex_destroy(&data->death_lock);
		free(data->forks);
		free(*philo);
	}
}

int	init_all(int ac, char **av, t_data *data, t_philo **philo)
{
	if (init_data(data, ac, av))
		return (1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * (data)->philo_count);
	if (!*philo)
	{
		free_destroy_mutex_stages(philo, data, 1);
		return (1);
	}
	if (init_philo(*philo, data))
	{
		free_destroy_mutex_stages(philo, data, 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;

	if (handel_input(ac, av))
		return (1);
	if (init_all(ac, av, &data, &philo))
		return (1);
	if (start_routine(philo, philo->data))
		return (1);
	return (0);
}
