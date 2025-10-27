/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:59:00 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/22 17:28:14 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	if_number(char x)
{
	if ('0' <= x && x <= '9')
		return (F);
	return (S);
}

static int	evaluate_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!if_number(str[i]))
			return (F);
		i++;
	}
	return (S);
}

int	validation(char **argv)
{
	int	x;

	x = 1;
	while (argv[x])
	{
		if (evaluate_exp(argv[x]))
			return (F);
		x++;
	}
	return (S);
}

int	pre_parsing(char **data, int len)
{
	int	x;

	x = 1;
	while (x < len)
	{
		if (ft_atol(data[x]) <= 0
			|| ft_atol(data[x]) > INT_MAX)
			return (F);
		x++;
	}
	return (S);
}
