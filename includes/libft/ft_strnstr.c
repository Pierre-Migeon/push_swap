/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 11:51:31 by pmigeon           #+#    #+#             */
/*   Updated: 2018/10/23 13:08:10 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t		j;
	const char *h_str;

	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (j < len && *haystack)
	{    
		h_str = haystack;
		i = 0;
		while (needle[i] && *h_str == needle[i] && len - j + 1 >= ft_strlen(needle))
		{
			h_str++;
			i++;
		}
		if (needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
		j++;
	}
	return (NULL);
}
