/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:10:38 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/07/19 14:12:02 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	error(char *err)
{
	int	i;

	i = 0;
	while (err[i])
	{
		write(2, &err[i], 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	gettwolen(char **args, int len)
{
	int	x;
	int	y;
	int	counter;

	x = 1;
	counter = 0;
	while (x < len)
	{
		y = 0;
		while (args[x][y])
		{
			counter++;
			y++;
		}
		x++;
	}
	counter = counter + (len - 2);
	return (counter);
}

char	*twoconverter(char **args, int len)
{
	int		x;
	int		i;
	int		y;
	char	*str;

	i = 0;
	x = 1;
	str = malloc(gettwolen(args, len) + 1);
	if (!str)
		return (error(MALLOC), NULL);
	while (x < len)
	{
		y = 0;
		while (args[x][y])
		{
			str[i++] = args[x][y];
			y++;
		}
		x++;
		if (x == len)
			break ;
		str[i++] = ' ';
	}
	str[i] = '\0';
	return (str);
}

long	ft_atol(char *str)
{
	size_t		i;
	long long	result;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (2147483650);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
