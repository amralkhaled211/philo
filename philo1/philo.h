#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
    pthread_t		thread;
    int				id;
    int				left_fork;
    int				right_fork;
    int				eat_count;
    long			last_eat;
    pthread_mutex_t	*forks;
    pthread_mutex_t	*print;
    pthread_mutex_t	*eat;
}				t_philo;

typedef struct s_data
{
    int				philo_count;
    int				die_time;
    int				eat_time;
    int				sleep_time;
    int				must_eat;
    int				philo_done;
    int				philo_dead;
    long			start_time;
    pthread_mutex_t	*forks;
    pthread_mutex_t	print;
    pthread_mutex_t	eat;
    t_philo			*philo;
}				t_data;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_usleep(long time);
long	get_time(void);
void	*philo_life(void *philo);
void	*philo_death(void *philo);
void	*philo_done(void *philo);
void	*philo_eat(void *philo);
void	*philo_sleep(void *philo);
void	*philo_think(void *philo);
void	*philo_print(t_philo *philo, char *str);
int		init_data(t_data *data, int argc, char **argv);
int		init_philo(t_data *data);
int		init_mutex(t_data *data);
int		init_thread(t_data *data);
int		free_data(t_data *data);
int		free_philo(t_data *data);
int		free_mutex(t_data *data);
int		free_thread(t_data *data);
int		check_args(int argc, char **argv);
int		check_data(t_data *data);
int		check_philo(t_data *data);
int		check_mutex(t_data *data);
int		check_thread(t_data *data);
int		check_death(t_data *data);
int		check_done(t_data *data);
int		check_eat(t_data *data);
int		check_sleep(t_data *data);
int		check_think(t_data *data);
int		check_print(t_data *data);
int		check_forks(t_data *data);
int		ft_error(char *str);



#endif