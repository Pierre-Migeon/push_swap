/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reversebits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:16:31 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 12:40:15 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_reversebits(unsigned char octet)
{
	unsigned char start;
	unsigned char end;
	unsigned char result;

	start = 1;
	end = 128;
	result = 0;
	while (start)
	{
		if (start & octet)
			result |= end;
		start <<= 1;
		end >>= 1;
	}
	return (result);
}
