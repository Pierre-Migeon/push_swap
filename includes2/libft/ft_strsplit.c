/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:33:36 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 12:43:34 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int		ft_wordcount(const char *str, char c)
{
	int i;
	int wcount;

	i = 0;
	wcount = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			++wcount;
		i++;
	}
	return (wcount + 1);
}

static int		ft_wordlen(const char *str, char c)
{
	int i;

	i = 0;
	while (*str != c && *str)
	{
		str++;
		i++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s || !c || !(split = (char **)malloc(
					sizeof(char *) * ft_wordcount(s, c))))
		return (NULL);
	while ((size_t)j < ft_strlen(s))
	{
		while (s[j] && s[j] == c)
			j++;
		k = j;
		while (s[j] && s[j] != c)
			j++;
		if (k < j)
		{
			split[i] = ft_strnew(ft_wordlen((char *)s + k, c));
			ft_strncpy(split[i++], (char *)s + k, j - k);
		}
	}
	split[i] = NULL;
	return (split);
}
