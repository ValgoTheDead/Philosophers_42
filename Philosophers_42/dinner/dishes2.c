/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dishes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 04:03:55 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/04/24 17:06:17 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	set_last_eat(t_philo *philo)
{
	if (mutex_lockers(&philo->data->last_eat, LOCK))
	{
		throw_forks(philo);
		return (F);
	}
	philo->last_time_ate = get_time();
	if (philo->last_time_ate == ANOMALY)
		return (F);
	if (mutex_lockers(&philo->data->last_eat, UNLOCK))
	{
		throw_forks(philo);
		return (F);
	}
	return (S);
}

long	get_last_eat(t_philo *philo)
{
	long	time;

	if (mutex_lockers(&philo->data->last_eat, LOCK))
		return (F);
	time = philo->last_time_ate;
	if (mutex_lockers(&philo->data->last_eat, UNLOCK))
		return (F);
	return (time);
}

int	check_bool(t_philo *philo)
{
	if (mutex_lockers(&philo->data->lock_done, LOCK))
		return (F);
	if (philo->data->done == true)
	{
		mutex_lockers(&philo->data->lock_done, UNLOCK);
		return (11);
	}
	if (mutex_lockers(&philo->data->lock_done, UNLOCK))
		return (F);
	return (S);
}

int	set_meals_ate(t_philo *philo)
{
	if (mutex_lockers(&philo->data->meals_ate, LOCK))
		return (F);
	philo->max_ate++;
	if (mutex_lockers(&philo->data->meals_ate, UNLOCK))
		return (F);
	return (S);
}
