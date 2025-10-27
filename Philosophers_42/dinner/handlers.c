/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:29:28 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/19 14:34:01 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	safe_print(t_philo *philo, char *print, int mode)
{
	long	now;

	now = 0;
	if (mutex_lockers(&philo->data->to_print, LOCK))
		return (F);
	if (check_bool(philo))
	{
		if (mode == THROW)
			throw_forks(philo);
		mutex_lockers(&philo->data->to_print, UNLOCK);
		return (F);
	}
	now = get_time() - philo->data->start_time;
	printf("%ld %d %s", now, philo->philo_id, print);
	if (mutex_lockers(&philo->data->to_print, UNLOCK))
		return (F);
	return (S);
}

static int	get_ready(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo->nphilo)
	{
		if (pthread_create(&data->philo[i].th_philo, NULL,
				sit_around, &data->philo[i]))
			return (error(MUTEX_CREATE), F);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, watching, data))
		return (error(MUTEX_CREATE), F);
	return (S);
}

static int	joiner(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL))
		return (error(MUTEX_JOIN), F);
	while (i < data->philo->nphilo)
	{
		if (pthread_join(data->philo[i].th_philo, NULL))
			return (error(MUTEX_JOIN), F);
		i++;
	}
	return (S);
}

int	handlers(t_data *data)
{
	if (get_ready(data) || joiner(data))
		return (F);
	return (S);
}
