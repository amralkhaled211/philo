/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:52:23 by amalkhal          #+#    #+#             */
/*   Updated: 2023/12/26 19:03:59 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return(pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	make_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int		i;

	if (pthread_create(&observer, NULL, &tracking, program->philos) != 0)
		destroy_all("ERROR making thread", program, forks);
	i = 0;
	while
}