/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 11:40:56 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/02 13:17:12 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <stdio.h>

static int		ft_numlen(int n)
{
	int i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*out;

	i = ft_numlen(n);
	sign = (n < 0) ? -1 : 1;
	if (!(out = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	out[i] = '\0';
	if (n == 0)
		out[--i] = '0';
	while (n != 0)
	{
		out[--i] = (char)((sign < 0) ? -(n % 10) + '0' : n % 10 + '0');
		n /= 10;
	}
	if (sign < 0)
		out[0] = '-';
	return (out);
}
