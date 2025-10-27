/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:43:51 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/22 17:04:14 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_free(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		error(NO_TIME);
		return (ANOMALY);
	}
	return (tv.tv_sec * CONVERTER
		+ tv.tv_usec / CONVERTER);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->nphilo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			data->forks_index = i;
			return (error(MUTEX_INIT), F);
		}
		i++;
	}
	data->forks_index = i;
	if (pthread_mutex_init(&data->to_print, NULL))
		data->print_flag = 1;
	if (pthread_mutex_init(&data->lock_done, NULL))
		data->done_flag = 1;
	if (pthread_mutex_init(&data->last_eat, NULL))
		data->last_eat_flag = 1;
	if (pthread_mutex_init(&data->meals_ate, NULL))
		data->meals_flag = 1;
	if (data->print_flag || data->done_flag
		|| data->last_eat_flag || data->meals_flag)
		return (error(MUTEX_INIT), F);
	return (S);
}

static int	init_data(t_data *data, char **params)
{
	int	i;

	i = 0;
	while (i < ft_atol(params[1]))
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].nphilo = ft_atol(params[1]);
		data->philo[i].dead_time = ft_atol(params[2]);
		data->philo[i].eat_time = ft_atol(params[3]);
		data->philo[i].sleep_time = ft_atol(params[4]);
		if (data->len == 5)
			data->philo[i].n_meals = ft_atol(params[5]);
		else
			data->philo[i].n_meals = -1;
		data->philo[i].max_ate = 0;
		data->philo[i].last_time_ate = get_time();
		data->philo[i].max_ate = 0;
		data->philo[i].data = data;
		i++;
	}
	return (S);
}

int	fill_init(char **param, t_data *data, int len)
{
	data->len = len;
	data->print_flag = 0;
	data->done_flag = 0;
	data->last_eat_flag = 0;
	data->meals_flag = 0;
	data->done = false;
	data->philo = malloc(ft_atol(param[1]) * sizeof(t_philo));
	data->forks = malloc(ft_atol(param[1]) * sizeof(t_mtx));
	if (!data->forks || !data->philo || init_data(data, param)
		|| init_mutexes(data))
		return (F);
	return (S);
}
