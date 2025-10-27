/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sit_around.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 06:24:33 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/20 19:09:26 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	pick_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	right_fork = philo->philo_id - 1;
	left_fork = philo->philo_id % philo->nphilo;
	if (mutex_lockers(&philo->data->forks[right_fork], LOCK)
		|| safe_print(philo, FORK, THROW))
		return (F);
	if (right_fork == left_fork)
		return (F);
	if ((mutex_lockers(&philo->data->forks[left_fork], LOCK)
			|| safe_print(philo, FORK, THROW)))
		return (F);
	return (S);
}

int	throw_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	right_fork = philo->philo_id - 1;
	left_fork = philo->philo_id % philo->nphilo;
	if (mutex_lockers(&philo->data->forks[right_fork], UNLOCK)
		|| mutex_lockers(&philo->data->forks[left_fork], UNLOCK))
		return (F);
	return (S);
}

static int	eating(t_philo *philo)
{
	if (pick_forks(philo)
		|| safe_print(philo, EAT, THROW)
		|| set_last_eat(philo)
		|| set_meals_ate(philo))
		return (F);
	if (sleeper(philo->eat_time, philo) == ANOMALY)
	{
		throw_forks(philo);
		return (F);
	}
	if (throw_forks(philo))
		return (F);
	return (S);
}

void	*sit_around(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
	{
		if (sleeper(SLEEP_EVEN, philo) == ANOMALY)
			return (NULL);
	}
	while (1)
	{
		if (eating(philo))
			break ;
		if (safe_print(philo, SLEEP, DN)
			|| sleeper(philo->sleep_time, philo) == ANOMALY)
			break ;
		if (safe_print(philo, THINK, DN))
			break ;
	}
	return (NULL);
}
