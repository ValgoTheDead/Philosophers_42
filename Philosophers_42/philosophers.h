/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:08:01 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/24 17:56:49 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

// Macros
# define F 1
# define S 0
# define DN 0
# define LOCK 1
# define THROW 1
# define UNLOCK 0
# define LOW_INDEX 0
# define MAX_INDEX 1
# define ANOMALY 111
# define SLEEP_EVEN 40
# define CONVERTER 1000
# define MALLOC "Malloc failed\n"
# define NO_TIME "get time failed\n"
# define INVALID "Invalid arguments\n"
# define MUTEX_LOCK "Failed to lock\n"
# define MUTEX_INIT "Mutex init failed\n"
# define MUTEX_UNLOCK "Failed to unlock\n"
# define MUTEX_JOIN "Failed to join thread\n"
# define MUTEX_CREATE "Failed to create thread\n"

// Philosophers States
# define DEAD "died\n"
# define EAT "is eating\n"
# define THINK "is thinking\n"
# define SLEEP "is sleeping\n"
# define FORK "has taken a fork\n"

// Philsoophers Struct
typedef struct s_philo
{
	long		nphilo;
	long		n_meals;
	long		max_ate;
	long		eat_time;
	int			philo_id;
	long		dead_time;
	long		sleep_time;
	pthread_t	th_philo;
	long		last_time_ate;
	t_data		*data;
}	t_philo;

// Shared Data
typedef struct s_data
{
	int				len;
	t_mtx			*forks;
	int				forks_index;
	t_mtx			to_print;
	int				print_flag;
	t_mtx			lock_done;
	int				done_flag;
	t_mtx			last_eat;
	int				last_eat_flag;
	t_mtx			meals_ate;
	int				meals_flag;
	bool			done;
	long			start_time;
	pthread_t		monitor;
	t_philo			*philo;
}	t_data;

// Parsing Input Data
void	error(char *err);
long	ft_atol(char *str);
int		ft_strlen(char *str);
int		validation(char **argv);
char	**ft_split(char *s, char c);
int		pre_parsing(char **data, int len);
char	*twoconverter(char **args, int len);

// Initialization && Tools
long	get_time(void);
void	*watching(void *arg);
int		handlers(t_data *data);
void	*sit_around(void *arg);
void	free_all(t_data *data);
int		throw_forks(t_philo *philo);
void	ft_free(char **str, int len);
long	sleeper(long mili, t_philo *philo);
int		mutex_lockers(void *lock, int mode);
int		fill_init(char **param, t_data *data, int len);
int		safe_print(t_philo *philo, char *print, int mode);

// Set and Get
int		set_bool(t_philo *philo);
int		check_bool(t_philo *philo);
int		set_last_eat(t_philo *philo);
long	get_last_eat(t_philo *philo);
int		get_meals_ate(t_philo *philo);
int		set_meals_out(t_philo *philo);
int		set_meals_ate(t_philo *philo);

#endif