/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 03:24:04 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/19 14:22:40 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	check_death(t_data *data, long time, long last_eat, int index)
{
	long	delay;

	delay = time - last_eat;
	if (delay >= data->philo->dead_time)
	{
		if (safe_print(&data->philo[index], DEAD, DN)
			|| set_bool(&data->philo[index]))
			return (F);
		return (F);
	}
	return (S);
}

static int	check_meals(t_data *data, int *full, int index)
{
	int	meals;

	meals = get_meals_ate(&data->philo[index]);
	if (meals == -1)
		return (F);
	if (meals == data->philo->n_meals)
	{
		if (set_meals_out(&data->philo[index]))
			return (F);
		(*full)++;
	}
	if (*full == data->philo->nphilo)
	{
		if (set_bool(&data->philo[index]))
			return (F);
		return (F);
	}
	return (S);
}

void	*watching(void *arg)
{
	int		i;
	int		full;
	long	time;
	long	last_eat;
	t_data	*data;

	full = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo->nphilo)
		{
			time = get_time();
			last_eat = get_last_eat(&data->philo[i]);
			if (time == ANOMALY || last_eat == ANOMALY)
				return (NULL);
			if (check_death(data, time, last_eat, i)
				|| check_meals(data, &full, i))
				return (NULL);
			i++;
			usleep(2);
		}
	}
}
