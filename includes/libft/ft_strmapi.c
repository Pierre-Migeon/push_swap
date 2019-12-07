/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:44:10 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 12:36:50 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstring;
	int		i;

	i = -1;
	if (s && f)
	{
		if (!(newstring = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		while (s[++i])
			newstring[i] = (*f)(i, s[i]);
		newstring[i] = '\0';
	}
	else
		return (NULL);
	return (newstring);
}
