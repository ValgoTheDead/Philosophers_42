/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:09:37 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/24 17:53:31 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
		return (F);
	return (S);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->forks_index)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->meals_flag != 1)
		pthread_mutex_destroy(&data->meals_ate);
	if (data->last_eat_flag != 1)
		pthread_mutex_destroy(&data->last_eat);
	if (data->print_flag != 1)
		pthread_mutex_destroy(&data->to_print);
	if (data->done_flag != 1)
		pthread_mutex_destroy(&data->lock_done);
	free(data->forks);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc) || validation(argv)
		|| pre_parsing(argv, argc))
	{
		error(INVALID);
		return (F);
	}
	if (fill_init(argv, &data, argc - 1)
		|| handlers(&data))
	{
		free_all(&data);
		return (F);
	}
	free_all(&data);
}
