/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:19:23 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/24 17:19:23 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	size_t				philo_count;
	size_t				die_time;
	size_t				eat_time;
	int				sleep_time;
	int				should_eat;
	size_t				philo_full;
	int				philo_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	size_t			last_eat;
	long			start;
	int				left_fork;
	int				right_fork;
	int				thread_flag;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);
size_t	time_diff(long long past, long long pres);
void		ft_usleep(size_t milliscond, t_philo *philo);
void		destroy_mutex(t_data *data, t_philo *philo);
void		*handel_one_philo(void *pointer);
void		multi_thread(t_philo *philo, t_data *data);
int			init_data(t_data *data, int ac, char **av);
int			init_philo(t_philo *philo, t_data *data);
size_t		get_time(void);
void		destroy_mutex(t_data *data, t_philo *philo);
int			start_routine(t_philo *philo, t_data *data);
int			printing_mutex(t_philo *philo, char *str);
int			printing_death(t_philo *philo, char *str);
void		*philo_routine(void *pointer);

#endif