/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:39:17 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/03 17:47:50 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *dummy;

	dummy = (unsigned char *)b;
	while (len--)
	{
		*dummy = (unsigned char)c;
		dummy++;
	}
	return (b);
}
