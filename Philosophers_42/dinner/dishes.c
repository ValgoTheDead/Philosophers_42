/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dishes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 08:52:32 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/19 14:19:19 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	set_bool(t_philo *philo)
{
	if (mutex_lockers(&philo->data->lock_done, LOCK))
		return (1);
	philo->data->done = true;
	if (mutex_lockers(&philo->data->lock_done, UNLOCK))
		return (1);
	return (0);
}

int	get_meals_ate(t_philo *philo)
{
	int	number;

	if (mutex_lockers(&philo->data->meals_ate, LOCK))
		return (-1);
	number = philo->max_ate;
	if (mutex_lockers(&philo->data->meals_ate, UNLOCK))
		return (-1);
	return (number);
}

int	set_meals_out(t_philo *philo)
{
	if (mutex_lockers(&philo->data->meals_ate, LOCK))
		return (1);
	philo->max_ate += philo->n_meals;
	if (mutex_lockers(&philo->data->meals_ate, UNLOCK))
		return (1);
	return (0);
}
