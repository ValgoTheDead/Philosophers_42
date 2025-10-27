/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:17:22 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/04/25 01:03:58 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	sleeper(long mili, t_philo *philo)
{
	long	start;

	start = get_time();
	if (start == ANOMALY)
		return (ANOMALY);
	while (get_time() - start < mili
		&& !check_bool(philo))
		usleep(500);
	return (S);
}

int	mutex_lockers(void *lock, int mode)
{
	if (mode == LOCK)
	{
		if (pthread_mutex_lock(lock))
		{
			printf(MUTEX_LOCK);
			return (F);
		}
	}
	else if (mode == UNLOCK)
	{
		if (pthread_mutex_unlock(lock))
		{
			printf(MUTEX_UNLOCK);
			return (F);
		}
	}
	return (S);
}
