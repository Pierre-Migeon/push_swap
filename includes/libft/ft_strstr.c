/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 10:47:18 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 12:42:02 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h_str;
	int			i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		h_str = haystack;
		i = 0;
		while (needle[i] && *h_str == needle[i])
		{
			h_str++;
			i++;
		}
		if (needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
