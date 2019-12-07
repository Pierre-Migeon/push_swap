/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:27:54 by pmigeon           #+#    #+#             */
/*   Updated: 2018/10/23 13:29:14 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *mem1;

	mem1 = (unsigned char *)s;
	while (n--)
	{
		if (*mem1 == (unsigned char)c)
			return (mem1);
		mem1++;
	}
	return (NULL);
}
