/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:59:36 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/04/24 17:01:23 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static char	**free_str(char **str, int i)
{
	while (i >= 0)
	{
		free (str[i]);
		i--;
	}
	free (str);
	return (NULL);
}

static size_t	words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*pusher(char const *s, char *split, size_t wl, size_t i)
{
	size_t	j;

	j = 0;
	while (wl > 0)
	{
		split[j] = s[i - wl];
		j++;
		wl--;
	}
	split[j] = '\0';
	return (split);
}

static char	**extractor(char const *s, char c, char **split, size_t toklen)
{
	size_t	i;
	size_t	w;
	size_t	wl;

	i = 0;
	w = 0;
	while (w < toklen)
	{
		while (s[i] && s[i] == c)
			i++;
		wl = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			wl++;
		}
		split[w] = malloc(wl + 1);
		if (!split[w])
			return (free_str(split, w));
		pusher(s, split[w], wl, i);
		w++;
	}
	split[w] = NULL;
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**new;
	size_t	tokens;

	if (!s)
		return (NULL);
	tokens = words(s, c);
	new = malloc((tokens + 1) * (sizeof(char *)));
	if (!new)
	{
		free(s);
		error(MALLOC);
		return (NULL);
	}
	new = extractor(s, c, new, tokens);
	if (!new)
	{
		free(s);
		error(MALLOC);
		return (NULL);
	}
	free(s);
	return (new);
}
