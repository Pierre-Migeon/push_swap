/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:30:22 by pmigeon           #+#    #+#             */
/*   Updated: 2018/11/06 12:38:20 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char	*trimmed;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = -1;
	if (!s)
		return (NULL);
	len = (int)ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
		len--;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		len--;
	if (len < 0)
		len = 0;
	if (!(trimmed = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s += i;
	while (++j < len)
		trimmed[j] = *s++;
	trimmed[j] = '\0';
	return (trimmed);
}
