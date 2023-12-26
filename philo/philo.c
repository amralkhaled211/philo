/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 21:05:05 by amalkhal          #+#    #+#             */
/*   Updated: 2023/12/26 19:07:12 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_av(char *av)
{
	if (!(*av == '+'
			|| (*av >= '0' && *av <= '9')))
		return (1);
	if ((*av == '+')
		&& !(av[1] >= '0' && av[1] <= '9'))
		return (1);
	while (*++av)
	{
		if (!(*av >= '0' && *av <= '9'))
			return (1);
	}
	return (0);
}


static int	check_ac(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| check_av(av[1]) == 1)
		return (write(2, "Invalid philosophers num\n", 25), 1);
	if (ft_atoi(av[2]) <= 0 || check_av(av[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || check_av(av[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || check_av(av[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_arg_content(av[5]) == 1))
		return (write(2, "Invalid meals to eat\n",21), 1);
	return (0);
}


int	main(int ac, char **av)
{
	t_program	program;
	t_philo		philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return(write(2, "Error", 5), 1);
	if (check_ac(av) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &program, forks, av);
	make_thread(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}