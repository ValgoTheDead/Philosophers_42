/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_guest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:25:57 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/19 14:33:26 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	join_both(t_data *data)
{
	if (pthread_join(data->monitor, NULL)
		|| pthread_join(data->philo->th_philo, NULL))
		return (error(MUTEX_JOIN), F);
	return (S);
}

int	one_guest(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->philo->th_philo, NULL,
			dinner_alone, data->philo)
		|| pthread_create(&data->monitor, NULL, watching, data))
		return (error(MUTEX_CREATE), F);
	if (join_both(data))
		return (F);
	return (S);
}

static int	pick_one(t_philo *philo)
{
	if (mutex_lockers(&philo->data->forks[0], LOCK))
		return (F);
	if (safe_print(philo, "has taken a fork\n", DN))
	{
		mutex_lockers(&philo->data->forks[0], UNLOCK);
		return (F);
	}
	if (mutex_lockers(&philo->data->forks[0], UNLOCK))
		return (F);
	return (S);
}

void	*dinner_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!pick_one(philo))
			break ;
	}
	return (NULL);
}
