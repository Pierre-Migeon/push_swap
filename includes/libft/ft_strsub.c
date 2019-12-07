/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:52:39 by pmigeon           #+#    #+#             */
/*   Updated: 2018/10/21 15:15:24 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *subset;

	if (!(subset = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (!s || !s[start] || !s[start + len - 1])
		return (NULL);
	while (start--)
		s++;
	subset = ft_strncpy(subset, s, len);
	subset[len] = '\0';
	return (subset);
}
